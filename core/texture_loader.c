
#include "cube3d.h"

int load_basic_textures(t_game *game)
{
    int width, height;
    
    game->map.wall_texture.ptr = mlx_xpm_file_to_image(game->mlx,
            "./texture/wall.xpm", &width, &height);
    if (!game->map.wall_texture.ptr)
        return (0);
    game->map.wall_texture.width = width;
    game->map.wall_texture.height = height;
    game->map.wall_texture.addr = mlx_get_data_addr(game->map.wall_texture.ptr,
            &game->map.wall_texture.bits_per_pixel,
            &game->map.wall_texture.line_length,
            &game->map.wall_texture.endian);

    game->map.floor_texture.ptr = mlx_xpm_file_to_image(game->mlx,
            "./texture/floor.xpm", &width, &height);
    if (!game->map.floor_texture.ptr)
        return (0);
    game->map.floor_texture.width = width;
    game->map.floor_texture.height = height;
    game->map.floor_texture.addr = mlx_get_data_addr(game->map.floor_texture.ptr,
            &game->map.floor_texture.bits_per_pixel,
            &game->map.floor_texture.line_length,
            &game->map.floor_texture.endian);
    
    return (1);
}

int load_door_textures(t_game *game)
{
    int width, height;
    
    game->map.door_texture.ptr = mlx_xpm_file_to_image(game->mlx,
            "./texture/door.xpm", &width, &height);
    if (!game->map.door_texture.ptr)
        return (0);
    game->map.door_texture.width = width;
    game->map.door_texture.height = height;
    game->map.door_texture.addr = mlx_get_data_addr(game->map.door_texture.ptr,
            &game->map.door_texture.bits_per_pixel,
            &game->map.door_texture.line_length,
            &game->map.door_texture.endian);

    game->map.door_shooted_texture.ptr = mlx_xpm_file_to_image(game->mlx,
            "./texture/door_shooted.xpm", &width, &height);
    if (!game->map.door_shooted_texture.ptr)
        return (0);
    game->map.door_shooted_texture.width = width;
    game->map.door_shooted_texture.height = height;
    game->map.door_shooted_texture.addr = mlx_get_data_addr(game->map.door_shooted_texture.ptr,
            &game->map.door_shooted_texture.bits_per_pixel,
            &game->map.door_shooted_texture.line_length,
            &game->map.door_shooted_texture.endian);
    
    return (1);
}

int load_special_textures(t_game *game)
{
    int width, height;

    game->map.wall_portal_texture.ptr = mlx_xpm_file_to_image(game->mlx,
            "./texture/wall_portal.xpm", &width, &height);
    if (!game->map.wall_portal_texture.ptr)
        return (0);
    game->map.wall_portal_texture.width = width;
    game->map.wall_portal_texture.height = height;
    game->map.wall_portal_texture.addr = mlx_get_data_addr(game->map.wall_portal_texture.ptr,
            &game->map.wall_portal_texture.bits_per_pixel,
            &game->map.wall_portal_texture.line_length,
            &game->map.wall_portal_texture.endian);

    game->map.wall_shooted_texture.ptr = mlx_xpm_file_to_image(game->mlx,
            "./texture/wall_shooted.xpm", &width, &height);
    if (!game->map.wall_shooted_texture.ptr)
        return (0);
    game->map.wall_shooted_texture.width = width;
    game->map.wall_shooted_texture.height = height;
    game->map.wall_shooted_texture.addr = mlx_get_data_addr(game->map.wall_shooted_texture.ptr,
            &game->map.wall_shooted_texture.bits_per_pixel,
            &game->map.wall_shooted_texture.line_length,
            &game->map.wall_shooted_texture.endian);
            
    return (1);
}

int load_directional_textures(t_game *game, char *north, char *south, char *east, char *west)
{
    int width, height;

    game->map.north.ptr = mlx_xpm_file_to_image(game->mlx, north, &width, &height);
    if (!game->map.north.ptr)
        return (0);
    game->map.north.width = width;
    game->map.north.height = height;
    game->map.north.addr = mlx_get_data_addr(game->map.north.ptr,
            &game->map.north.bits_per_pixel,
            &game->map.north.line_length,
            &game->map.north.endian);

    game->map.south.ptr = mlx_xpm_file_to_image(game->mlx, south, &width, &height);
    if (!game->map.south.ptr)
        return (0);
    game->map.south.width = width;
    game->map.south.height = height;
    game->map.south.addr = mlx_get_data_addr(game->map.south.ptr,
            &game->map.south.bits_per_pixel,
            &game->map.south.line_length,
            &game->map.south.endian);

    game->map.east.ptr = mlx_xpm_file_to_image(game->mlx, east, &width, &height);
    if (!game->map.east.ptr)
        return (0);
    game->map.east.width = width;
    game->map.east.height = height;
    game->map.east.addr = mlx_get_data_addr(game->map.east.ptr,
            &game->map.east.bits_per_pixel,
            &game->map.east.line_length,
            &game->map.east.endian);

    game->map.west.ptr = mlx_xpm_file_to_image(game->mlx, west, &width, &height);
    if (!game->map.west.ptr)
        return (0);
    game->map.west.width = width;
    game->map.west.height = height;
    game->map.west.addr = mlx_get_data_addr(game->map.west.ptr,
            &game->map.west.bits_per_pixel,
            &game->map.west.line_length,
            &game->map.west.endian);

    return (1);
}

int load_all_textures(t_game *game)
{
    if (!load_basic_textures(game))
        return (0);
    if (!load_door_textures(game))
        return (0);
    if (!load_special_textures(game))
        return (0);
    return (1);
}