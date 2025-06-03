/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:09:16 by tcaccava          #+#    #+#             */
/*   Updated: 2025/06/03 14:37:07 by abkhefif         ###   ########.fr       */
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
# define ESPACE 32
# define F 102
# define LEFT 65508
# define RIGHT 65363

#define HANDS 0
#define PORTALGUN 1  // G dans la carte
#define RAYGUN 2     // R dans la carte
#define HEALGUN 3 // H sur la carte 
#define MAX_WEAPONS 4

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

typedef struct s_texture_paths
{
	char				*north;
	char				*south;
	char				*east;
	char				*west;
}						t_texture_paths;

typedef struct s_scene_data
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color;
	int		ceiling_color;
	int		map_started;
	int		map_count;
}	t_scene_data;

typedef struct s_ray_hit_data
{
	double	distance;
	double	hit_x;
	double	hit_y;
	int		is_vertical;
	char	hit_type;
}	t_ray_hit_data;

typedef struct s_minimap_params
{
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;
}	t_minimap_params;

typedef struct s_pixel_data
{
	int				src_x;
	int				src_y;
	int				x;
	int				y;
	unsigned int	color;
}	t_pixel_data;


typedef struct s_heal_coords
{
	int	x;
	int	y;
	int	px;
	int	py;
}	t_heal_coords;

typedef struct s_game	t_game;


typedef struct s_laser
{
    double x;
    double y;
    int active;
    double distance_to_player;
} t_laser;

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
	int					map_x;
	int					map_y;
	int					orientation;
	int					direction;
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

typedef struct s_weapon_pickup
{
    double x;
    double y;
    int weapon_type; // RAYGUN ou PORTALGUN our HEAL GUN
    int active;
    t_img sprite;
    double distance_to_player;
} t_weapon_pickup;


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
}						t_enemy;

typedef struct s_player
{
	double				x;
	double				y;
	double				angle;
	double				fov;
	int					move_speed;
	double				rot_speed;
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
	bool				has_weapon[MAX_WEAPONS];
	int					healgun_ammo;    
	int healgun_heal_applied;    // Nombre de munitions
    int healgun_is_loaded;   // 1 si chargé, 0 si vide
	int healgun_anim_state;     // 0-4 (frame actuelle)
    int healgun_anim_timer;     // Timer pour chaque frame
    int healgun_animating;      // 1 si en cours d'animation
    int healgun_frame_duration;
	int healgun_anim_frame; // Frame actuelle de l'animation
}						t_player;

typedef struct s_intersect
{
	double				x;
	double				y;
	double				step_x;
	double				step_y;
}						t_intersect;

typedef struct s_ray_setup_data
{
	t_intersect	*v;
	t_intersect	*h;
	double		distances[2];
	char		types[2];
}	t_ray_setup_data;

typedef struct s_env
{
	void				*mlx;
	void				*win;
	t_img				img;
}						t_env;

typedef struct s_open_door
{
    double				x;
    double				y;
    int					active;
    t_img				sprite;
    double				distance_to_player;

	int orientation;
    double width;    // ✅ NOUVEAU : largeur de l'ouverture
    double start_x;  // ✅ NOUVEAU : début de l'ouverture
    double start_y; 
}						t_open_door;

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
	t_img				open_door_texture;
	t_img				open_door_shooted_texture;
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
	t_weapon_pickup		*weapon_pickup;
	int					num_weapon_pickup;
	t_open_door			*open_doors;
    int					num_open_doors;
	t_img healgun_frames[5];
	t_texture_paths texture_paths;
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

typedef struct s_shoot_params
{
	t_enemy	*enemy;
	double	player_x;
	double	player_y;
	double	ray_dir_x;
	double	ray_dir_y;
	t_ray	*center_ray;
}	t_shoot_params;

typedef struct s_weapon_pixel_data
{
	t_img	*sprite;
	t_point	pos;
	int		size;
	int		i;
	int		j;
	int		enemy_state;
}	t_weapon_pixel_data;

