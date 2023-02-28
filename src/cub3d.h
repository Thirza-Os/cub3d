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

# define VALID_MAP_CHARS "10\n "

# define PLAYER_POS "NSEW"

typedef enum e_player_pos
{
	N,
	S,
	W,
	E,
}	t_players_pos;

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

const static char	*g_positions[4] = {"N", "S", "W", "E"};

const static char	*g_labels[SIZE] = {"NO", "SO", "WE", "EA", "F", "C"};

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_program
{
	char			*textures[5];
	mlx_texture_t	*mlx_textures[4];
	int				floor_rgb[3];
	int				ceiling_rgb[3];
	char			**map;
	t_vector		max_xy;
	t_vector		start_pos;
	int				spawning_pos;
}	t_program;

// utils
void		print_error(char *message);
void		*ft_malloc_check(void *s);

// parser
void		parser(char *argv[]);
char		**tokenize_input(char *argv);
char		*get_next_line(int fd);
void		validate_nr_of_identifiers(char **elements);
void		validate_rgb_input(char **elements, t_program *program);
void		validate_structure_paths(char **elements, t_program *program);
void		validate_map(char *map, t_program *program);
void		check_surrounded_walls(t_program *program);
//parse utils
int			ft_atorgb(const char *str);
int			check_png(char *arg);
int			check_cub(char *arg);
// mlx_processing
void		extract_mlx_pixels(t_program program);
uint32_t	get_pixel(double x, double y, mlx_texture_t *texture);

#endif
