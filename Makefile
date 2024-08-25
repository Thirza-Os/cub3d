NAME := cub3d

CC              = cc
CFLAGS          = -Wall -Wextra -Werror -Wshadow -Wpedantic -g3

SRC_DIR = ./src
ENG_DIR = $(SRC_DIR)/engine
PAR_DIR = $(SRC_DIR)/parser
OBJ_DIR = ./obj

SRCS    :=  $(SRC_DIR)/main.c\
            $(SRC_DIR)/cub_free.c\
            $(SRC_DIR)/parser_free.c\
            $(SRC_DIR)/utils.c\
			$(ENG_DIR)/buffer.c\
            $(ENG_DIR)/dda_calc.c\
            $(ENG_DIR)/render.c\
            $(ENG_DIR)/init_mlx.c\
            $(ENG_DIR)/textures.c\
            $(ENG_DIR)/hooks.c\
			$(PAR_DIR)/parser.c\
			$(PAR_DIR)/parse_utils.c\
			$(PAR_DIR)/validate_identifiers.c\
			$(PAR_DIR)/validate_ident_utils.c\
			$(PAR_DIR)/validate_map.c\
			$(PAR_DIR)/validate_map_utils.c\
			$(PAR_DIR)/validate_map_surrounded.c\
			$(PAR_DIR)/tokenize_input.c\
			$(PAR_DIR)/tokenize_utils.c\

OBJECTS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

LIB             = ./libft/libft.a
LIBFT_LOC       = libft
LIBFT_LIB       = libft/libft.a
LIBMLX = MLX42

UNAME_S := $(shell uname -s)
MLX_FLAGS =
ifeq ($(UNAME_S), Darwin)
    MLX_FLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(UNAME_S), Linux)
    MLX_FLAGS = -ldl -lglfw -pthread -lm
else
	$(error "Unsupported operating system: $(UNAME_S). Only macOS and Linux are supported.")
endif

HEADERS = -I include -I $(LIBFT_LOC)/include -I $(LIBMLX)/include

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBMLX)/build/libmlx42.a
	@$(MAKE) -C $(LIBFT_LOC)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJECTS) $(LIBMLX)/build/libmlx42.a $(LIB) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(LIBMLX)/build/libmlx42.a
	@mkdir -p $(@D)
	$(CC) $(HEADERS) -MMD -MP -c $(CFLAGS) -o $@ $<

$(LIBMLX)/build/libmlx42.a:
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

-include $(DEPS)
.PHONY: all clean fclean re
