/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:19:32 by rbrune        #+#    #+#                 */
/*   Updated: 2023/06/02 13:36:18 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

void	make_ceiling_floor(t_cub3d *eng, int color_ceiling, int color_floor)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j < HEIGHT / 2)
				mlx_put_pixel(eng->g_img_p, i, j, color_ceiling);
			else
				mlx_put_pixel(eng->g_img_p, i, j, color_floor);
			j++;
		}
		i++;
	}
}

void	draw3dwalls(t_cub3d *eng, int r, double line_h)
{
	double	line_o;
	int		cords[4];

	line_o = 200 - line_h / 2;
	cords[0] = r;// - 512
	cords[1] = 80 + 200 - line_h / 2; // 80 is the offset of the walls but should be based on the height of the window
	cords[2] = r;// - 512
	cords[3] = 80 + line_h + line_o;
	draw_line_3d(eng, cords);
}

void	walls(t_cub3d *eng)
{
	if (eng->ra < 0)
		eng->ra += 2 * PI;
	if (eng->ra > 2 * PI)
		eng->ra -= 2 * PI;
	eng->ca = eng->player_a - eng->ra;
	if (eng->ca < 0)
		eng->ca += 2 * PI;
	if (eng->ca > 2 * PI)
		eng->ca -= 2 * PI;
	eng->dis_t = eng->dis_t * cos(eng->ca);
	if (eng->dis_t < 1)
		eng->dis_t = 1;
	eng->line_h = (eng->map_s * (eng->map_y * 64)) / eng->dis_t;
	if (eng->line_h > (eng->map_y * 64))
		eng->line_h = (eng->map_y * 64);
	draw3dwalls(eng, eng->r, eng->line_h);
}

void	init(t_cub3d *eng)
{
	eng->r = 0;
	eng->ra = eng->player_a - 0.0174533 * 30;
	eng->dis_h = 100000;
	eng->hx = eng->player_x;
	eng->hy = eng->player_y;
	eng->dis_v = 100000;
	eng->vx = eng->player_x;
	eng->vy = eng->player_y;
}

void	draw_rays(t_cub3d *eng)
{
	int	cords[4];

	make_ceiling_floor(eng, 10000, 0xFF00FFFF);
	draw2DMap(eng);
	create_player(eng);
	init(eng);
	if (eng->ra < 0)
		eng->ra += 2 * PI;
	if (eng->ra > 2 * PI)
		eng->ra -= 2 * PI;
	eng->r = 0;
	while (eng->r < WIDTH)
	{
		calc_angle_hori(eng);
		shoot_ray_hori(eng);
		calc_angle_vert(eng);
		shoot_rays_vert(eng);
		check_distance_v_h(eng);
		cords[0] = eng->player_x;
		cords[1] = eng->player_y;
		cords[2] = eng->rx;
		cords[3] = eng->ry;
		draw_line_2d(eng, cords, 0xFF00FFFF);
		walls(eng);
		eng->r++;
		eng->ra += DR;
	}
}
