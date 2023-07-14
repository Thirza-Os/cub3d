/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda_raycast.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:17:02 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/11 12:36:39 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

//These functions trigger when a wall is found
int	dda_hori(t_cub3d *eng)
{
	eng->hx = eng->rx;
	eng->hy = eng->ry;
	eng->dis_h = dist(eng->player_x, eng->player_y, eng->hx, eng->hy);
	if (eng->dis_h < 0)
	{
		eng->dis_h = 1;
		return (0);
	}
	eng->dof = eng->map_x;
	return (1);
}

int	dda_vert(t_cub3d *eng)
{
	eng->vx = eng->rx;
	eng->vy = eng->ry;
	eng->dis_v = dist(eng->player_x, eng->player_y, eng->vx, eng->vy);
	if (eng->dis_v < 0)
	{
		eng->dis_v = 1;
		return (0);
	}
	eng->dof = eng->map_y;
	return (1);
}
