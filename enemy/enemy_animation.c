/* ************************************************************************** */
/*                                                                            */
/*   enemy_animation.c - Gestion des animations d'ennemis                    */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void update_death_animation(t_enemy *enemy)
{
    int frame_duration;
    
    if (enemy->state != DEAD)
        return;
        
    enemy->animation.frame_counter++;
    
    if (enemy->animation.current_frame == 0)
        frame_duration = 10;
    else if (enemy->animation.current_frame == 1)
        frame_duration = 4;
    else
        frame_duration = 300;
    
    if (enemy->animation.frame_counter >= frame_duration)
    {
        enemy->animation.current_frame++;
        
        if (enemy->animation.current_frame >= 3)
            enemy->animation.current_frame = 2;
        
        enemy->animation.frame_counter = 0;
        printf("Death progression: frame %d\n", enemy->animation.current_frame);
    }
}

void update_enemy_animation(t_enemy *enemy)
{
    if (!enemy->active)
        return;

    if (enemy->state == DEAD)
    {
        update_death_animation(enemy);
        return;
    }
    
    if (enemy->state == SEARCH || enemy->state == IDLE)
    {
        enemy->animation.frame_counter++;
        if (enemy->animation.frame_counter >= ANIMATION_SPEED)
        {
            enemy->animation.current_frame = (enemy->animation.current_frame + 1) % 2;
            enemy->animation.frame_counter = 0;
        }
    }
    else if (enemy->state == SHOOT)
    {
        enemy->animation.frame_counter++;
        if (enemy->animation.frame_counter >= ANIMATION_SPEED)
        {
            enemy->animation.current_frame = (enemy->animation.current_frame + 1) % 2;
            enemy->animation.frame_counter = 0;
        }
    }
}

int load_enemy_animations(t_game *game, t_enemy *enemy)
{
    int width, height;
    
    // Charger sprites de marche
    enemy->walk_morty[0].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_walk.xpm", &width, &height);
    if (!enemy->walk_morty[0].ptr)
        return (0);
        
    enemy->walk_morty[0].width = width;
    enemy->walk_morty[0].height = height;
    enemy->walk_morty[0].addr = mlx_get_data_addr(enemy->walk_morty[0].ptr,
        &enemy->walk_morty[0].bits_per_pixel,
        &enemy->walk_morty[0].line_length,
        &enemy->walk_morty[0].endian);
        
    enemy->walk_morty[1].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_walk01.xpm", &width, &height);
    if (!enemy->walk_morty[1].ptr)
        return (0);
        
    enemy->walk_morty[1].width = width;
    enemy->walk_morty[1].height = height;
    enemy->walk_morty[1].addr = mlx_get_data_addr(enemy->walk_morty[1].ptr,
        &enemy->walk_morty[1].bits_per_pixel,
        &enemy->walk_morty[1].line_length,
        &enemy->walk_morty[1].endian);

    // Charger sprites de tir
    enemy->shoot_morty[0].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_shot.xpm", &width, &height);
    if (!enemy->shoot_morty[0].ptr)
        return (0);
        
    enemy->shoot_morty[0].width = width;
    enemy->shoot_morty[0].height = height;
    enemy->shoot_morty[0].addr = mlx_get_data_addr(enemy->shoot_morty[0].ptr,
        &enemy->shoot_morty[0].bits_per_pixel,
        &enemy->shoot_morty[0].line_length,
        &enemy->shoot_morty[0].endian);
        
    enemy->shoot_morty[1].ptr = mlx_xpm_file_to_image(game->mlx,
        "./texture/morty_shot01.xpm", &width, &height);
    if (!enemy->shoot_morty[1].ptr)
        return (0);
        
    enemy->shoot_morty[1].width = width;
    enemy->shoot_morty[1].height = height;
    enemy->shoot_morty[1].addr = mlx_get_data_addr(enemy->shoot_morty[1].ptr,
        &enemy->shoot_morty[1].bits_per_pixel,
        &enemy->shoot_morty[1].line_length,
        &enemy->shoot_morty[1].endian);

    return (1);
}

int load_death_animations(t_game *game, t_enemy *enemy)
{
    int width, height;

    // Charger sprites de mort
    enemy->death_morty[0].ptr = mlx_xpm_file_to_image(game->mlx, 
        "./texture/morty_death.xpm", &width, &height);
    if (!enemy->death_morty[0].ptr)
        return (0);
    enemy->death_morty[0].width = width;
    enemy->death_morty[0].height = height;
    enemy->death_morty[0].addr = mlx_get_data_addr(enemy->death_morty[0].ptr,
        &enemy->death_morty[0].bits_per_pixel,
        &enemy->death_morty[0].line_length,
        &enemy->death_morty[0].endian);

    enemy->death_morty[1].ptr = mlx_xpm_file_to_image(game->mlx, 
        "./texture/morty_death01.xpm", &width, &height);
    if (!enemy->death_morty[1].ptr)
        return (1);
    enemy->death_morty[1].width = width;
    enemy->death_morty[1].height = height;
    enemy->death_morty[1].addr = mlx_get_data_addr(enemy->death_morty[1].ptr,
        &enemy->death_morty[1].bits_per_pixel,
        &enemy->death_morty[1].line_length,
        &enemy->death_morty[1].endian);

    enemy->death_morty[2].ptr = mlx_xpm_file_to_image(game->mlx, 
        "./texture/morty_death02.xpm", &width, &height);
    if (!enemy->death_morty[2].ptr)
        return (2);
    enemy->death_morty[2].width = width;
    enemy->death_morty[2].height = height;
    enemy->death_morty[2].addr = mlx_get_data_addr(enemy->death_morty[2].ptr,
        &enemy->death_morty[2].bits_per_pixel,
        &enemy->death_morty[2].line_length,
        &enemy->death_morty[2].endian);
    
    return (1);
}