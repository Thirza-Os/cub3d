/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2dmap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:05:20 by rbrune        #+#    #+#                 */
/*   Updated: 2023/04/26 15:39:52 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

void	draw2DMap(t_cub3d *eng)
{
	int	unsigned color;
	int x = 0;
	int y = 0;
	int xo = 0;
	int yo = 0;

	eng->map_x = eng->program->max_xy.x;
	eng->map_y = eng->program->max_xy.y;
	eng->map_s = 64;
	eng->width = (eng->map_x * eng->map_s); //+ 512;
	eng->height = eng->map_y * eng->map_s;
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