
#include "../cube3d.h"

void render_column(t_game *game, int column_x, t_ray *ray)
{
    t_render renderer;

    renderer.corrected_dist = no_fish_eye(ray->distance, ray->radiant_angle, ray->player_angle);
    renderer.wall_height = calc_wall_height(renderer.corrected_dist);
    renderer.door_height = (int)(renderer.wall_height * 1.3);
    
    renderer.draw_start = (DISPLAY_HEIGHT / 2) - (renderer.wall_height / 2) + game->pitch;
    renderer.draw_end = (DISPLAY_HEIGHT / 2) + (renderer.wall_height / 2) + game->pitch;
    
    renderer.texture_offset_y = 0;
    if (renderer.wall_height > DISPLAY_HEIGHT)
        renderer.texture_offset_y = (renderer.wall_height - DISPLAY_HEIGHT) / 2;
    
    if (renderer.draw_start < 0)
        renderer.draw_start = 0;
    if (renderer.draw_end >= DISPLAY_HEIGHT)
        renderer.draw_end = DISPLAY_HEIGHT - 1;
    
    if (ray->hit_type == 'P')
        render_wall_portal(game, column_x, &renderer, ray);
    else if (ray->hit_type == 'D')
        render_door(game, column_x, &renderer, ray);
    else if (ray->hit_type == 'i')
        render_wall_shooted(game, column_x, &renderer, ray);
    else if (ray->hit_type == 'd')
        render_door_shooted(game, column_x, &renderer, ray);
    else
        render_wall(game, column_x, &renderer, ray);
        
    render_floor_and_ceiling(game, column_x, &renderer);
}

void render_scene(t_game *game)
{
    int col = 0;

    while (col < DISPLAY_WIDTH)
    {
        render_column(game, col, &game->rays[col]);
        col++;
    }
}

void render_frame(t_game *game)
{
    int col = 0;

    while (col < DISPLAY_WIDTH)
    {
        render_column(game, col, &game->rays[col]);
        col++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->screen.ptr, 0, 0);
    render_weapon(game);
}

void render_ui(t_game *game)
{
    render_weapon(game);
    draw_health_bar(game);
    minimap(game);
}

void render_next_frame_enemies(t_game *game)
{
    int j = 0;
    
    while (j < game->num_enemies)
    {
        if (game->enemies[j].active)
            render_enemy(game, &game->enemies[j]);
        j++;
    }
}