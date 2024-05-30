/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   engine.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/29 22:00:03 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/05/30 18:46:37 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

#include <stdbool.h>

// # include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42.h"

// voor nu hardcoded zo dat ik mijn tracer kan checken
// komt later van de parser af
# define MAPWIDTH 24
# define MAPHEIGHT 24
# define SCREENWIDTH 640
# define SCREENHEIGHT 480

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_dir
{
	int	x;
	int	y;
}	t_dir;

typedef struct s_plane
{
	double	x;
	double	y;
}	t_plane;

typedef struct s_ray
{
	double	x;
	double	y;
}	t_ray;

typedef struct s_engine
{
	t_dir		dir;
	t_player	player;
	t_plane		plane;
	t_ray		ray;
	double		cur_time;
	double		prev_time;
} t_engine;

// pov

void	init_state(void);
#endif