typedef struct s_los_data
{
	double				distance;
	double				step_x;
	double				step_y;
	double				x;
	double				y;
	double				traveled;
}						t_los_data;

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
//void					init_portals(t_game *game);
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
//int						load_weapon_textures(void *mlx,
//							t_img weapon_textures[3], int weapon_type);
// int						load_raygun(t_game *game);
// int						load_portalgun(t_game *game);
// int						load_all_weapons(t_game *game);
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
int						is_valid_playable_char(char c);
int						check_surrounding_spaces(t_map *map, int x, int y);

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
// // player/player_move.c
// int						key_release(int keycode, t_player *player);
// int						key_press(int keycode, t_player *player);
// int						mouse_move(int x, int y, t_game *game);
// int						is_wall(t_game *game, float x, float y);
// void					move_player(t_player *player);

// ========== RAYCASTER FUNCTIONS ==========
// raycaster/raycasting.c
t_intersect				v_intersection(int x_player, int y_player,
							double radiant_angle);
t_intersect				h_intersection(int x_player, int y_player,
							double radiant_angle);
int						is_not_wall(t_map *map, double x, double y);
double					normalize_angle(double angle);
char					get_hit_type(t_map *map, double x, double y);
void	store_ray_info(t_game *game, int column_x, t_ray_hit_data *hit_data);
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
void					draw_minimap_cells(t_game *game);
void					minimap(t_game *game);
void                    draw_minimap_cell(t_game *game, int positions[4]);

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
int line_of_sight(t_point enemy_pos, t_point player_pos, t_map *map);
int						damage_enemy_at_position(t_game *game, int tile_x,
							int tile_y, int damage);
void					update_camera_vectors(t_player *player);

// enemy/enemy_ai.c
void					idle(t_enemy *e, t_player *p, t_map *m);
void					search(t_enemy *e, t_player *p, t_map *m);
void					shoot(t_enemy *e, t_player *p, t_map *m);
void					melee(t_enemy *e, t_player *p, t_map *m);

// enemy/enemy_animation.c
void					update_death_animation(t_enemy *enemy);
void					update_enemy_animation(t_enemy *enemy);
int						load_enemy_animations(t_game *game, t_enemy *enemy);
int						load_death_animations(t_game *game, t_enemy *enemy);

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

// ========== SHOOT FUNCTIONS ==========
// shoot/shoot_core.c
void					calculate_shoot(t_game *game);
int						mouse_button(int button, int x, int y, t_game *game);
void					handle_left_click(t_game *game);
void					handle_scroll_wheel(t_game *game, int button);

// shoot/shoot_portal.c
void					handle_portal_shot(t_game *game, t_ray *center_ray);
int						calculate_portal_orientation(t_ray *center_ray);
void					create_portal_at_position(t_game *game, int map_x, int map_y, int orientation);
void					shoot_portalgun(t_game *game);

// shoot/shoot_raygun.c
void					handle_raygun_shot(t_game *game, t_ray *center_ray);
int						check_enemy_hit(t_game *game, t_ray *center_ray);
void					shoot_raygun(t_game *game);
void					start_raygun_animation(t_game *game);

// shoot/shoot_healgun.c
void					shoot_healgun(t_game *game);
int						validate_healgun_shot(t_game *game);
void					execute_healgun_shot(t_game *game);
void					handle_healgun_shot(t_game *game, t_ray *center_ray);

// shoot/shoot_utils.c
int						is_enemy_in_line_of_fire(t_game *game, t_shoot_params *params);
int						damage_enemy(t_enemy *enemy, t_game *game);
void					apply_wall_damage(t_game *game, t_ray *center_ray);
void					apply_damage_to_surface(t_game *game, char hit_type, int map_x, int map_y);

// shoot/shoot_portal_utils.c
void					create_new_portal_at_position(t_game *game, int map_x, int map_y, int orientation);
void					reset_and_create_portal_at_position(t_game *game, int map_x, int map_y, int orientation);
void					setup_portal_data(t_game *game, int map_x, int map_y, int orientation);
void					print_portal_creation(int portal_count, int map_x, int map_y, int orientation);
void					print_portal_reset(int map_x, int map_y, int orientation);


// ========== GNL FUNCTIONS ==========
// gnl/get_next_line.c
char					*get_next_line(int fd);

// gnl/get_next_line_utils.c
size_t					ft_strlen(const char *s);

