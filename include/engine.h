/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   engine.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/29 22:00:03 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/05/30 21:27:16 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <stdbool.h>

// # include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42.h"

// voor nu hardcoded zo dat ik mijn tracer kan checken
// komt later van de parser af
# define MAPWIDTH 24
# define MAPHEIGHT 24
# define SCREENWIDTH 640
# define SCREENHEIGHT 480

typedef union u_color
{
	struct
	{
		unsigned char	a;
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
	};
	unsigned int		hexdecimal;
	unsigned char		rgba[4];
}	t_color;

typedef struct s_location
{
	size_t	x;
	size_t	y;
}	t_location;

typedef struct s_ray
{
	float		len;
	float		corr_len;
	float		angle;
	float		x;
	float		y;
	float		wall_ht;
	uint8_t		wall;
	mlx_image_t	*slice_old;
	mlx_image_t	*slice_new;
}	t_ray;

typedef struct s_player
{
	t_location	start;
	float		location[2];
	float		angle;
	float		dx;
	float		dy;
	float		plane;
	t_ray		*ray;
	size_t		raycount;
}	t_player;

typedef union u_wall
{
	struct
	{
		mlx_texture_t	*north;
		mlx_texture_t	*south;
		mlx_texture_t	*west;
		mlx_texture_t	*east;
	};
	mlx_texture_t		*direction[4];
}	t_wall;

typedef struct s_map
{
	t_wall		*walls;
	t_color		*floor;
	t_color		*ceiling;
	char		**map;
}	t_map;

void	init_state(void);
#endif
