/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2dmap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:05:20 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/06 14:04:01 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

void	draw2dmap(t_cub3d *eng)
{
	int unsigned	color;
	int				x;
	int				y;

	y = 0;
	eng->map_x = eng->program->max_xy.x;
	eng->map_y = eng->program->max_xy.y;
	eng->map_s = 64;
	while (y < eng->map_y)
	{
		x = 0;
		while (x < eng->map_x)
		{
			if (eng->program->map[y][x] == '1')
				color = 0x000000FF;
			else
				color = 0xFFFFFFFF;
			draw_square(eng, x * 8, y * 8, color);
			x++;
		}
		y++;
	}
}
