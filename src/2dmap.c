/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2dmap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:05:20 by rbrune        #+#    #+#                 */
/*   Updated: 2023/06/07 12:46:34 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

void	draw2DMap(t_cub3d *eng)
{
	int unsigned	color;
	int				x;
	int				y;
	int				xo;
	int				yo;

	y = 0;
	eng->map_x = eng->program->max_xy.x;
	eng->map_y = eng->program->max_xy.y;
	eng->map_s = 64;
	//eng->width = (eng->map_x * eng->map_s);
	//eng->height = eng->map_y * eng->map_s;
	while (y < eng->map_y)
	{
		x = 0;
		while (x < eng->map_x)
		{
			if (eng->program->map[y][x] == '1')
				color = 0x000000FF;
			else
				color = 0xFFFFFFFF;
			xo = x * 8;
			yo = y * 8;
			draw_square(eng, xo, yo, color);
			x++;
		}
		y++;
	}
}
