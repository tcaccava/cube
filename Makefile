NAME = cube3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I./
MLX_DIR = ./minilibx-linux
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

CORE_SRC = core/main.c core/game_loop.c core/init_game.c
RAYCASTER_SRC = raycaster/raycasting.c raycaster/ray_utils.c
MAP_SRC = map/map_parser.c
PLAYER_SRC = player/player_move.c
PNJ_SRC = pnj/enemy.c
RENDER_SRC = render/render.c render/render_env.c render/render_ui.c render/render_minimap.c render/render_health_bar.c
GNL_SRC = gnl/get_next_line.c gnl/get_next_line_utils.c
SHOOT_SRC = shoot/shoot.c
PORTAL_SRC = portal/portal.c
INIT_SRC = init/init_minimap.c init/init_health_bar.c

SRCS = $(CORE_SRC) $(RAYCASTER_SRC) $(MAP_SRC) $(PLAYER_SRC) $(RENDER_SRC) $(GNL_SRC) $(PNJ_SRC) $(SHOOT_SRC) $(PORTAL_SRC) $(INIT_SRC)

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