// ========== WEAPON PICKUP FUNCTIONS ==========
// render/render_weapon_pickups.c
void render_weapon_pickup(t_game *game, t_weapon_pickup *weapon);
void calculate_weapon_transform(t_game *game, t_weapon_pickup *weapon, t_render *render);
void calculate_weapon_screen_pos(t_game *game, t_render *render);
void draw_weapon_pickup_sprite(t_game *game, t_img *sprite, t_point pos, int size);

// core/weapon_loader.c
//int load_weapon_pickup_sprite(t_game *game, t_weapon_pickup *pickup, char *path);
int count_weapons_in_map(t_game *game);
int set_weapon_positions(t_game *game);
//int load_weapon_pickup_sprites(t_game *game);
void disable_weapon_pickup_at_position(t_game *game, int map_x, int map_y, int weapon_type);
int	is_not_wall_for_movement(t_map *map, double x, double y);
int count_open_doors_in_map(t_game *game);
int load_open_door_sprites(t_game *game);
int set_open_door_positions(t_game *game);
void draw_open_door_sprite(t_game *game, t_img *sprite, t_point pos, int size);
void render_all_open_doors(t_game *game);
void render_door_columns(t_game *game, t_open_door *door, int col_start, int col_end, 
                        int door_top, int door_bottom, double distance);
int world_to_screen_column(t_game *game, double world_x, double world_y);
// Dans la section render functions
void render_open_door_as_sprite(t_game *game, t_open_door *door);
void draw_ultra_thin_door_sprite(t_game *game, t_img *sprite, t_point pos, int size);
// Dans les fonctions de rendu
void render_fixed_door_columns(t_game *game, t_open_door *door, int center_column, 
                              int door_width, int door_top, int door_bottom, double distance);
// Dans les fonctions de raycasting
void check_open_doors_on_ray(t_game *game, int column_x, double radiant_angle);
void render_door_on_column(t_game *game, t_open_door *door, int column_x, double distance);
int check_and_render_door_on_column(t_game *game, int column_x, t_ray *ray);
void render_door_column_fixed(t_game *game, t_open_door *door, int column_x, double distance);
double check_open_door_on_ray(t_game *game, double radiant_angle);

// Fonctions de rendu
void render_open_door_ultra_thin(t_game *game, int column_x, t_render *renderer, t_ray *ray);
void render_simple_door_line(t_game *game, int column_x, t_render *renderer);
t_open_door *find_door_at_position(t_game *game, int map_x, int map_y);
void render_open_door(t_game *game, int column_x, t_render *renderer, t_ray *ray);
void open_door(t_game *game);
void render_shooted_open_door(t_game *game, int column_x, t_render *renderer, t_ray *ray);

void render_laser_overlays(t_game *game);
void render_laser_overlay_on_column(t_game *game, int column_x);
int count_lasers_in_map(t_game *game);
int init_lasers(t_game *game);
void render_laser_sprite(t_game *game, t_laser *laser);
void draw_laser_lines(t_game *game, int start_col, int end_col, int top, int bottom, double depth);
void render_all_lasers(t_game *game);
int ray_crosses_laser(t_game *game, double radiant_angle);
void draw_laser_line_on_column(t_game *game, int column);
void use_healgun(t_game *game);
void render_healgun_animation(t_game *game);
void start_healgun_animation(t_game *game);
void update_healgun_animation(t_game *game);
int load_healgun(t_game *game);
void use_healgun(t_game *game);
int	load_single_weapon_texture(void *mlx, t_img *tex, char *path);



// ========== HEAL FUNCTIONS ==========
// heal/heal_system.c
void					use_healgun(t_game *game);
int						validate_healgun_use(t_game *game);
void					start_heal_process(t_game *game);
void					consume_heal_ammo(t_game *game);
void					apply_healing(t_game *game);

// heal/heal_animation.c
void					update_healgun_animation(t_game *game);
void					advance_heal_frame(t_game *game);
void					set_frame_durations(int frame_durations[5]);
void					finish_heal_animation(t_game *game);
void					set_next_frame_timer(t_game *game, int frame_durations[5]);

