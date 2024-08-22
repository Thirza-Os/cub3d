/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:25 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/22 15:52:38 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

# include <stdint.h>
# include <stdlib.h>

# include "../MLX42/include/MLX42/MLX42.h"

# define COL_SIDE 1
# define ROW_SIDE 2

# define MOVESPEED 0.10
# define ROTSPEED 0.03

# define FORWARD 1
# define BACKWARD -1
# define LEFTWARD -1
# define RIGHTWARD 1
# define TURNLEFT -1
# define TURNRIGHT 1

# define SCR_WIDTH 800
# define SCR_HEIGHT 600

# define MAX_IMGS 4
# define PLAYER_POS "NSEW"
# define VALID_MAP_CHARS "10\n "
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

typedef struct s_dvector
{
	double	col;
	double	row;
}	t_dvector;

typedef struct s_ivector
{
	int	col;
	int	row;
}	t_ivector;

typedef struct s_draw_info
{
	int	heigth;
	int	start;
	int	end;
}	t_draw_info;

typedef struct s_player
{
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_ivector	max_map;
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
	t_ivector	max_map;
	double		camera_x;
	double		perp_wall_dist;
	int			current_side;
	t_draw_info	line;
}	t_dda;

typedef struct s_mlx_state
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[MAX_IMGS];
	uint32_t		**img_buffer;
}	t_mlx_state;

typedef struct s_program
{
	t_mlx_state	*mlx_state;
	t_player	*player;
	t_dda		*dda;
	char		*paths[MAX_IMGS];
}	t_program;

#endif
