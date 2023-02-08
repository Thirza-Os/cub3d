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

typedef struct s_textures
{
	char	*elements[SIZE];

}	t_textures;

void	print_error(char *message);
void	*ft_malloc_check(void *s);

void	parse_input(int argc, char *argv[]);
char	*get_next_line(int fd);

int		ft_isspace(char c);

#endif
