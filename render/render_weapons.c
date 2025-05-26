/* ************************************************************************** */
/*                                                                            */
/*   render_weapons.c - Rendu des armes                                     */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void update_weapon_animation(t_game *game)
{
    if (game->player.weapon.is_firing)
    {
        game->player.weapon.frame_delay--;
        if (game->player.weapon.frame_delay <= 0)
        {
            if (game->current_weapon == RAYGUN)
            {
                if (game->player.weapon.current_state == WEAPON_PREFIRE)
                {
                    game->player.weapon.current_state = WEAPON_FIRE;
                    game->player.weapon.frame = 2;
                    game->player.weapon.frame_delay = 2;
                }
                else if (game->player.weapon.current_state == WEAPON_FIRE)
                {
                    game->player.weapon.current_state = WEAPON_POSTFIRE;
                    game->player.weapon.frame = 1;
                    game->player.weapon.frame_delay = 2;
                }
                else if (game->player.weapon.current_state == WEAPON_POSTFIRE)
                {
                    game->player.weapon.current_state = WEAPON_NEUTRE;
                    game->player.weapon.frame = 0;
                    game->player.weapon.is_firing = 0;
                }
            }
        }
    }
}

void draw_weapon_pixel(t_game *game, t_img *weapon, t_render *renderer, int tex_x, int tex_y)
{
    char *dst;
    
    renderer->tex_addr = weapon->addr + (tex_y * weapon->line_length +
                tex_x * (weapon->bits_per_pixel / 8));
    renderer->color = *(unsigned int*)renderer->tex_addr;

    renderer->red = (renderer->color >> 16) & 0xFF;
    renderer->green = (renderer->color >> 8) & 0xFF;
    renderer->blue = renderer->color & 0xFF;

    if (!(renderer->red < 10 && renderer->green < 10 && renderer->blue < 10))
    {
        dst = game->screen.addr + ((renderer->y + tex_y) * game->screen.line_length +
              (renderer->x + tex_x) * (game->screen.bits_per_pixel / 8));
        *(unsigned int*)dst = renderer->color;
    }
}

void render_weapon(t_game *game)
{
    t_render renderer;
    t_img *weapon;
    
    if (game->map.north.ptr != NULL)
        return;
        
    weapon = &game->weapons[game->current_weapon][game->player.weapon.frame];
    renderer.x = (DISPLAY_WIDTH - weapon->width) + 180;
    renderer.y = (DISPLAY_HEIGHT - weapon->height) + 250 + game->pitch;
    
    update_weapon_animation(game);
    
    renderer.tex_y = 0;
    while (renderer.tex_y < weapon->height)
    {
        if (renderer.y + renderer.tex_y >= 0 && renderer.y + renderer.tex_y < DISPLAY_HEIGHT)
        {
            renderer.tex_x = 0;
            while (renderer.tex_x < weapon->width)
            {
                if (renderer.x + renderer.tex_x >= 0 && renderer.x + renderer.tex_x < DISPLAY_WIDTH)
                {
                    draw_weapon_pixel(game, weapon, &renderer, renderer.tex_x, renderer.tex_y);
                }
                renderer.tex_x++;
            }
        }
        renderer.tex_y++;
    }
}