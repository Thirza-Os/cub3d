#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define WHITESPACE "\10\11\12\13\14\15\40"

typedef enum e_tokens
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	SIZE
}	t_tokens;

const static char	*g_labels[SIZE] = {"NO", "SO", "WE", "EA", "F", "C"};

typedef struct s_rgb
{
	int	*red;
	int	*green;
	int	*blue;
}	t_rgb;

typedef struct s_vector
{
	int	width;
	int	height;
}	t_vector;

typedef struct s_program
{
	char		*textures[5];
	t_rgb		floor_rgb;
	t_rgb		ceiling_rgb;
	t_vector	max_xy;
}	t_program;


void	parse_input(int argc, char *argv[]);
char	*get_next_line(int fd);

// utils
void	print_error(char *message);
void	*ft_malloc_check(void *s);

// parser
void	parse_input(int argc, char *argv[]);

// tokenizer
char	**tokenize_input(char *argv);

// parse input
void	parse_file(char	**elements);

//parse utils
int	ft_atorgb(const char *str);
int	check_png(char *arg);
int	check_cub(char *arg);

#endif