// heal/heal_render.c
void					render_healgun_animation(t_game *game);
void					draw_arm_sprite(t_game *game, t_img *sprite, int x, int y);
void					draw_arm_row(t_game *game, t_img *sprite, int x, int y, int row);
void					draw_arm_pixel(t_game *game, t_img *sprite, int x, int y, int px, int py);
int						is_transparent_pixel(unsigned int color);

// heal/heal_loader.c
int						load_healgun(t_game *game);
void					init_healgun_sprite_paths(const char *sprites[5]);
int						load_healgun_frame(t_game *game, int frame, const char *path);
void					check_reload_healgun(t_game *game);
void					start_healgun_animation(t_game *game);

// heal/heal_utils.c
int						is_pixel_in_bounds(int x, int y);
char					*get_sprite_pixel(t_img *sprite, int x, int y);
char					*get_screen_pixel(t_game *game, int x, int y);
void					init_healgun_animation(t_game *game);
int						is_healgun_ready(t_game *game);

// ========== PORTAL FUNCTIONS ==========
// portal/portal_init.c
void					init_portals(t_game *game);
void					init_portal_one(t_game *game);
void					init_portal_two(t_game *game);
void					setup_portal_one(t_game *game, int map_x, int map_y, int orientation);
void					setup_portal_two(t_game *game, int map_x, int map_y, int orientation);

// portal/portal_create.c
int						create_portal(t_game *game, int map_x, int map_y, int orientation);
int						create_new_portal(t_game *game, int map_x, int map_y, int orientation);
int						reset_and_create_portal(t_game *game, int map_x, int map_y, int orientation);
void					print_portal_created(int portal_num, int x, int y, int orientation);
void					print_portal_reset(int x, int y, int orientation);

// portal/portal_teleport.c
void					teleport_through_portal(t_game *game, int portal_x, int portal_y);
t_portal				*get_destination_portal(t_game *game, int portal_x, int portal_y);
void					execute_teleportation(t_game *game, t_portal *dest_portal);
int						calculate_exit_direction(t_portal *dest_portal);
void					emergency_teleport(t_game *game, t_portal *dest_portal);

// portal/portal_utils.c
char					*get_orientation_name(int orientation);
int						is_valid_map_position(t_game *game, int x, int y);
int						is_valid_teleport_position(t_game *game, int x, int y);
void					place_player_at_position(t_game *game, int x, int y);
int						try_teleport_at_direction(t_game *game, int dest_x, int dest_y, int dir);

// portal/portal_cleanup.c
void					remove_all_portals(t_game *game);
void					clear_portals_from_map(t_game *game);
void					reset_portal_states(t_game *game);
void					recalculate_rays(t_game *game);
void					update_ray_data(t_game *game, int i, double radiant_angle);

// portal/portal_utils2.c
void					init_adjacent_offsets(int adj_offsets[4][2]);
void					check_portal_teleportation(t_game *game);
void					check_nearby_portals(t_game *game, int player_x, int player_y);
void					init_check_offsets(int check_offsets[9][2]);
void					check_portal_at_offset(t_game *game, int player_x, int player_y, int offset[2]);
double					calculate_distance_to_portal(t_game *game, double portal_x, double portal_y);

// ========== WEAPON FUNCTIONS ==========
// weapon/weapon_init.c
void					init_player_weapons(t_player *player);
void					init_weapon_inventory(t_player *player);
void					init_weapon_state(t_player *player);
void					init_weapon_ammo(t_player *player);
int						load_all_weapons(t_game *game);

// weapon/weapon_loader.c
int						load_single_weapon_texture(void *mlx, t_img *tex, char *path);
int						load_weapon_textures(void *mlx, t_img weapon_textures[3], int weapon_type);
void					init_weapon_paths(const char paths[MAX_WEAPONS][3]);
void					init_hands_paths(const char paths[3]);
void					init_portalgun_paths(const char paths[3]);
void					init_raygun_paths(const char paths[3]);
void					init_healgun_paths(const char paths[3]);

// weapon/weapon_pickup.c
int						count_weapons_in_map(t_game *game);
int						is_weapon_cell(char cell);
int						load_weapon_pickup_sprites(t_game *game);
void					init_weapon_pickup_array(t_game *game);
int						load_weapon_pickup_sprite(t_game *game, t_weapon_pickup *pickup, char *path);
int						set_weapon_positions(t_game *game);

