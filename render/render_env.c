/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:55:05 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/18 19:34:40 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void render_weapon(t_game *game)
{
    t_render renderer;
    t_img *weapon;
    char *dst;
    
    weapon = &game->weapons[game->current_weapon][game->player.weapon.frame];
    renderer.x = (DISPLAY_WIDTH - weapon->width) + 180;
    renderer.y = (DISPLAY_HEIGHT - weapon->height) + 250 + game->pitch;
    
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
    /* Draw weapon image pixel by pixel */
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
                    /* Get weapon texture pixel */
                    renderer.tex_addr = weapon->addr + (renderer.tex_y * weapon->line_length +
                                renderer.tex_x * (weapon->bits_per_pixel / 8));
                    renderer.color = *(unsigned int*)renderer.tex_addr;

                    /* Extract RGB components */
                    renderer.red = (renderer.color >> 16) & 0xFF;
                    renderer.green = (renderer.color >> 8) & 0xFF;
                    renderer.blue = renderer.color & 0xFF;

                    /* Skip nearly black pixels (transparency) */
                    if (!(renderer.red < 10 && renderer.green< 10 && renderer.blue< 10))
                    {
                        dst = game->screen.addr + ((renderer.y + renderer.tex_y) * game->screen.line_length +
                              (renderer.x + renderer.tex_x) * (game->screen.bits_per_pixel / 8));
                        *(unsigned int*)dst = renderer.color;
                    }
                }
                renderer.tex_x++;
            }
        }
        renderer.tex_y++;
    }
}


void render_sky(t_game *game, int column_x, t_render *renderer)
{
    renderer->y = 0;
    int screen_y = renderer->y - game->pitch;
    renderer->color = 0xb0a56b; //87CEEB; // Sky blue color

    /* Draw sky from top of screen to wall top */
    while (renderer->y < renderer->draw_start)
    {
        renderer->screen_pixel = game->screen.addr + (screen_y * game->screen.line_length
                + column_x * (game->screen.bits_per_pixel / 8));
        *(unsigned int *)(renderer->screen_pixel) = renderer->color;
        renderer->y++;
    }
}

void render_wall_portal(t_game *game, int column_x, t_render *renderer, t_ray *ray)
{
    int   CY = (DISPLAY_HEIGHT / 2) + game->pitch;
    double H  = renderer->wall_height;
    int   texture_y;

    /* Calcolo tex_x in base al punto d’impatto */
    if (ray->hit_vertical)
        renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
    else
        renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;

    renderer->y = renderer->draw_start;
    while (renderer->y <= renderer->draw_end)
    {
        if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
        {
            float rel = ((renderer->y - CY) / H) + 0.5f;
            texture_y = (int)(rel * TILE_SIZE);
            if (texture_y < 0)           texture_y = 0;
            else if (texture_y >= TILE_SIZE) texture_y = TILE_SIZE - 1;

            /* Preleva il pixel dalla texture del portale */
            renderer->tex_addr = game->map.wall_portal_texture.addr
                + (texture_y * game->map.wall_portal_texture.line_length
                   + renderer->tex_x * (game->map.wall_portal_texture.bits_per_pixel / 8));
            renderer->color = *(unsigned int *)renderer->tex_addr;

            /* Scrive sul buffer video */
            renderer->screen_pixel = game->screen.addr
                + (renderer->y * game->screen.line_length
                   + column_x * (game->screen.bits_per_pixel / 8));
            *(unsigned int *)renderer->screen_pixel = renderer->color;
        }
        renderer->y++;
    }
}

void render_door_shooted(t_game *game, int column_x, t_render *renderer, t_ray *ray)
{
    int   CY = (DISPLAY_HEIGHT / 2) + game->pitch;
    double H  = renderer->wall_height;
    int   texture_y;

    /* Calcolo tex_x in base al punto d’impatto */
    if (ray->hit_vertical)
        renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
    else
        renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;

    renderer->y = renderer->draw_start;
    while (renderer->y <= renderer->draw_end)
    {
        if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
        {
            float rel = ((renderer->y - CY) / H) + 0.5f;
            texture_y = (int)(rel * TILE_SIZE);
            if (texture_y < 0)           texture_y = 0;
            else if (texture_y >= TILE_SIZE) texture_y = TILE_SIZE - 1;

            /* Preleva il pixel dalla texture del portale */
            renderer->tex_addr = game->map.door_shooted_texture.addr
                + (texture_y * game->map.door_shooted_texture.line_length
                   + renderer->tex_x * (game->map.door_shooted_texture.bits_per_pixel / 8));
            renderer->color = *(unsigned int *)renderer->tex_addr;

            /* Scrive sul buffer video */
            renderer->screen_pixel = game->screen.addr
                + (renderer->y * game->screen.line_length
                   + column_x * (game->screen.bits_per_pixel / 8));
            *(unsigned int *)renderer->screen_pixel = renderer->color;
        }
        renderer->y++;
    }
}

