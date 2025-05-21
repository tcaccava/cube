/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:50:29 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/21 20:44:25 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../gnl/get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define W 119
# define A 97
# define S 115
# define D 100

# define ESC 65307

# define R 114

# define Q 113
# define E 101

# define LEFT 65508
# define RIGHT 65363

# define RAYGUN 0
# define PORTALGUN 1
# define MAX_WEAPONS 2


# define TILE_SIZE 64
# define DISPLAY_WIDTH 1920
# define DISPLAY_HEIGHT 1080
# define FOV (M_PI / 3)
# define STEP_SIZE 0.05

# ifndef ENEMY_RADIUS
#  define ENEMY_RADIUS (TILE_SIZE * 0.3)
# endif

/// shooting anim test

# define WEAPON_NEUTRE 0
# define WEAPON_PREFIRE 1
# define WEAPON_FIRE 2
# define WEAPON_POSTFIRE 1 // same image of PREFIRE

typedef struct s_game	t_game;

typedef struct s_weapon_state
{
	int current_state; // État actuel de l'arme
	int frame;         // Frame courante
	int frame_delay;   // Délai entre les frames
	int is_firing;     // Indique si l'arme est en train de tirer
}						t_weapon_state;

typedef struct s_health_bar
{
	int					x;
	int					y;
	int					width;
	int					height;
	int					border;
	unsigned int		border_color;
	unsigned int		empty_color;
	unsigned int		health_color;
}						t_health_bar;

typedef struct s_minimap
{
	int					size;
	int					x;
	int					y;
	int					cell_size;
	int					border;
	int visible_radius; // Nombre de cellules visibles autour du joueur
	int show;           // 1 = afficher, 0 = masquer

	unsigned int		border_color;
	unsigned int		bg_color;
	unsigned int		wall_color;
	unsigned int		door_color;
	unsigned int		portal_color;
	unsigned int		player_color;
	unsigned int		fov_color;
}						t_minimap;

typedef struct s_portal
{
	double				x;
	double				y;
	int					is_active;
	int					is_vertical;
	char				surface_type;
}						t_portal;

typedef struct s_portal_system
{
	t_portal			portals[2];
	int					portal_count;
	int					next_portal_index;
}						t_portal_system;

typedef struct s_img
{
	void				*ptr;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_img;

enum					e_enemy_state
{
	IDLE,
	SEARCH,
	MELEE,
	SHOOT,
	DEAD
};
typedef struct s_point
{
	int					x;
	int					y;
}						t_point;
typedef struct s_enemy
{
	double				x;
	double				y;
	double				angle;
	int					health;
	int					state;
	double				speed;
	int					cooldown;
	double				distance_to_player;
	t_img				*texture;
	double				distance;
	int					active;
	int					sees_player;
	int visible;
}						t_enemy;

typedef struct s_player
{
	double				x;
	double				y;
	double				angle;
	double				fov;
	int					move_speed;
	int					rot_speed;

	bool				key_down;
	bool				key_up;
	bool				key_right;
	bool				key_left;
	bool				left_rotate;
	bool				right_rotate;
	bool				turn_back;
	bool				left;
	bool				right;
	t_game				*game;
	int					current_weapon;
	int					health;
	int					is_firing;
	int					fire_cooldown;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;

	t_weapon_state		weapon;
}						t_player;

typedef struct s_intersect
{
	double				x;
	double				y;
	double				step_x;
	double				step_y;
}						t_intersect;

typedef struct s_env
{
	void				*mlx;
	void				*win;
	t_img				img;
}						t_env;

typedef struct s_map
{
	char				**matrix;
	int					width;
	int					height;
	t_img				enemy_texture;
	t_img				floor_texture;
	t_img				wall_texture;
	t_img				wall_shooted_texture;
	t_img				door_texture;
	t_img				door_shooted_texture;
	t_img				wall_portal_texture;
	t_img				arm_1;
	int					x_player;
	int					y_player;
}						t_map;

typedef struct s_ray
{
	double				radiant_angle;
	double				player_angle;
	double				distance;
	double				wall_hit_x;
	double				wall_hit_y;
	int					hit_vertical;
	char				hit_type;
	int					hit_enemy_idx;
	int					skip_wall;
}						t_ray;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	t_img				screen;
	t_map				map;
	t_player			player;
	t_img				weapons[MAX_WEAPONS][3];
	int					current_weapon;
	t_ray				rays[DISPLAY_WIDTH];
	double				depth_buffer[DISPLAY_WIDTH];

	t_enemy				*enemies;
	int					num_enemies;
	t_portal			portal_1;
	t_portal			portal_2;
	int					portal_count;
	int					pitch;
	t_minimap			minimap;
	t_health_bar		health_bar;
}						t_game;

