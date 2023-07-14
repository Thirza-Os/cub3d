/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:19:32 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/14 16:03:22 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

void	convert_colors(t_cub3d *eng)
{
	((uint8_t *)(&eng->program->usable_floor))[3] = eng->program->floor_rgb[0];
	((uint8_t *)(&eng->program->usable_floor))[2] = eng->program->floor_rgb[1];
	((uint8_t *)(&eng->program->usable_floor))[1] = eng->program->floor_rgb[2];
	((uint8_t *)(&eng->program->usable_floor))[0] = 255;
	((uint8_t *)(&eng->program->usable_ceiling))[3] = \
	eng->program->ceiling_rgb[0];
	((uint8_t *)(&eng->program->usable_ceiling))[2] = \
	eng->program->ceiling_rgb[1];
	((uint8_t *)(&eng->program->usable_ceiling))[1] = \
	eng->program->ceiling_rgb[2];
	((uint8_t *)(&eng->program->usable_ceiling))[0] = 255;
}

void	make_ceiling_floor(t_cub3d *eng)
{
	int	i;
	int	j;

	i = 0;
	convert_colors(eng);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j < HEIGHT / 2)
				mlx_put_pixel(eng->g_img_p, i, j, eng->program->usable_ceiling);
			else
				mlx_put_pixel(eng->g_img_p, i, j, eng->program->usable_floor);
			j++;
		}
		i++;
	}
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
	draw_line_3d(eng);
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
	if (eng->ra < 0)
		eng->ra += 2 * PI;
	if (eng->ra > 2 * PI)
		eng->ra -= 2 * PI;
}

void	draw_rays(t_cub3d *eng)
{
	int	cords[4];

	make_ceiling_floor(eng);
	draw2dmap(eng);
	create_player(eng);
	init(eng);
	eng->r = 0;
	while (eng->r < WIDTH)
	{
		calc_angle_vert(eng);
		shoot_rays_vert(eng);
		calc_angle_hori(eng);
		shoot_ray_hori(eng);
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
