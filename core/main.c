/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:26 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:36:26 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// static int load_game_assets_after_parsing(t_game *game)
// {
// 	if (game->texture_paths.north)
//     {
//         if (!load_directional_textures(game, &game->texture_paths))
//             return (0);
//     }
//     else
//     {
//         // Charger les textures de base si pas de textures directionnelles
//         if (!load_all_textures(game))
//             return (0);
//     }
//     // Charger les armes
//     if (!load_all_weapons(game))
//         return (0);
//     // Charger les weapon pickups
//     if (!load_weapon_pickup_sprites(game))
//         return (0);
//     if (!set_weapon_positions(game))
//         return (0);
//     // Charger les portes
//     if (!load_open_door_sprites(game))
//         return (0);
//     if (!set_open_door_positions(game))
//         return (0);
//     // Initialiser les ennemis
//     if (!init_all_enemies(game))
//         return (0);
//     // Initialiser les portails et l'UI
//     init_portals(game);
//     init_ui_components(game);
//     return (1);
// }

// // core/init_game.c
// static int init_game_after_parsing(t_game *game)
// {
//     // Initialiser le joueur
//     init_player(&game->player);
//     game->player.game = game;
//     // Initialiser MLX et la fenêtre
//     if (!init_mlx_window(game))
//         return (0);
//     // Définir la position du joueur sur la carte
//     if (!set_player_pos(game))
//     {
//         printf("Erreur: Aucune position de départ trouvée dans la carte!\n");
//         return (0);
//     }
//     // Initialiser l'arme courante
//     game->current_weapon = HANDS;
//     // Charger les assets du jeu
//     if (!load_game_assets_after_parsing(game))
//         return (0);
//     return (1);
// }

// int main(int argc, char **argv)
// {
//     t_game game;
//     if (argc != 2)
//     {
//         printf("Usage: %s <scene.cub>\n", argv[0]);
//         return (1);
//     }
//     // Initialiser la structure game
//     ft_memset(&game, 0, sizeof(t_game));
//     // Parser le fichier .cub
//     if (!parse_cub_file(argv[1], &game))
//         return (1);
//     // AJOUT : Initialisation complète du jeu
//     if (!init_game_after_parsing(&game))
//     {
//         printf("Error: game initialization failed\n");
//         return (1);
//     }
//     init_rays(&game);
//     loop_game(&game);
//     return (0);
// }

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (!init_game_mode(&game, argc, argv))
		return (1);
	init_rays(&game);
	loop_game(&game);
	return (0);
}
