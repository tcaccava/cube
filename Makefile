NAME = cube3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I./
MLX_DIR = ./minilibx-linux
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm


UI_SRC = ui/minimap.c ui/minimap_player.c ui/health_bar.c ui/crosshair.c
CORE_SRC = core/main.c core/game_loop.c core/init_game.c core/texture_loader.c core/weapon_loader.c core/enemy_init.c core/enemy_init_2.c core/game_loop_2.c core/init_game_2.c core/texture_loader_2.c core/init_game_3.c
RAYCASTER_SRC = raycaster/raycasting.c raycaster/raycasting_2.c raycaster/raycasting_3.c raycaster/raycasting_4.c
MAP_SRC = map/file_utils.c map/map_reader.c map/map_validator.c map/player_spawn.c map/enemy_spawn.c map/map_parser_2.c map/map_parser_3.c
PLAYER_SRC = player/player_move.c player/player_move_2.c
ENEMY_SRC = enemy/enemy_core.c enemy/enemy_ai.c enemy/enemy_ai_2.c enemy/enemy_animation.c enemy/enemy_render.c enemy/enemy_sprite.c enemy/enemy_animations_2.c enemy/enemy_core_2.c enemy/enemy_render_2.c enemy/enemy_sprite_2.c
RENDER_SRC = render/render_core.c render/render_walls.c render/render_weapons.c render/render_floor.c
GNL_SRC = gnl/get_next_line.c gnl/get_next_line_utils.c
SHOOT_SRC = shoot/shoot.c
PORTAL_SRC = portal/portal.c
INIT_SRC = init/init_minimap.c init/init_health_bar.c

SRCS = $(CORE_SRC) $(RAYCASTER_SRC) $(MAP_SRC) $(PLAYER_SRC) $(RENDER_SRC) $(GNL_SRC) $(ENEMY_SRC) $(SHOOT_SRC) $(PORTAL_SRC) $(UI_SRC)

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
