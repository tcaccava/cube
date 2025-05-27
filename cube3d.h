/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:09:16 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:14:49 by tcaccava         ###   ########.fr       */
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

# define WEAPON_NEUTRE 0
# define WEAPON_PREFIRE 1
# define WEAPON_FIRE 2
# define WEAPON_POSTFIRE 1

# define ANIMATION_SPEED 6

// ========== STRUCTURES ==========
typedef struct s_game	t_game;

typedef struct s_enemy_animation
{
	int					current_frame;
	int					frame_counter;
}						t_enemy_animation;

typedef struct s_weapon_state
{
	int					current_state;
	int					frame;
	int					frame_delay;
	int					is_firing;
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
	int					visible_radius;
	int					show;
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
	t_img				walk_morty[2];
	t_img				shoot_morty[2];
	t_img				death_morty[3];
	double				distance;
	int					active;
	int					sees_player;
	t_enemy_animation	animation;
	int					last_state;
	int					frame_counter;
	int					sprite_size;
	int					death_timer;
	int					shooting;
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
	t_img				north;
	t_img				south;
	t_img				west;
	t_img				east;
	int					floor_color;
	int					sky_color;
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
	double				corrected_dist;
	int					wall_height;
	int					door_height;
	int					draw_start;
	int					draw_end;
	int					texture_offset_y;
	int					x;
	int					y;
	int					tex_x;
	int					tex_y;
	char				*tex_addr;
	double				row_distance;
	double				floor_x;
	double				floor_y;
	double				dim_factor;
	unsigned int		color;
	unsigned int		red;
	unsigned int		green;
	unsigned int		blue;
	char				*screen_pixel;
	int					sprite_size;
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

typedef struct s_enemy_sprites
{
	t_img				walk[2];
	t_img				shoot[2];
	t_img				death[3];
}						t_enemy_sprites;

typedef struct s_texture_paths
{
	char				*north;
	char				*south;
	char				*east;
	char				*west;
}						t_texture_paths;

typedef struct s_enemy_ctx
{
	t_enemy				*enemy;
	t_player			*player;
	t_map				*map;
	double				dx;
	double				dy;
	double				distance;
}						t_enemy_ctx;

typedef struct s_los_args
{
	double				ex;
	double				ey;
	double				px;
	double				py;
}						t_los_args;

typedef struct s_sprite_info
{
	t_game		*game;
	t_img		*sprite;
	t_point		pos;
	int			size;
	t_enemy		*enemy;
}	t_sprite_info;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;
// ========== CORE FUNCTIONS ==========
// core/main.c
void					init_player(t_player *player);
void					init_rays(t_game *game);
int						init_game_mode(t_game *game, int argc, char **argv);

// core/game_loop.c
int						close_window(void *param);
int						render_next_frame(t_game *game);
int						loop_game(t_game *game);

// core/game_init.c
int						init_mlx_window(t_game *game);
int						init_map_and_player(t_game *game, char *map_file);
void					init_portals(t_game *game);
void					init_ui_components(t_game *game);
int						init_game(t_game *game, char *map_file);

// core/texture_loader.c
int						load_basic_textures(t_game *game);
int						load_door_textures(t_game *game);
int						load_special_textures(t_game *game);
int						load_directional_textures(t_game *game,
							t_texture_paths *paths);
int						load_all_textures(t_game *game);

// core/weapon_loader.c
int						load_weapon_textures(void *mlx,
							t_img weapon_textures[3], int weapon_type);
int						load_raygun(t_game *game);
int						load_portalgun(t_game *game);
int						load_all_weapons(t_game *game);
int						init_game_with_4_textures(t_game *game, char *map_file,
							t_texture_paths *paths);
// core/enemy_init.c
int						count_enemies_in_map(t_game *game);
int						load_shared_enemy_sprites(t_game *game,
							t_img shared_sprites[2]);
int						load_shared_shoot_sprites(t_game *game,
							t_img shared_sprites[2]);
int						load_shared_death_sprites(t_game *game,
							t_img shared_sprites[3]);
int						init_all_enemies(t_game *game);

// ========== MAP FUNCTIONS ==========
// map/file_utils.c
int						check_file_cub(char *file_path);
int						count_file_lines(char *file_path);
int						calculate_map_width(t_game *game);
int						allocate_map_matrix(t_game *game, int line_count);
void					clean_line_ending(char *line);

// map/map_reader.c
int						read_map_lines(char *file_path, t_game *game);
int						set_map_dimensions(t_game *game, int line_count);
int						read_map(char *file_path, t_game *game);

// map/map_validator.c
int						check_borders(t_map *map);
int						is_valid_playable_char(char c);
int						check_surrounding_spaces(t_map *map, int x, int y);
int						check_playable_spaces(t_map *map);
int						validate_map(t_map *map);

// map/player_spawn.c
int						is_player_spawn(char c);
void					set_player_angle(t_player *player, char direction);
void					set_player_position(t_game *game, int x, int y,
							char direction);
int						set_player_pos(t_game *game);

// map/enemy_spawn.c
void					init_enemy_stats(t_enemy *enemy);
void					set_enemy_position(t_enemy *enemy, int x, int y);
int						place_enemy_at_position(t_game *game, int x, int y,
							int *enemy_index);
int						set_enemy_pos(t_game *game);

// ========== PLAYER FUNCTIONS ==========
// player/player_move.c
int						key_release(int keycode, t_player *player);
int						key_press(int keycode, t_player *player);
int						mouse_move(int x, int y, t_game *game);
int						is_wall(t_game *game, float x, float y);
void					move_player(t_player *player);

// ========== RAYCASTER FUNCTIONS ==========
// raycaster/raycasting.c
t_intersect				v_intersection(int x_player, int y_player,
							double radiant_angle);
t_intersect				h_intersection(int x_player, int y_player,
							double radiant_angle);
int						is_not_wall(t_map *map, double x, double y);
double					normalize_angle(double angle);
char					get_hit_type(t_map *map, double x, double y);
void					store_ray_info(t_game *game, int column_x,
							double distance, double hit_x, double hit_y,
							int is_vertical, char hit_type);
double					ray_casting(t_game *game, double radiant_angle,
							int column_x);
double					no_fish_eye(double min_distance, double radiant_angle,
							double player_angle);
int						calc_wall_height(double corrected_dist);

// raycaster/ray_utils.c
// (actuellement vide)

// ========== RENDER FUNCTIONS ==========
// render/render_core.c
void					render_column(t_game *game, int column_x, t_ray *ray);
void					render_scene(t_game *game);
void					render_frame(t_game *game);
void					render_ui(t_game *game);
void					render_next_frame_enemies(t_game *game);

// render/render_walls.c
t_img					*get_wall_texture(t_game *game, t_ray *ray);
void					render_wall(t_game *game, int column_x,
							t_render *renderer, t_ray *ray);
void					render_door(t_game *game, int column_x,
							t_render *renderer, t_ray *ray);
void					render_wall_portal(t_game *game, int column_x,
							t_render *renderer, t_ray *ray);
void					render_wall_shooted(t_game *game, int column_x,
							t_render *renderer, t_ray *ray);

// render/render_weapons.c
void					update_weapon_animation(t_game *game);
void					draw_weapon_pixel(t_game *game, t_img *weapon,
							t_render *renderer, int tex_x, int tex_y);
void					render_weapon(t_game *game);

// render/render_floor.c
void					render_ceiling(t_game *game, int column_x,
							t_render *renderer);
void					render_floor_section(t_game *game, int column_x,
							t_render *renderer);
void					render_floor_and_ceiling(t_game *game, int column_x,
							t_render *renderer);
void					render_door_shooted(t_game *game, int column_x,
							t_render *renderer, t_ray *ray);

// ========== UI FUNCTIONS ==========
// ui/minimap.c
void					init_minimap(t_game *game);
void					draw_minimap_background(t_game *game);
void					draw_minimap_cell(t_game *game, int map_x, int map_y,
							int screen_x, int screen_y);
void					draw_minimap_cells(t_game *game);
void					minimap(t_game *game);

// ui/minimap_player.c
void					draw_minimap_cone(t_game *game);
void					draw_player_circle(t_game *game, int center_x,
							int center_y);
void					draw_minimap_player(t_game *game);

// ui/health_bar.c
void					init_health_bar(t_game *game);
void					draw_health_bar_border(t_game *game);
void					draw_health_bar_background(t_game *game);
void					draw_health_bar_fill(t_game *game);
void					draw_health_bar(t_game *game);

// ui/crosshair.c
void					draw_crosshair_line(t_game *game, int center_x,
							int center_y, int size, unsigned int color,
							int is_vertical);
void					draw_crosshair(t_game *game);

// ========== ENEMY FUNCTIONS ==========
// enemy/enemy_core.c

void					update_enemy(t_enemy *enemy, t_player *player,
							t_map *map);

int						enemy_sees_you(t_enemy *enemy, t_player *player,
							t_map *map);
int						line_of_sight(t_los_args pos, t_map *map);
int						damage_enemy_at_position(t_game *game, int tx, int ty,
							int dmg);

void					update_camera_vectors(t_player *player);

// enemy/enemy_ai.c
void					idle(t_enemy_ctx *ctx);
void					search(t_enemy_ctx *ctx);
void					shoot(t_enemy_ctx *ctx);
void					melee(t_enemy_ctx *ctx);
void					update_enemy_position_on_map(t_game *game,
							t_enemy *enemy, double old_x, double old_y);

// enemy/enemy_animation.c
void					update_death_animation(t_enemy *enemy);
void					update_enemy_animation(t_enemy *enemy);
void					load_enemy_animations_part1(t_game *game,
							t_enemy *enemy);
void					load_enemy_animations_part2(t_game *game,
							t_enemy *enemy);
int						load_death_animations_part1(t_game *game,
							t_enemy *enemy);
int						load_death_animations_part2(t_game *game,
							t_enemy *enemy);

// enemy/enemy_render.c
void					render_enemy(t_game *game, t_enemy *enemy);
void					calculate_enemy_transform(t_game *game, t_enemy *enemy,
							t_render *render);
void					calculate_enemy_screen_pos(t_game *game,
							t_render *render);
int						check_enemy_occlusion(t_game *game, t_render *render);
void					setup_enemy_render_params(t_game *game,
							t_render *render);
void					render_death_animation(t_game *game, t_enemy *enemy);

// enemy/enemy_sprite.c

void	draw_sprite_pixel(t_sprite_info *info, int i, int j);
void	draw_enemy_sprite(t_sprite_info *info);
void	render_enemy_sprite(t_game *game, t_img *sprite,
			t_render *renderer, t_enemy *enemy);

// ========== WEAPON FUNCTIONS ==========
// shoot/shoot.c
void					calculate_shoot(t_game *game);
int						mouse_button(int button, int x, int y, t_game *game);

// ========== PORTAL FUNCTIONS ==========
// portal/portal.c
void					remove_all_portals(t_game *game);

// ========== GNL FUNCTIONS ==========
// gnl/get_next_line.c
char					*get_next_line(int fd);

// gnl/get_next_line_utils.c
size_t					ft_strlen(const char *s);

#endif