void render_wall_shooted(t_game *game, int column_x, t_render *renderer, t_ray *ray)
{
    int   CY = (DISPLAY_HEIGHT / 2) + game->pitch;
    double H  = renderer->wall_height;
    int   texture_y;

    /* Calcolo tex_x in base al punto d’impatto */
    if (ray->hit_vertical)
        renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
    else
        renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;

    renderer->y = renderer->draw_start;
    while (renderer->y <= renderer->draw_end)
    {
        if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
        {
            float rel = ((renderer->y - CY) / H) + 0.5f;
            texture_y = (int)(rel * TILE_SIZE);
            if (texture_y < 0)           texture_y = 0;
            else if (texture_y >= TILE_SIZE) texture_y = TILE_SIZE - 1;

            /* Preleva il pixel dalla texture del portale */
            renderer->tex_addr = game->map.wall_shooted_texture.addr
                + (texture_y * game->map.wall_shooted_texture.line_length
                   + renderer->tex_x * (game->map.wall_shooted_texture.bits_per_pixel / 8));
            renderer->color = *(unsigned int *)renderer->tex_addr;

            /* Scrive sul buffer video */
            renderer->screen_pixel = game->screen.addr
                + (renderer->y * game->screen.line_length
                   + column_x * (game->screen.bits_per_pixel / 8));
            *(unsigned int *)renderer->screen_pixel = renderer->color;
        }
        renderer->y++;
    }
}

void render_door(t_game *game, int column_x, t_render *renderer, t_ray *ray)
{
    int   CY = (DISPLAY_HEIGHT / 2) + game->pitch;
    double H  = renderer->wall_height;
    int   texture_y;

    /* Calcolo tex_x in base al punto d’impatto */
    if (ray->hit_vertical)
        renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
    else
        renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;

    renderer->y = renderer->draw_start;
    while (renderer->y <= renderer->draw_end)
    {
        if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
        {
            // normalizza y rispetto al centro + pitch e all’altezza H
            float rel = ((renderer->y - CY) / H) + 0.5f;
            texture_y = (int)(rel * TILE_SIZE);
            if (texture_y < 0)           texture_y = 0;
            else if (texture_y >= TILE_SIZE) texture_y = TILE_SIZE - 1;

            /* Preleva il pixel dalla texture della porta */
            renderer->tex_addr = game->map.door_texture.addr
                + (texture_y * game->map.door_texture.line_length
                   + renderer->tex_x * (game->map.door_texture.bits_per_pixel / 8));
            renderer->color = *(unsigned int *)renderer->tex_addr;

            /* Scrive sul buffer video */
            renderer->screen_pixel = game->screen.addr
                + (renderer->y * game->screen.line_length
                   + column_x * (game->screen.bits_per_pixel / 8));
            *(unsigned int *)renderer->screen_pixel = renderer->color;
        }
        renderer->y++;
    }
}

void render_wall(t_game *game, int column_x, t_render *renderer, t_ray *ray)
{
    int   CY = (DISPLAY_HEIGHT / 2) + game->pitch;
    double H  = renderer->wall_height;
    int   texture_y;

    /* Calcolo tex_x in base al punto d’impatto */
    if (ray->hit_vertical)
    {
        renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
        if (cos(ray->radiant_angle) > 0)
            renderer->tex_x = TILE_SIZE - renderer->tex_x - 1;
    }
    else
    {
        renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;
        if (sin(ray->radiant_angle) < 0)
            renderer->tex_x = TILE_SIZE - renderer->tex_x - 1;
    }

    renderer->y = renderer->draw_start;
    while (renderer->y <= renderer->draw_end)
    {
        if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
        {
            float rel = ((renderer->y - CY) / H) + 0.5f;
            texture_y = (int)(rel * TILE_SIZE);
            if (texture_y < 0)           texture_y = 0;
            else if (texture_y >= TILE_SIZE) texture_y = TILE_SIZE - 1;

            /* Preleva il pixel dalla texture del muro */
            renderer->tex_addr = game->map.wall_texture.addr
                + (texture_y * game->map.wall_texture.line_length
                   + renderer->tex_x * (game->map.wall_texture.bits_per_pixel / 8));
            renderer->color = *(unsigned int *)renderer->tex_addr;

            /* Scrive sul buffer video */
            renderer->screen_pixel = game->screen.addr
                + (renderer->y * game->screen.line_length
                   + column_x * (game->screen.bits_per_pixel / 8));
            *(unsigned int *)renderer->screen_pixel = renderer->color;
        }
        renderer->y++;
    }
}

void render_floor(t_game *game, int column_x, t_render *renderer)
{
    int y;
    unsigned int floor_color = 0x444444;
    unsigned int ceiling_color = 0x777777;

    y = 0;
    while (y < renderer->draw_start)
    {
        renderer->screen_pixel = game->screen.addr + (y * game->screen.line_length
                + column_x * (game->screen.bits_per_pixel / 8));
        *(unsigned int *)(renderer->screen_pixel) = ceiling_color;
        y++;
    }
    y = renderer->draw_end + 1;
    while (y < DISPLAY_HEIGHT)
    {
        renderer->screen_pixel = game->screen.addr + (y * game->screen.line_length
                + column_x * (game->screen.bits_per_pixel / 8));
        *(unsigned int *)(renderer->screen_pixel) = floor_color;
        y++;
    }
}