// weapon/weapon_shoot.c
int						mouse_button(int button, int x, int y, t_game *game);
void					handle_left_click(t_game *game);
void					shoot_raygun(t_game *game);
void					shoot_portalgun(t_game *game);
void					shoot_healgun(t_game *game);
void					calculate_shoot(t_game *game);

// weapon/weapon_render.c
void					render_weapon(t_game *game);
t_img					*get_current_weapon_sprite(t_game *game);
t_img					*get_healgun_sprite(t_game *game);
void					calculate_weapon_position(t_game *game, t_render *renderer, t_img *weapon);
int						is_healgun_frame_2(t_game *game);
void					update_weapon_animation(t_game *game);
void					draw_weapon_sprite(t_game *game, t_render *renderer, t_img *weapon);
void					draw_weapon_row(t_game *game, t_render *renderer, t_img *weapon);
void	draw_weapon_pixel(t_game *game, t_weapon_pixel_data *data);

// weapon/weapon_specific.c
int						load_hands(t_game *game);
void					setup_hands_texture(t_game *game, int width, int height);
int						load_raygun(t_game *game);
int						load_portalgun(t_game *game);
int						load_healgun(t_game *game);

// weapon/weapon_pickup_render.c
void					render_weapon_pickup(t_game *game, t_weapon_pickup *weapon);
int						should_skip_weapon_render(t_game *game, t_weapon_pickup *weapon);
int						setup_healgun_pickup_sprite(t_game *game, t_weapon_pickup *weapon);
void					calculate_weapon_transform(t_game *game, t_weapon_pickup *weapon, t_render *render);
void					calculate_weapon_screen_pos(t_game *game, t_render *render);
void					setup_weapon_pickup_render(t_game *game, t_render *renderer);
void					draw_weapon_pickup_sprite(t_game *game, t_img *sprite, t_point pos, int size);
// void					draw_weapon_pickup_pixel(t_game *game, t_img *sprite, t_point pos, int size, int i, int j);
// int						is_pickup_pixel_transparent(unsigned int color);

// weapon/weapon_utils.c
void					handle_scroll_wheel(t_game *game, int button);
void					switch_to_next_weapon(t_game *game);
void					switch_to_previous_weapon(t_game *game);
void					disable_weapon_pickup_at_position(t_game *game, int map_x, int map_y, int weapon_type);
int						is_weapon_at_position(t_weapon_pickup *weapon, int map_x, int map_y, int weapon_type);
void					setup_weapon_at_position(t_game *game, int x, int y, int *weapon_index);
void					setup_raygun_pickup(t_game *game, int index);
void					setup_portalgun_pickup(t_game *game, int index);
void					setup_healgun_pickup_weapon(t_game *game, int index);

// ========== DOOR FUNCTIONS ==========
// door/door_core.c
void	open_door(t_game *game);
void	calculate_door_check_position(t_game *game, double *check_x, double *check_y);
int		is_valid_door_position(t_game *game, int map_x, int map_y);
void	toggle_door_state(t_game *game, int map_x, int map_y, char cell);
t_open_door	*find_door_at_position(t_game *game, int map_x, int map_y);

// door/door_render.c  
void	render_door(t_game *game, int column_x, t_render *renderer, t_ray *ray);
void	render_open_door(t_game *game, int column_x, t_render *renderer, t_ray *ray);
void	calculate_door_texture_coordinates(t_render *renderer, t_ray *ray);
double	get_position_in_cell(t_ray *ray);
int		is_door_frame_position(double pos_in_cell);

// door/door_textures.c
int		load_door_textures(t_game *game);
int		load_closed_door_texture(t_game *game);
int		load_open_door_texture(t_game *game);
int		load_shot_door_textures(t_game *game);
void	setup_texture_data(t_img *texture, int width, int height);

// door/door_sprites.c
int		load_open_door_sprites(t_game *game);
void	init_open_door_array(t_game *game);
int		count_open_doors_in_map(t_game *game);
int		load_all_door_sprites(t_game *game);
int		set_open_door_positions(t_game *game);

