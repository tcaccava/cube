/* ************************************************************************** */
/*                                                                            */
/*   weapon_loader.c - Chargement des textures d'armes                      */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int load_weapon_textures(void *mlx, t_img weapon_textures[3], int weapon_type)
{
    char *texture_paths[MAX_WEAPONS][3] = {
        {"./texture/w_raygun.xpm", "./texture/w_raygun_prefire.xpm", "./texture/w_raygun_fire.xpm"},
        {"./texture/w_portalgun.xpm", "./texture/w_portalgun.xpm", "./texture/w_portalgun.xpm"}
    };
    int width, height;
    int i = 0;

    while (i < 3)
    {
        weapon_textures[i].ptr = mlx_xpm_file_to_image(mlx,
                texture_paths[weapon_type][i], &width, &height);
        if (!weapon_textures[i].ptr)
        {
            printf("Erreur de chargement de la texture : %s\n",
                texture_paths[weapon_type][i]);
            return (0);
        }
        weapon_textures[i].addr = mlx_get_data_addr(weapon_textures[i].ptr,
                &weapon_textures[i].bits_per_pixel,
                &weapon_textures[i].line_length, &weapon_textures[i].endian);
        weapon_textures[i].width = width;
        weapon_textures[i].height = height;
        i++;
    }
    return (1);
}

int load_raygun(t_game *game)
{
    if (!load_weapon_textures(game->mlx, game->weapons[RAYGUN], RAYGUN))
    {
        printf("Erreur de chargement des textures du Ray Gun\n");
        return (0);
    }
    return (1);
}

int load_portalgun(t_game *game)
{
    if (!load_weapon_textures(game->mlx, game->weapons[PORTALGUN], PORTALGUN))
    {
        printf("Erreur de chargement des textures du Portal Gun\n");
        return (0);
    }
    return (1);
}

int load_all_weapons(t_game *game)
{
    if (!load_raygun(game))
        return (0);
    if (!load_portalgun(game))
        return (0);
    return (1);
}

int init_game_with_4_textures(t_game *game, char *map_file, char *north_texture, char *south_texture, char *east_texture, char *west_texture)
{
    init_player(&game->player);
    game->player.game = game;
    
    if (!init_mlx_window(game))
        return (0);
    
    if (!init_map_and_player(game, map_file))
        return (0);
    
    game->current_weapon = RAYGUN;
    
    if (!load_special_textures(game))
        return (0);
    
    if (!load_all_weapons(game))
        return (0);
    
    if (!load_door_textures(game))
        return (0);
    
    if (!load_directional_textures(game, north_texture, south_texture, east_texture, west_texture))
        return (0);
    
    if (!init_all_enemies(game))
        return (0);
    
    init_portals(game);
    init_ui_components(game);
    
    return (1);
}