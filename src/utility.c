/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:22:02 by rbrune        #+#    #+#                 */
/*   Updated: 2023/06/07 13:05:42 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

void	init_drawline(t_drawline *vars, int *cords, t_cub3d *eng)
{
	vars->ty = 0;
	vars->tx = (int)(eng->rx / 2.0) % eng->active_texture->width;
	vars->ty_step = eng->active_texture->height / (double)eng->line_h;
	vars->x0 = cords[0];
	vars->y0 = cords[1];
	vars->x1 = cords[2];
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

void	draw_line_3d(t_cub3d *eng, int *cords)
{
	t_drawline	vars;
	uint32_t	color;

	init_drawline(&vars, cords, eng);
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

void	draw_line_2d(t_cub3d *eng, int *cords, int color)
{
	t_drawline	*vars;

	vars = malloc(sizeof(t_drawline));
	init_drawline(vars, cords, eng);
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
