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

typedef struct	s_vector
{
	int	width;
	int	height;
}	t_vector;

typedef struct s_program
{
	char		*texture[5];
	char		*colors[2];
	t_vector	max_xy;
}	t_program;

void	print_error(char *message);
void	*ft_malloc_check(void *s);

void	parse_input(int argc, char *argv[]);
char	*get_next_line(int fd);

int		ft_isspace(char c);
char	**ft_free_narr(char **arr, size_t len);
char	*ft_strjoin_free_cub3d(char const *s1, char const *s2);

#endif