// door/door_utils.c
void	render_door_column(t_game *game, int column_x, t_render *renderer);
int		calculate_texture_y(t_render *renderer, int cy, double h);
void	render_door_pixel(t_game *game, int column_x, t_render *renderer, int texture_y);
void	setup_door_at_position(t_game *game, int x, int y, int *door_index);
int		load_single_door_sprite(t_game *game, int index);

// door/door_textures_2.c
int		load_door_shooted_texture(t_game *game);
int		load_open_door_shooted_texture(t_game *game);

// ========== WALLS FUNCTIONS ==========
// walls/wall_basic.c
void    render_wall(t_game *game, int column_x, t_render *renderer, t_ray *ray);

// walls/wall_shot.c  
void    render_wall_shooted(t_game *game, int column_x, t_render *renderer, t_ray *ray);

// walls/wall_portal.c
void    render_wall_portal(t_game *game, int column_x, t_render *renderer, t_ray *ray);

// walls/wall_textures.c
t_img   *get_wall_texture(t_game *game, t_ray *ray);

// walls/wall_utils.c
int     calculate_texture_y_from_position(int y, int cy, double h);
void    set_wall_pixel_color(t_game *game, int x, int y, unsigned int color);

void	render_shooted_open_door(t_game *game, int column_x, t_render *renderer, t_ray *ray);
void	apply_damage_effect(unsigned int color, unsigned int *damaged_color);

// ========== PLAYER FUNCTIONS ==========
// player/player_move.c (coordinateur principal)
void					move_player(t_player *player);

// player/movement/player_movement.c
void					move_forward(t_player *player, float speed);
void					move_backward(t_player *player, float speed);
void					move_strafe_left(t_player *player, float speed);
void					move_strafe_right(t_player *player, float speed);
void					process_movement_keys(t_player *player);

// player/movement/player_rotation.c
void					rotate_left(t_player *player, float angle_speed);
void					rotate_right(t_player *player, float angle_speed);
void					turn_around(t_player *player);
void					normalize_player_angle(t_player *player);
void					process_rotation_keys(t_player *player);

// player/input/player_keyboard.c
int						key_press(int keycode, t_player *player);
int						key_release(int keycode, t_player *player);
void					handle_movement_keys_press(int keycode, t_player *player);
void					handle_movement_keys_release(int keycode, t_player *player);
void					handle_rotation_keys_press(int keycode, t_player *player);

// player/input/player_weapon_switch.c
void					handle_weapon_keys_press(int keycode, t_player *player);
void					switch_to_hands(t_player *player);
void					switch_to_raygun(t_player *player);
void					switch_to_portalgun(t_player *player);
void					switch_to_healgun(t_player *player);

// player/input/player_mouse.c
int						mouse_move(int x, int y, t_game *game);
void					apply_mouse_rotation(t_game *game, int delta_x, int delta_y);
void					clamp_pitch(t_game *game);
void					handle_rotation_keys_release(int keycode, t_player *player);

// player/pickup/player_pickup.c
void					check_weapon_pickup(t_player *player);
void					process_weapon_pickup(t_player *player, char cell_type, int map_x, int map_y);
void					pickup_raygun(t_player *player, int map_x, int map_y);
void					pickup_portalgun(t_player *player, int map_x, int map_y);
void					pickup_healgun(t_player *player, int map_x, int map_y);

// player/pickup/player_pickup_healgun.c
void					pickup_healgun_first_time(t_player *player, int map_x, int map_y);
void					pickup_healgun_ammo(t_player *player, int map_x, int map_y);
void					reload_healgun_if_empty(t_player *player);
int						is_valid_pickup_position(t_game *game, int map_x, int map_y);
void					handle_action_keys_press(int keycode, t_player *player);

// player/utils/player_utils.c
int						is_wall(t_game *game, float x, float y);
void					update_player_position(t_player *player);
int						validate_player_game(t_player *player);
int						can_move_to_position(t_game *game, float x, float y);
void					apply_movement_bounds(t_player *player, float *new_x, float *new_y);

void					init_laser_positions(int *positions, int center_y);
void	draw_weapon_pixel_at_coords(t_game *game, t_img *weapon, t_render *renderer);
void	draw_crosshair(t_game *game);
void	draw_cell_pixels(t_game *game, t_minimap *mini_map,
		unsigned int cell_color, int coords[4]);
