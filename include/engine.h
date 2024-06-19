/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   engine.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/29 22:00:03 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/20 01:05:15 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <stdbool.h>
# include <stdlib.h>
# include <math.h>

# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

// voor nu hardcoded zo dat ik mijn tracer kan checken
// komt later van de parser af
# define SCREENWIDTH 1024
# define SCREENHEIGHT 512
# define CELLSIZE 64

typedef struct s_vector
{
	double	row;
	double	col;
} t_vector;

typedef struct s_draw_info
{
	int		heigth;
	int		start;
	int		end;
}	t_draw_info;

typedef	struct	s_dda
{
	t_vector	plane;
	double		camera_col;
	t_vector	ray_dir;
	t_vector	delta_dist;
	t_vector	stepper;
	t_vector	side_dist;
	t_vector	pos;
	double		prep_wall;
	int			side;
	t_draw_info	line;
} t_dda;

typedef struct s_player
{
	t_vector	pos;
	t_vector	d_pos;
	float		angle;
	char		faceing;
}	t_player;

typedef struct s_mlx_state
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t	*mini_map;
}	t_mlx_state;

typedef struct s_map
{
	char	**map;
	size_t	max_row;
	size_t	max_col;
}	t_map;

typedef struct s_game_state
{
	t_player	*player;
	t_mlx_state	*mlx;
	t_dda		*dda;
	t_map		*map;
}	t_game_state;

bool	init_state(t_game_state *state);
bool	err_handler(const char *msg, t_game_state *state);

void	free_game_state(t_game_state *state);

void	 key_hook(void *param);

void	run_game(t_game_state *state);

void	print_player(t_player *player);
void	print_dda(t_dda *dda);
#endif
