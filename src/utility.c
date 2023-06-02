/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:22:02 by rbrune        #+#    #+#                 */
/*   Updated: 2023/05/24 14:37:18 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"


void	init_drawline(t_drawline *vars, int *cords)
{
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

//if (vars.x0 >= 0 && vars.x0 < eng->width && \
//		vars.y0 >= 0 && vars.y0 < eng->height)
//			mlx_put_pixel(eng->g_img_p, vars.x0, vars.y0, eng->color);
//		vars.e2 = 2 * vars.err;
//		if (vars.e2 > -vars.dy && (vars.x1 - vars.x0) * vars.sx > 0)
//		{
//			vars.err -= vars.dy;
//			vars.x0 += vars.sx;
//		}
//		if (vars.e2 < vars.dx && (vars.y1 - vars.y0) * vars.sy > 0)
//		{
//			vars.err += vars.dx;
//			vars.y0 += vars.sy;
//		}


void	draw_line_3d(t_cub3d *eng, int *cords)
{
	t_drawline	vars;

	init_drawline(&vars, cords);
	int drawStart = -eng->line_h / 2 + HEIGHT / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = eng->line_h / 2 + HEIGHT / 2;
      if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
	if (eng->wall_side == 0)
		eng->wall_x = eng->player_y + eng->dis_t * eng->ry;
	else
		eng->wall_x = eng->player_x + eng->dis_t * eng->rx;

	int texX = (int)(eng->wall_x * (double)(eng->active_texture->width));
    if(eng->wall_side == 0 && eng->rx > 0) texX = eng->active_texture->width - texX - 1;
    if(eng->wall_side == 1 && eng->ry < 0) texX = eng->active_texture->width - texX - 1;
	double step = 1.0 * eng->active_texture->height / eng->line_h;
	double texPos = (drawStart - HEIGHT / 2 + eng->line_h / 2) * step;
	while (drawStart < drawEnd)
	{
		int texY = (int)texPos & (eng->active_texture->height - 1);
		uint32_t color = get_pixel(eng->wall_x, texY, eng->active_texture);
		//if (x < eng->map_x * 8 && y < eng->map_y * 8)
		//	(void)vars;
		//else
			mlx_put_pixel(eng->g_img_p, vars.x0 , vars.y0, color);
		drawStart++;
		texPos += step;
		vars.y0++;
	}
}


void	draw_line_2d(t_cub3d *eng, int *cords, int color)
{
	t_drawline	*vars;

	vars = malloc(sizeof(t_drawline));
	init_drawline(vars, cords);
	while (vars->x0 != vars->x1 || vars->y0 != vars->y1)
	{
		if (vars->x0 >= 0 && vars->x0 < WIDTH && \
		vars->y0 >= 0 && vars->y0 < HEIGHT)
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
}

double	dist(double ax, double ay, double bx, double by)
{
	double	dx;
	double	dy;

	dx = bx - ax;
	dy = by - ay;
	return (sqrt(dx * dx + dy * dy));
}
