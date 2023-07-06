/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   engine.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 10:55:06 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/06 14:09:43 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# define WIDTH 576
# define HEIGHT 576
# define PI 3.1415926535
# define P2 PI / 2
# define P3 3 * PI / 2
# define DR 0.0020453077172

# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "src/cub3d.h"
typedef struct s_drawline {
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	double	tx;
	double	ty_step;
	double	ty;
}	t_drawline;

typedef struct s_cub3d {
	t_program		*program;
	mlx_image_t		*g_img_p;
	mlx_t			*mlx_p;
	mlx_texture_t	*active_texture;
	int				width;
	int				height;
	double			player_x;
	double			player_y;
	double			pdx;
	double			pdy;
	double			player_a;
	int				map_x;
	int				map_y;
	int				map_s;
	char			*map;
	int				r;
	int				mx;
	int				my;
	int				mp;
	int				dof;
	int				dis_t;
	double			rx;
	double			ry;
	double			ra;
	double			xo;
	double			yo;
	double			atan;
	double			dis_h;
	double			hx;
	double			hy;
	double			dis_v;
	double			vx;
	double			vy;
	double			ntan;
	double			ca;
	double			line_h;
	int				color;
}	t_cub3d;

void	drawgame(t_program *program);

// raycasting
void	draw_rays(t_cub3d *eng);
void	calc_angle_hori(t_cub3d *eng);
void	calc_angle_vert(t_cub3d *eng);
void	shoot_ray_hori(t_cub3d *eng);
void	shoot_rays_vert(t_cub3d *eng);
void	check_distance_v_h(t_cub3d *eng);
void	walls(t_cub3d *eng);

// utility
double	dist(double ax, double ay, double bx, double by);
void	draw_line_2d(t_cub3d *eng, int *cords, int color);
void	draw_line_3d(t_cub3d *eng);
// map
void	draw2dmap(t_cub3d *eng);

// hooks
void	my_keyhook(mlx_key_data_t keydata, void *eng_void);

void	draw_square(t_cub3d *eng, int x, int y, unsigned int color);
void	create_player(t_cub3d *eng);
#endif