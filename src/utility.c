/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:22:02 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/06 14:33:32 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

void	init_draw_3d(t_drawline *vars, t_cub3d *eng)
{
	double	ty_off;

	ty_off = 0;
	vars->tx = (int)fmod(eng->rx, eng->active_texture->width);
	eng->line_h = (eng->map_s * (eng->map_y * 64)) / eng->dis_t;
	vars->ty_step = eng->active_texture->height / (double)eng->line_h;
	if (eng->line_h > (eng->map_y * 64))
	{
		ty_off = (eng->line_h - HEIGHT) / 2.0;
		eng->line_h = (eng->map_y * 64);
	}
	vars->ty = ty_off * vars->ty_step;
	vars->x0 = eng->r;
	vars->y0 = 80 + 200 - eng->line_h / 2;
	vars->y1 = 80 + eng->line_h + (200 - eng->line_h / 2);
	vars->dx = abs(vars->x1 - vars->x0);
	vars->dy = abs(vars->y1 - vars->y0);
}

void	draw_line_3d(t_cub3d *eng)
{
	t_drawline	vars;
	uint32_t	color;

	init_draw_3d(&vars, eng);
	while (vars.y0 < vars.y1)
	{
		color = get_pixel(vars.tx, vars.ty, eng->active_texture);
		if (vars.x0 < eng->map_x * 8 && vars.y0 < eng->map_y * 8)
			(void) vars;
		else if (vars.y0 < eng->map_s * eng->map_y && \
		vars.x0 < eng->map_s * eng->map_x)
		{
			if (vars.y0 > 0)
			{
				mlx_put_pixel(eng->g_img_p, vars.x0, vars.y0, color);
			}
		}
		vars.ty += vars.ty_step;
		vars.y0++;
	}
}

void	init_draw_2d(t_drawline *vars, int *cords)
{
	vars->x0 = cords[0];
	vars->x1 = cords[2];
	vars->y0 = cords[1];
	vars->y1 = cords[3];
	vars->dx = abs(vars->x1 - vars->x0);
	vars->dy = abs(vars->y1 - vars->y0);
	if (vars->x0 < vars->x1)
		vars->sx = 1;
	else
		vars->sx = -1;
	if (vars->y0 < vars->y1)
		vars->sy = 1;
	else
		vars->sy = -1;
	vars->err = vars->dx - vars->dy;
}

void	draw_line_2d(t_cub3d *eng, int *cords, int color)
{
	t_drawline	*vars;

	vars = malloc(sizeof(t_drawline));
	init_draw_2d(vars, cords);
	while (vars->x0 != vars->x1 || vars->y0 != vars->y1)
	{
		if (vars->x0 >= 0 && vars->x0 < eng->map_s * eng->map_x && \
		vars->y0 >= 0 && vars->y0 < eng->map_s * eng->map_y)
			mlx_put_pixel(eng->g_img_p, (vars->x0 / 8), (vars->y0 / 8), color);
		vars->e2 = 2 * vars->err;
		if (vars->e2 > -vars->dy && (vars->x1 - vars->x0) * vars->sx > 0)
		{
			vars->err -= vars->dy;
			vars->x0 += vars->sx;
		}
		if (vars->e2 < vars->dx && (vars->y1 - vars->y0) * vars->sy > 0)
		{
			vars->err += vars->dx;
			vars->y0 += vars->sy;
		}
	}
	if (vars->x1 >= 0 && vars->x1 < WIDTH && vars->y1 >= 0 && vars->y1 < HEIGHT)
		mlx_put_pixel(eng->g_img_p, (vars->x0 / 8), (vars->y0 / 8), color);
	free (vars);
}

double	dist(double ax, double ay, double bx, double by)
{
	double	dx;
	double	dy;

	dx = bx - ax;
	dy = by - ay;
	return (sqrt(dx * dx + dy * dy));
}