int	is_valid_screen_pixel(t_minimap *mini_map, int screen_pixel_x,
		int screen_pixel_y);
unsigned int	get_cell_color(t_minimap *mini_map, char cell_type);
void	calculate_weapon_transform(t_game *game, t_weapon_pickup *weapon,
		t_render *render);
void	render_weapon_pickup(t_game *game, t_weapon_pickup *weapon);
int		should_skip_weapon_render(t_game *game, t_weapon_pickup *weapon);
void	calculate_weapon_screen_pos(t_game *game, t_render *render);
void	draw_weapon_pickup_sprite(t_game *game, t_img *sprite, t_point pos,
			int size);
void	draw_weapon_pickup_pixel(t_game *game, t_weapon_pixel_data *data);

// render/render_weapons.c  
void	update_weapon_animation(t_game *game);
void	render_weapon(t_game *game);
void	render_shooted_door_column(t_game *game, t_render *renderer,
			int column_x);
			void    init_player_basics(t_player *player);
void    init_player_weapons(t_player *player);
void	draw_weapon_pixel_render(t_game *game, t_img *weapon, t_render *renderer);
void	draw_weapon_pickup_row(t_game *game, t_weapon_pixel_data *data);
void	calculate_pickup_src_coords(t_weapon_pixel_data *data, int src_coords[2]);
unsigned int	get_pickup_pixel_color(t_img *sprite, int src_coords[2]);
int		is_pickup_pixel_transparent(unsigned int color);
int		is_valid_screen_coord(int coords[2]);
void	set_pickup_pixel_color(t_game *game, int coords[2], unsigned int color);
void	setup_weapon_pickup_render(t_game *game, t_render *renderer);

// enemy/enemy_ai_utils.c
void	apply_random_rotation(t_enemy *e);
void	set_search_state(t_enemy *e);
void	set_melee_state(t_enemy *e);
void	set_shoot_state(t_enemy *e);
void	move_towards_player(t_enemy *e, t_player *p, t_map *m, double angle);
// enemy/enemy_ai_combat.c
void	handle_shoot_cooldown(t_enemy *e, t_player *p);
void	handle_melee_cooldown(t_enemy *e, t_player *p);
void	handle_old_enemy_position(t_game *game, int old_map_x, int old_map_y);

// enemy/enemy_ai_position.c  
void	update_enemy_position_on_map(t_game *game, t_enemy *enemy, double old_x, double old_y);
// enemy/enemy_render_utils.c
void    calculate_enemy_transform(t_game *game, t_enemy *enemy, t_render *render);
void    calculate_enemy_screen_pos(t_game *game, t_render *render);
int     check_enemy_occlusion(t_game *game, t_render *render);
void    setup_enemy_render_params(t_game *game, t_render *render);
int	calculate_sprite_bounds(t_render *render, int *start, int *end);

void	draw_enemy_sprite(t_game *game, t_img *sprite, t_render *renderer, t_enemy *enemy);
void	render_death_animation(t_game *game, t_enemy *enemy);

// enemy/enemy_sprite_pixel.c
void	draw_sprite_pixel_at_pos(t_game *game, t_weapon_pixel_data *data);

// enemy/enemy_sprite_utils.c
t_img	*get_death_sprite(t_enemy *enemy);
int		setup_death_render(t_game *game, t_enemy *enemy, t_render *renderer);
void	apply_death_modifiers(t_enemy *enemy, t_render *renderer);
int		validate_death_render(t_render *renderer);
void	finalize_death_render(t_game *game, t_render *renderer);

// enemy/enemy_sprite_debug.c
void	print_death_debug(t_enemy *enemy, t_render *renderer);

double	calculate_distance_to_weapon(t_game *game, t_weapon_pickup *weapon);

int	parse_cub_file(char *filename, t_game *game);
int	process_line(char *line, t_scene_data *scene, t_game *game);
int	parse_texture(char *path_str, char **texture_path);
int	parse_color(char *color_str, int *color);
int	add_map_line(char *line, t_game *game, t_scene_data *scene);
int	validate_and_load_scene(t_scene_data *scene, t_game *game);



#endif
