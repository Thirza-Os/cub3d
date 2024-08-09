/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 03:50:36 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/09 03:50:38 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

# include "../MLX42/include/MLX42/MLX42.h"

# define X_SIDE 1
# define Y_SIDE 2

# define MOVESPEED 0.12
# define ROTSPEED 0.08

# define FORWARD 1
# define BACKWARD -1
# define LEFTWARD -1
# define RIGHTWARD 1
# define TURNLEFT -1
# define TURNRIGHT 1

# define SCR_WIDTH 1600
# define SCR_HEIGHT 1200

# define NORTH "NO"
# define EAST "EA"
# define SOUTH "SO"
# define WEST "WE"
# define FLOOR "F"
# define CEILING "C"

# define N_INDEX 0
# define S_INDEX 1
# define E_INDEX 2
# define W_INDEX 3
# define F_INDEX 4
# define C_INDEX 5

# define MAX_IMGS 4

typedef struct s_dvector
{
	double	col;
	double	row;
}	t_dvector;

typedef struct s_i_vector
{
	int	col;
	int	row;
}	t_ivector;

typedef struct s_draw_info
{
	int		heigth;
	int		start;
	int		end;
}	t_draw_info;

typedef struct s_player
{
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	size_t		row_size;
	size_t		col_size;
	t_dvector	player_pos;
	char		starting_dir;
	char		**map;
}	t_player;

typedef struct s_dda
{
	t_dvector	plane;
	t_dvector	player_pos;
	t_dvector	delta_dist;
	t_dvector	side_dist;
	t_ivector	map_pos;
	t_ivector	step_map;
	t_dvector	player_dir;
	t_dvector	ray_dir;
	double		camera_x;
	double		perp_wall_dist;
	int			current_side;
	t_draw_info	line;
	t_player	*player;
}	t_dda;

typedef struct s_mlx_state
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[4];
	uint32_t		**img_buffer;
}	t_mlx_state;

typedef struct s_program
{
	t_mlx_state	*mlx_state;
	t_dda		*dda;
	char		*paths[4];
}	t_program;

#endif