typedef struct s_render
{
	/* Distance calculations and dimensions */
	double corrected_dist; // Wall distance corrected for fisheye effect
	int wall_height;       // Wall height on screen (in pixels)
	int door_height;       // Door height on screen (in pixels)
	/* Vertical rendering boundaries */
	int draw_start; // Starting pixel for vertical column rendering
	int draw_end;   // Ending pixel for vertical column rendering
	int					texture_offset_y;
	// Vertical texture offset for walls taller than screen
	/* Screen coordinates and iterators */
	int x; // Current horizontal position
	int y; // Current vertical position
	/* Texture coordinates */
	int tex_x;      // X coordinate in texture
	int tex_y;      // Y coordinate in texture
	char *tex_addr; // Address of pixel in texture data
	/* Floor rendering variables */
	double row_distance; // Distance to the pixel row being rendered
	double floor_x;      // Floor X coordinate in world space
	double floor_y;      // Floor Y coordinate in world space
	double dim_factor;   // Darkening factor based on distance
	/* Color management */
	unsigned int color; // Final pixel color
	unsigned int red;   // Red component
	unsigned int green; // Green component
	unsigned int blue;  // Blue component
	/* Screen pixel pointer */
	char *screen_pixel; // Destination pixel address on screen
}						t_render;

typedef struct s_sprite
{
	double				x;
	double				y;
	int					texture_id;
	double				distance;
	double				angle;
	double				size;
}						t_sprite;

t_intersect				v_intersection(int x_player, int y_player,
							double radiant_angle);

t_intersect				h_intersection(int x_player, int y_player,
							double radiant_angle);

int						is_not_wall(t_map *map, double x, double y);
int						calc_wall_height(double corrected_dist);
double					no_fish_eye(double min_distance, double radiant_angle,
							double player_angle);

void					render_column(t_game *game, int column_x, t_ray *ray);
void					render_frame(t_game *game);
double					ray_casting(t_game *game, double radiant_angle,
							int column_x);

int						set_player_pos(t_game *game);
int						read_map(char *file_path, t_game *game);
int						init_game(t_game *game, char *map_file);

int						check_file_cub(char *file_path);
int						validate_map(t_map *map);

int						init_game(t_game *game, char *map_file);

void					render_wall(t_game *game, int column_x, t_render *r,
							t_ray *ray);
void					render_floor(t_game *game, int column_x, t_render *r);
void					render_sky(t_game *game, int column_x, t_render *r);
void					render_weapon(t_game *game);
void					move_player(t_player *player);
void					init_player(t_player *player);
int						key_press(int keycode, t_player *player);
int						key_release(int keycode, t_player *player);

int						render_next_frame(t_game *game);
void					render_scene(t_game *game);
void					render_ui(t_game *game);
int						loop_game(t_game *game);
void					render_door(t_game *game, int column_x, t_render *r,
							t_ray *ray);
double					normalize_angle(double angle);
int						close_window(void *param);
void					draw_crosshair(t_game *game);
int						mouse_move(int x, int y, t_game *game);
int						mouse_button(int button, int x, int y, t_game *game);
void					calculate_shoot(t_game *game);
void					render_wall_portal(t_game *game, int column_x,
							t_render *renderer, t_ray *ray);
void					remove_all_portals(t_game *game);
void					draw_health_bar(t_game *game);
void					minimap(t_game *game);
void					init_minimap(t_game *game);
void					init_health_bar(t_game *game);
void					render_wall_shooted(t_game *game, int column_x,
							t_render *renderer, t_ray *ray);
void					render_door_shooted(t_game *game, int column_x,
							t_render *renderer, t_ray *ray);
int						enemy_sees_you(t_enemy *enemy, t_player *player,
							t_map *map);
int						line_of_sight(double ex, double ey, double px,
							double py, t_map *map);
void					update_enemy(t_enemy *enemy, t_player *player,
							t_map *map);
void					render_enemy(t_game *game, t_enemy *enemy);

void					draw_enemy_sprite(t_game *game, t_img *sprite,
							t_point pos, int size);
int						set_enemy_pos(t_game *game);
void					update_camera_vectors(t_player *player);
void					draw_minimap_cone(t_game *game);
t_enemy *get_enemy_at_tile(t_game *game, int tile_x, int tile_y);
double enemy_hit_by_ray(t_game *game, double ray_x, double ray_y, double radiant_angle, int *enemy_index);



#endif
