/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   engine.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/29 22:00:03 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/07/25 21:04:41 by lvan-gef      ########   odam.nl         */
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
# define SCREENWIDTH 640
# define SCREENHEIGHT 480
# define CELLSIZE 64

// typedef struct s_vector
// {
// 	double	row;
// 	double	col;
// } t_vector;
//
// typedef struct s_draw_info
// {
// 	int		heigth;
// 	int		start;
// 	int		end;
// }	t_draw_info;
//
// typedef	struct	s_dda
// {
// 	t_vector	plane;
// 	double		camera_col;
// 	t_vector	ray_dir;
// 	t_vector	delta_dist;
// 	t_vector	stepper;
// 	t_vector	side_dist;
// 	t_vector	pos;
// 	t_vector	dir;
// 	double		prep_wall;
// 	int			side;
// 	t_draw_info	line;
// } t_dda;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_coors_int
{
	int	x;
	int	y;
}	t_coors_int;

typedef struct s_draw_info
{
	int		heigth;
	int		start;
	int		end;
}	t_draw_info;

typedef struct s_dda
{
	double		plane_x;
	double		plane_y;
	t_vector	player_pos;
	t_vector	player_dir;
	double		camera_x;
	t_vector	ray_dir;
	t_coors_int	map_pos;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_map_x;
	int			step_map_y;
	double		side_dist_x;
	double		side_dist_y;
	int			current_side;
	double		prep_wall_dist;
	t_draw_info	line;
}	t_dda;


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

void	key_hook(void *param);

void	run_game(t_game_state *state);

void	print_player(t_player *player);
void	print_dda(t_dda *dda);

void	dda_loop(void *param);
void	draw_info_calc(t_game_state *state);
void	dda_per_x(t_game_state *game, int x);
bool	dda_init(t_game_state *state);

#endif
