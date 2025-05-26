/* ************************************************************************** */
/*                                                                            */
/*   render_walls.c - Rendu des murs et portes                              */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

t_img* get_wall_texture(t_game *game, t_ray *ray)
{
    if (game->map.north.ptr != NULL)
    {
        if (ray->hit_vertical)
        {
            if (cos(ray->radiant_angle) > 0)
                return &game->map.east;
            else
                return &game->map.west;
        }
        else
        {
            if (sin(ray->radiant_angle) > 0)
                return &game->map.south;
            else
                return &game->map.north;
        }
    }
    else
    {
        return &game->map.wall_texture;
    }
}

void render_wall(t_game *game, int column_x, t_render *renderer, t_ray *ray)
{
    int CY = (DISPLAY_HEIGHT / 2) + game->pitch;
    double H = renderer->wall_height;
    int texture_y;
    t_img *current_texture = get_wall_texture(game, ray);

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
            if (texture_y < 0) texture_y = 0;
            else if (texture_y >= TILE_SIZE) texture_y = TILE_SIZE - 1;

            renderer->tex_addr = current_texture->addr
                + (texture_y * current_texture->line_length
                + renderer->tex_x * (current_texture->bits_per_pixel / 8));
            renderer->color = *(unsigned int *)renderer->tex_addr;

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
    int CY = (DISPLAY_HEIGHT / 2) + game->pitch;
    double H = renderer->wall_height;
    int texture_y;

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
            if (texture_y < 0) texture_y = 0;
            else if (texture_y >= TILE_SIZE) texture_y = TILE_SIZE - 1;

            renderer->tex_addr = game->map.door_texture.addr
                + (texture_y * game->map.door_texture.line_length
                + renderer->tex_x * (game->map.door_texture.bits_per_pixel / 8));
            renderer->color = *(unsigned int *)renderer->tex_addr;

            renderer->screen_pixel = game->screen.addr
                + (renderer->y * game->screen.line_length
                + column_x * (game->screen.bits_per_pixel / 8));
            *(unsigned int *)renderer->screen_pixel = renderer->color;
        }
        renderer->y++;
    }
}

void render_wall_portal(t_game *game, int column_x, t_render *renderer, t_ray *ray)
{
    int CY = (DISPLAY_HEIGHT / 2) + game->pitch;
    double H = renderer->wall_height;
    int texture_y;

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
            if (texture_y < 0) texture_y = 0;
            else if (texture_y >= TILE_SIZE) texture_y = TILE_SIZE - 1;

            renderer->tex_addr = game->map.wall_portal_texture.addr
                + (texture_y * game->map.wall_portal_texture.line_length
                + renderer->tex_x * (game->map.wall_portal_texture.bits_per_pixel / 8));
            renderer->color = *(unsigned int *)renderer->tex_addr;

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
    int CY = (DISPLAY_HEIGHT / 2) + game->pitch;
    double H = renderer->wall_height;
    int texture_y;

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
            if (texture_y < 0) texture_y = 0;
            else if (texture_y >= TILE_SIZE) texture_y = TILE_SIZE - 1;

            renderer->tex_addr = game->map.wall_shooted_texture.addr
                + (texture_y * game->map.wall_shooted_texture.line_length
                + renderer->tex_x * (game->map.wall_shooted_texture.bits_per_pixel / 8));
            renderer->color = *(unsigned int *)renderer->tex_addr;

            renderer->screen_pixel = game->screen.addr
                + (renderer->y * game->screen.line_length
                + column_x * (game->screen.bits_per_pixel / 8));
            *(unsigned int *)renderer->screen_pixel = renderer->color;
        }
        renderer->y++;
    }
}