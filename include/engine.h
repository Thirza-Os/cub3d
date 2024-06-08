/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   engine.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/29 22:00:03 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/08 19:36:40 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <stdbool.h>
# include <stdlib.h>

# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

// voor nu hardcoded zo dat ik mijn tracer kan checken
// komt later van de parser af
# define MAPWIDTH 8
# define MAPHEIGHT 8
# define SCREENWIDTH 1024
# define SCREENHEIGHT 512

typedef struct s_ray
{
	float	len;
	float	corr_len;
	float	angle;
	float	x;
	float	y;
	float	wall_ht;
}	t_ray;

typedef struct s_player
{
	float	pos[2];
	float	angle;
	float	dx;
	float	dy;
	t_ray	*ray;
	char	faceing;
}	t_player;

typedef struct s_mlx_state
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_mlx_state;

typedef struct s_game_state
{
	t_player	*player;
	t_mlx_state	*mlx;
	char		**map;
	size_t		map_size[2];
}	t_game_state;

bool	init_state(t_game_state *state);
bool	err_handler(const char *msg, t_game_state *state);

void	free_game_state(t_game_state *state);

#endif
