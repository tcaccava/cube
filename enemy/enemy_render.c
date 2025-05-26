/* ************************************************************************** */
/*                                                                            */
/*   enemy_render.c - Rendu principal des ennemis                           */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void calculate_enemy_transform(t_game *game, t_enemy *enemy, t_render *render)
{
    double dx, dy, inv_det;
    
    dx = enemy->x - game->player.x;
    dy = enemy->y - game->player.y;
    
    inv_det = 1.0f / (game->player.plane_x * game->player.dir_y - 
                      game->player.dir_x * game->player.plane_y);
    render->floor_x = inv_det * (game->player.dir_y * dx - game->player.dir_x * dy);
    render->floor_y = inv_det * (-game->player.plane_y * dx + game->player.plane_x * dy);
}

void calculate_enemy_screen_pos(t_game *game, t_render *render)
{
    double distance_to_projection_plane;
    double corrected_dist;
    double enemy_height;
    
    render->x = (int)((DISPLAY_WIDTH / 2) * (1 + render->floor_x / render->floor_y));
    
    distance_to_projection_plane = (DISPLAY_WIDTH / 2.0) / tan(game->player.fov / 2.0);
    corrected_dist = fmax(render->floor_y, 0.1);
    enemy_height = TILE_SIZE * 1.4;
    
    render->sprite_size = (int)((enemy_height / corrected_dist) * distance_to_projection_plane);
    
    if (render->sprite_size > DISPLAY_HEIGHT * 2)
        render->sprite_size = DISPLAY_HEIGHT * 2;
    if (render->sprite_size < 1)
        render->sprite_size = 1;
}

int check_enemy_occlusion(t_game *game, t_render *render)
{
    int sprite_left_edge;
    int sprite_start_pixel;
    int sprite_end_pixel;
    int sample_count;
    int col;
    int i;

    sprite_left_edge = render->x - render->sprite_size / 2;
    
    if (sprite_left_edge < 0)
        sprite_start_pixel = 0;
    else
        sprite_start_pixel = sprite_left_edge;
        
    sprite_end_pixel = sprite_left_edge + render->sprite_size - 1;
    
    if (sprite_end_pixel >= DISPLAY_WIDTH)
        sprite_end_pixel = DISPLAY_WIDTH - 1;

    sample_count = 0;
    i = 0;
    while (i < 5)
    {
        col = sprite_start_pixel + i * (sprite_end_pixel - sprite_start_pixel) / 4;
        if (render->floor_y < game->depth_buffer[col])
            sample_count++;
        i++;
    }
    return (sample_count > 0);
}

void setup_enemy_render_params(t_game *game, t_render *render)
{
    int y_offset = 55;
    
    render->draw_start = render->x - render->sprite_size / 2;
    render->draw_end = (DISPLAY_HEIGHT - render->sprite_size) / 2 + game->pitch + y_offset;
}

void render_enemy(t_game *game, t_enemy *enemy)
{
    t_render renderer;
    t_img *current_sprite;
    int is_visible;
    
    if (enemy->state == DEAD)
    {
        if (enemy->death_timer > 0)
            enemy->death_timer--;
        else
        {
            enemy->active = 0;
            return;
        }
        update_death_animation(enemy);      
        render_death_animation(game, enemy);
        return;
    }
    
    update_enemy_animation(enemy);
    
    if (enemy->state == SHOOT)
        current_sprite = &enemy->shoot_morty[enemy->animation.current_frame];
    else
        current_sprite = &enemy->walk_morty[enemy->animation.current_frame];
    
    calculate_enemy_transform(game, enemy, &renderer);
    
    if (renderer.floor_y <= 0.2f)
        return;
    
    calculate_enemy_screen_pos(game, &renderer);
    
    if (renderer.x < 0 || renderer.x >= DISPLAY_WIDTH)
        return;
    
    is_visible = check_enemy_occlusion(game, &renderer);
    if (!is_visible)
        return;
    
    setup_enemy_render_params(game, &renderer);
    draw_enemy_sprite(game, current_sprite, 
                     (t_point){renderer.draw_start, renderer.draw_end}, 
                     renderer.sprite_size, enemy);
}