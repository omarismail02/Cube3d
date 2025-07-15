NAME = cub3D
FLAGS = -Wall -Werror -Wextra -g

# Directories
LIBFT = libft
MLX = minilibx-linux  # At project root, NOT inside lib

# Lib Includes and Flags
LIB_INCLUDE = -I$(LIBFT) -I$(MLX)

# Linker flags
LIB_FLAGS = -L$(LIBFT) -lft -L$(MLX) -lmlx -lXext -lX11 -lm -lz

# Source files
SRC_FILES = \
	parsing/input.c \
	parsing/input_helpers.c \
	parsing/color.c \
	parsing/map.c \
	parsing/map_validation.c \
	parsing/main.c \
	parsing/utils.c \
	raycasting/render.c \
	raycasting/render_init.c \
	raycasting/vector_functions.c \
	raycasting/bres_algo.c \
	raycasting/image_buffer_functions.c \
	raycasting/map2d_functions.c \
	raycasting/map2d_functions_utils.c \
	raycasting/dda_algo.c \
	raycasting/utils.c \
	raycasting/projection3d.c \
	raycasting/colour_functions.c

GNL_DIR = get_next_line/
GNL = get_next_line.c \
	  get_next_line_utils.c

OBJ_SRC = $(SRC_FILES:.c=.o)
OBJ_UTILS = $(UTILS:%.c=$(UTILS_DIR)%.o)
OBJ_GNL = $(GNL:%.c=$(GNL_DIR)%.o)

OBJ_FILES = $(OBJ_SRC) $(OBJ_UTILS) $(OBJ_GNL)


# Main rule
all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MLX)
	$(CC) $(FLAGS) $(OBJ_FILES) -o $(NAME) $(LIB_INCLUDE) $(LIB_FLAGS)

# Pattern rule for compilation
%.o: %.c
	$(CC) $(FLAGS) $(LIB_INCLUDE) -c $< -o $@

# Clean rules
clean:
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(MLX) clean
	rm -f $(OBJ_FILES)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	$(MAKE) -C $(MLX) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
