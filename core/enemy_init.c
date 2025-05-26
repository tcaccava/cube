/* ************************************************************************** */
/*                                                                            */
/*   enemy_init.c - Initialisation des ennemis                              */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int count_enemies_in_map(t_game *game)
{
    int count = 0;
    int y = 0;
    int x;
    
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (game->map.matrix[y][x] == 'M')
                count++;
            x++;
        }
        y++;
    }
    return (count);
}

int load_shared_enemy_sprites(t_game *game, t_img shared_sprites[2])
{
    int width, height;
    
    shared_sprites[0].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_walk.xpm", &width, &height);
    if (!shared_sprites[0].ptr)
        return (0);
        
    shared_sprites[0].width = width;
    shared_sprites[0].height = height;
    shared_sprites[0].addr = mlx_get_data_addr(shared_sprites[0].ptr,
        &shared_sprites[0].bits_per_pixel,
        &shared_sprites[0].line_length,
        &shared_sprites[0].endian);
        
    shared_sprites[1].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_walk01.xpm", &width, &height);
    if (!shared_sprites[1].ptr)
        return (0);
        
    shared_sprites[1].width = width;
    shared_sprites[1].height = height;
    shared_sprites[1].addr = mlx_get_data_addr(shared_sprites[1].ptr,
        &shared_sprites[1].bits_per_pixel,
        &shared_sprites[1].line_length,
        &shared_sprites[1].endian);
        
    return (1);
}

int load_shared_shoot_sprites(t_game *game, t_img shared_sprites[2])
{
    int width, height;
    
    shared_sprites[0].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_shot.xpm", &width, &height);
    if (!shared_sprites[0].ptr)
        return (0);
        
    shared_sprites[0].width = width;
    shared_sprites[0].height = height;
    shared_sprites[0].addr = mlx_get_data_addr(shared_sprites[0].ptr,
        &shared_sprites[0].bits_per_pixel,
        &shared_sprites[0].line_length,
        &shared_sprites[0].endian);
        
    shared_sprites[1].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_shot01.xpm", &width, &height);
    if (!shared_sprites[1].ptr)
        return (0);
        
    shared_sprites[1].width = width;
    shared_sprites[1].height = height;
    shared_sprites[1].addr = mlx_get_data_addr(shared_sprites[1].ptr,
        &shared_sprites[1].bits_per_pixel,
        &shared_sprites[1].line_length,
        &shared_sprites[1].endian);
        
    return (1);
}

int load_shared_death_sprites(t_game *game, t_img shared_sprites[3])
{
    int width, height;
    
    shared_sprites[0].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_death.xpm", &width, &height);
    if (!shared_sprites[0].ptr)
        return (0);
        
    shared_sprites[0].width = width;
    shared_sprites[0].height = height;
    shared_sprites[0].addr = mlx_get_data_addr(shared_sprites[0].ptr,
        &shared_sprites[0].bits_per_pixel,
        &shared_sprites[0].line_length,
        &shared_sprites[0].endian);
        
    shared_sprites[1].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_death01.xpm", &width, &height);
    if (!shared_sprites[1].ptr)
    {
        shared_sprites[1] = shared_sprites[0];
        return (1);
    }
        
    shared_sprites[1].width = width;
    shared_sprites[1].height = height;
    shared_sprites[1].addr = mlx_get_data_addr(shared_sprites[1].ptr,
        &shared_sprites[1].bits_per_pixel,
        &shared_sprites[1].line_length,
        &shared_sprites[1].endian);

    shared_sprites[2].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_death02.xpm", &width, &height);
    if (!shared_sprites[2].ptr)
    {
        shared_sprites[2] = shared_sprites[0];
        return (1);
    }
        
    shared_sprites[2].width = width;
    shared_sprites[2].height = height;
    shared_sprites[2].addr = mlx_get_data_addr(shared_sprites[2].ptr,
        &shared_sprites[2].bits_per_pixel,
        &shared_sprites[2].line_length,
        &shared_sprites[2].endian);
        
    return (1);
}

int init_all_enemies(t_game *game)
{
    t_img shared_morty_sprites[2];
    t_img shared_morty_shoot_sprites[2];
    t_img shared_morty_death_sprites[3];
    int i;
    
    if (!load_shared_enemy_sprites(game, shared_morty_sprites))
    {
        printf("Erreur: impossible de charger les sprites d'ennemis\n");
        return (0);
    }
    
    if (!load_shared_shoot_sprites(game, shared_morty_shoot_sprites))
    {
        printf("Erreur: impossible de charger les sprites d'ennemis shoot\n");
        return (0);
    }
    
    if (!load_shared_death_sprites(game, shared_morty_death_sprites))
    {
        printf("Erreur: impossible de charger les sprites d'ennemis morts\n");
        return (0);
    }
    
    game->num_enemies = count_enemies_in_map(game);
    game->enemies = malloc(sizeof(t_enemy) * game->num_enemies);
    if (!game->enemies)
    {
        printf("Errore malloc enemies");
        return (0);
    }
    
    i = 0;
    while (i < game->num_enemies)
    {
        game->enemies[i] = (t_enemy){.x = 0.0, .y = 0.0, .angle = 0.0,
            .health = 25, .state = IDLE, .speed = 0.05, .cooldown = 0,
            .distance_to_player = 0.0, .texture = &game->map.enemy_texture,
            .active = 1, .sees_player = 0, .death_timer = 0};
        
        game->enemies[i].walk_morty[0] = shared_morty_sprites[0];
        game->enemies[i].walk_morty[1] = shared_morty_sprites[1];
        game->enemies[i].shoot_morty[0] = shared_morty_shoot_sprites[0];
        game->enemies[i].shoot_morty[1] = shared_morty_shoot_sprites[1];
        game->enemies[i].death_morty[0] = shared_morty_death_sprites[0];
        game->enemies[i].death_morty[1] = shared_morty_death_sprites[1];
        game->enemies[i].death_morty[2] = shared_morty_death_sprites[2];
        
        game->enemies[i].animation.current_frame = 0;
        game->enemies[i].animation.frame_counter = 0;
        i++;
    }
    
    if (!set_enemy_pos(game))
        printf("Errore: nessun marker 'M' trovato nella mappa");
    
    return (1);
}
