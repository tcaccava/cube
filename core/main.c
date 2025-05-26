/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:25:20 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/20 21:48:44 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
/* ************************************************************************** */
/*                                                                            */
/*   main.c - Point d'entrée du programme                                    */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void init_player(t_player *player)
{
    player->x = DISPLAY_WIDTH / 2;
    player->y = DISPLAY_HEIGHT / 2;
    player->angle = M_PI / 3;
    player->fov = player->angle;
    update_camera_vectors(player);
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
    player->left_rotate = false;
    player->right_rotate = false;
    player->turn_back = false;
    player->current_weapon = PORTALGUN;
    player->health = 100;
    player->weapon.current_state = WEAPON_NEUTRE;
    player->weapon.frame = 0;
    player->weapon.frame_delay = 0;
    player->weapon.is_firing = 0;
    player->fire_cooldown = 0;
}

void init_rays(t_game *game)
{
    int i = 0;
    double ray_offset;
    double radiant_angle;
    
    while (i < DISPLAY_WIDTH)
    {
        ray_offset = game->player.fov * ((double)i / DISPLAY_WIDTH - 0.5);
        radiant_angle = game->player.angle + ray_offset;
        while (radiant_angle < 0)
            radiant_angle += 2 * M_PI;
        while (radiant_angle >= 2 * M_PI)
            radiant_angle -= 2 * M_PI;
        game->rays[i].radiant_angle = radiant_angle;
        game->rays[i].player_angle = game->player.angle;
        game->rays[i].distance = ray_casting(game, radiant_angle, i);
        i++;
    }
}

int init_game_mode(t_game *game, int argc, char **argv)
{
    if (argc == 2)
    {
        if (check_file_cub(argv[1]) == 0)
        {
            printf("Usage: %s <map_file.cub>\n", argv[0]);
            return (0);
        }
        if (!init_game(game, argv[1]))
        {
            printf("Error: game init failed\n");
            return (0);
        }
    }
    else if (argc == 6)
    {
        if (check_file_cub(argv[1]) == 0)
        {
            printf("Usage: %s <map_file.cub> <north.xpm> <south.xpm> <east.xpm> <west.xpm>\n", argv[0]);
            return (0);
        }
        if (!init_game_with_4_textures(game, argv[1], argv[2], argv[3], argv[4], argv[5]))
        {
            printf("Error: game init failed\n");
            return (0);
        }
    }
    else
    {
        printf("Usage: %s <map_file.cub>\n", argv[0]);
        printf("   ou: %s <map_file.cub> <north.xpm> <south.xpm> <east.xpm> <west.xpm>\n", argv[0]);
        return (0);
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_game game;

    if (!init_game_mode(&game, argc, argv))
        return (1);
    
    init_rays(&game);
    loop_game(&game);
    return (0);
}