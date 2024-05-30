NAME 	= 	cub3d

CC				= cc
CFLAGS 			= -Wall -Wextra -Werror -Wshadow -Wpedantic -g3

SRC_DIR = ./src
OBJ_DIR = ./obj

PARSER_DIR := $(SRC_DIR)/parser
ENGINE_DIR := $(SRC_DIR)/engine

SRCS 	:= 	$(SRC_DIR)/main.c 						       \
			$(SRC_DIR)/engine.c

OBJECTS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
LIB				= ./libft/libft.a
LIBFT_LOC		= libft
LIBFT_LIB		= libft/libft.a
LIBMLX = MLX42

UNAME_S := $(shell uname -s)
MLX_FLAGS =
ifeq ($(UNAME_S), Darwin)
    MLX_FLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(UNAME_S), Linux)
    MLX_FLAGS = -ldl -lglfw -pthread -lm
endif

HEADERS = -I include -I $(LIBFT_LOC)/include -I $(MLX_LOC)/include

all: mlx $(NAME)

$(NAME): $(OBJECTS)
	@$(MAKE) -C $(LIBFT_LOC)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJECTS) $(LIBMLX)/build/libmlx42.a $(LIB) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(HEADERS) -c $(CFLAGS) -o $@ $<

mlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX) && cd $(LIBMLX) && git checkout v2.3.3 && cmake -B build && cmake --build build -j4; \
	fi

clean:
	@$(MAKE) -s -C $(LIBFT_LOC) clean
	@$ rm -rf $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$ rm -rf MLX42
	@$(MAKE) -s -C $(LIBFT_LOC) fclean

re: fclean all

.PHONY: all clean fclean re mlx
