/* ************************************************************************** */
/*                                                                            */
/*   enemy_sprite.c - Rendu des sprites d'ennemis                           */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void draw_sprite_pixel(t_game *game, t_img *sprite, t_point pos, int size, t_enemy *enemy, int i, int j)
{
    int src_x, src_y, x, y;
    char *src, *dst;
    unsigned int color;
    int red, green, blue;
    int skip_pixel = 0;
    
    src_x = i * sprite->width / size;
    src_y = j * sprite->height / size;
    
    if (src_x < 0) src_x = 0;
    else if (src_x >= sprite->width) src_x = sprite->width - 1;
    if (src_y < 0) src_y = 0;
    else if (src_y >= sprite->height) src_y = sprite->height - 1;
    
    src = sprite->addr + src_y * sprite->line_length + src_x * (sprite->bits_per_pixel / 8);
    color = *(unsigned int *)src;
    
    red = (color >> 16) & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = color & 0xFF;

    if (enemy->state == DEAD)
    {
        if (red > 180 && blue > 180 && green < 100)
            skip_pixel = 1;
    }
    else
    {
        int tolerance = 2;
        if (abs(red - 255) <= tolerance && abs(green - 0) <= tolerance && abs(blue - 0) <= tolerance)
            skip_pixel = 1;
    }

    if (!skip_pixel)
    {
        x = pos.x + i;
        y = pos.y + j;
        if (x >= 0 && x < DISPLAY_WIDTH && y >= 0 && y < DISPLAY_HEIGHT)
        {
            dst = game->screen.addr + y * game->screen.line_length + x * (game->screen.bits_per_pixel / 8);
            *(unsigned int *)dst = color;
        }
    }
}

void draw_enemy_sprite(t_game *game, t_img *sprite, t_point pos, int size, t_enemy *enemy)
{
    int i = 0;
    
    if (!sprite || !sprite->addr || size <= 0)
        return;
        
    while (i < size)
    {
        int j = 0;
        while (j < size)
        {
            draw_sprite_pixel(game, sprite, pos, size, enemy, i, j);
            j++;
        }
        i++;
    }
}

void render_death_animation(t_game *game, t_enemy *enemy)
{
    t_render renderer;
    t_img *current_sprite;
    int death_y_offset = 0;
    int death_size_modifier = 0;
    int is_visible;
    
    if (enemy->animation.current_frame == 0)
    {
        death_y_offset = 0;
        death_size_modifier = 0;
    }
    else if (enemy->animation.current_frame == 1)
    {
        death_y_offset = 20;
        death_size_modifier = -10;
    }
    else
    {
        death_y_offset = 100;
        death_size_modifier = -20;
    }
    
    current_sprite = &enemy->death_morty[enemy->animation.current_frame];
    
    calculate_enemy_transform(game, enemy, &renderer);
    
    if (renderer.floor_y <= 0.2f)
        return;
    
    calculate_enemy_screen_pos(game, &renderer);
    
    renderer.sprite_size += death_size_modifier;
    if (renderer.sprite_size < 10)
        renderer.sprite_size = 10;
    
    if (renderer.x < 0 || renderer.x >= DISPLAY_WIDTH)
        return;
    
    is_visible = check_enemy_occlusion(game, &renderer);
    if (!is_visible)
        return;
    
    setup_enemy_render_params(game, &renderer);
    renderer.draw_end += death_y_offset;
    
    printf("Death frame %d: y_offset=%d, size=%d\n", 
           enemy->animation.current_frame, death_y_offset, renderer.sprite_size);
    
    draw_enemy_sprite(game, current_sprite, 
                     (t_point){renderer.draw_start, renderer.draw_end}, 
                     renderer.sprite_size, enemy);
}