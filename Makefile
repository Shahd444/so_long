CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11
NAME = so_long
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

SRC = main.c\
	  cleanup.c\
	  keypress.c\
	  load_to_window.c\
	  map_main_check.c\
	  utils1.c\
	  utils2.c\
	  utils3.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

mlx:
	@$(MAKE) -C $(MLX_DIR)

$(NAME) : $(OBJ)  | libft mlx 
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) $(MLX) $(MLX_FLAGS)

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft mlx
