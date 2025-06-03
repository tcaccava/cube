NAME = cube3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I./
MLX_DIR = ./minilibx-linux
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

UI_SRC = ui/minimap.c ui/minimap_2.c ui/minimap_3.c ui/minimap_player.c ui/health_bar.c ui/crosshair.c ui/health_bar_2.c 
CORE_SRC = core/main.c core/game_loop.c core/init_game.c core/texture_loader.c core/weapon_loader.c core/weapon_loader_2.c core/weapon_loader_3.c core/enemy_init.c core/enemy_init_2.c core/game_loop_2.c core/init_game_2.c core/texture_loader_2.c core/init_game_3.c
RAYCASTER_SRC = raycaster/ray_casting.c raycaster/ray_intersection.c raycaster/ray_collision.c raycaster/ray_utils.c
MAP_SRC = map/file_utils.c map/map_reader.c map/map_validator.c map/player_spawn.c map/enemy_spawn.c 
PLAYER_SRC = player/player_move.c player/movement/player_movement.c player/movement/player_rotation.c player/input/player_keyboard.c player/input/player_weapon_switch.c player/input/player_mouse.c player/pickup/player_pickup.c player/pickup/player_pickup_healgun.c player/utils/player_utils.c player/input/input_utils.c
ENEMY_SRC = enemy/enemy_core.c enemy/enemy_ai.c enemy/enemy_ai_utils.c enemy/enemy_ai_combat.c enemy/enemy_animation.c enemy/enemy_animation_load.c enemy/enemy_animation_death.c enemy/enemy_render.c enemy/enemy_sprite.c enemy/enemy_sprite_pixel.c enemy/enemy_core_2.c enemy/enemy_sprite_utils.c enemy/enemy_ai_helper.c enemy/enemy_render_utils.c
RENDER_SRC = render/render_core.c render/render_core_2.c render/render_weapons.c render/render_weapons_2.c render/render_floor.c render/render_weapon_pickups.c render/render_weapon_pickups_2.c render/render_weapon_pickups_3.c
GNL_SRC = gnl/get_next_line.c gnl/get_next_line_utils.c gnl/get_next_line_utils_extra.c
SHOOT_SRC = shoot/shoot_core.c shoot/shoot_portal.c shoot/shoot_raygun.c shoot/shoot_utils.c 
PORTAL_SRC = portal/portal_init.c portal/portal_create.c portal/portal_teleport.c portal/portal_utils.c portal/portal_cleanup.c portal/portal_utils2.c portal/portal_utils3.c
DOOR_SRC = door/door_core.c door/door_render.c door/door_render_2.c door/door_textures.c door/door_textures_2.c door/door_sprites.c door/door_utils.c door/door_utils_2.c
LASER_SRC = laser/laser.c laser/render_laser.c
HEAL_SRC = heal/heal_system.c heal/heal_animation.c heal/heal_render.c heal/heal_utils.c heal/heal_loader.c
WALLS_SRC = walls/wall_basic.c walls/wall_shot.c walls/wall_portal.c walls/wall_textures.c walls/wall_utils.c
WEAPON_SRC = weapon/weapon_core.c weapon/weapon_render.c weapon/weapon_utils.c weapon/weapon_loader.c weapon/weapon_pickcup_render_2.c weapon/weapon_render_2.c weapon/weapon_utils_2.c weapon/weapon_shoot_2.c
SRCS = $(CORE_SRC) $(RAYCASTER_SRC) $(MAP_SRC) $(PLAYER_SRC) $(RENDER_SRC) $(GNL_SRC) $(ENEMY_SRC) $(SHOOT_SRC) $(PORTAL_SRC) $(UI_SRC) $(DOOR_SRC) $(LASER_SRC) $(HEAL_SRC) $(WALLS_SRC)

OBJS = $(SRCS:.c=.o)
RM = rm -f

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re: fclean all
