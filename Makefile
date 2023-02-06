NAME 	= 	cub3d

SRCS 	= 		src/main.c 				\
				src/utils.c				\
				src/parse_input.c		\
				src/parse_utils.C		\
				src/get_next_line.c		\
				src/get_next_line_utils.c 

LIB				= ./libft/libft.a
LIBFT_LOC		= libft
LIBFT_LIB		= libft/libft.a
MLX_LOC			= MLX42
MLX_LIB			= MLX42/libmlx42.a
MLX_FLAGS		= -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
CFLAGS 			= -Wall -Wextra
CC				= gcc
# HEADER 			= src/cub3d.h

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	@echo "\033[0;33mCompiling..."
	@$(MAKE) -s -C $(LIBFT_LOC)
	@$(MAKE) -s -C $(MLX_LOC)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJECTS) $(MLX_LIB) $(LIB) -o $(NAME)
	@echo "\033[0m"

%.o : %.c
	@echo "\033[0;32mGenerating obj..."
	@$(CC) $(CFLAGS) -Imlx -c -o $@ $<
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	@$(RM) $(OBJECTS)
	@$(MAKE) -s -C $(dir $(LIB)) clean
	@$(MAKE) -s -C $(MLX_LOC) clean
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(dir $(LIB)) fclean
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re
