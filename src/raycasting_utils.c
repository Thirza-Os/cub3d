/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 13:44:36 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/14 16:07:33 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

int	dda_vert(t_cub3d *eng);
int	dda_hori(t_cub3d *eng);

void	calc_angle_hori(t_cub3d *eng)
{
	eng->dof = 0;
	eng->atan = -1 / tan(eng->ra);
	if (eng->ra > PI)
	{
		eng->ry = (((int)eng->player_y >> 6) << 6) - 0.0001;
		eng->rx = (eng->player_y - eng->ry) * eng->atan + eng->player_x;
		eng->yo = -64;
		eng->xo = -eng->yo * eng->atan;
	}
	if (eng->ra < PI)
	{
		eng->ry = (((int)eng->player_y >> 6) << 6) + 64;
		eng->rx = (eng->player_y - eng->ry) * eng->atan + eng->player_x;
		eng->yo = 64;
		eng->xo = -eng->yo * eng->atan;
	}
	if (eng->ra == 0 || eng->ra == PI)
	{
		eng->rx = eng->player_x;
		eng->ry = eng->player_y;
		eng->dof = eng->map_x;
	}
}

void	shoot_ray_hori(t_cub3d *eng)
{
	while (eng->dof < eng->map_x)
	{
		eng->mx = (int)(eng->rx) >> 6;
		eng->my = (int)(eng->ry) >> 6;
		eng->mp = eng->my * eng->map_x + eng->mx;
		if (eng->mp > 0 && eng->mp < eng->map_x * \
		eng->map_y && eng->map[eng->mp] == '1')
		{
			if (!dda_hori(eng))
				break ;
		}
		else if (eng->mp % eng->map_x == 0 || eng->mp % \
		eng->map_x == eng->map_x - 1 || eng->mp < eng->map_x || eng->mp > \
		(eng->map_x * eng->map_y) - eng->map_x || eng->mp < 0)
		{
			eng->dis_h = 100000;
			break ;
		}
		else
		{
			eng->rx += eng->xo;
			eng->ry += eng->yo;
			eng->dof += 1;
		}
	}
}

void	calc_angle_vert(t_cub3d *eng)
{
	eng->dof = 0;
	eng->ntan = -tan(eng->ra);
	if (eng->ra > P2 && eng->ra < P3)
	{
		eng->rx = (((int)eng->player_x >> 6) << 6) - 0.0001;
		eng->ry = (eng->player_x - eng->rx) * eng->ntan + eng->player_y;
		eng->xo = -64;
		eng->yo = -eng->xo * eng->ntan;
	}
	if (eng->ra < P2 || eng->ra > P3)
	{
		eng->rx = (((int)eng->player_x >> 6) << 6) + 64;
		eng->ry = (eng->player_x - eng->rx) * eng->ntan + eng->player_y;
		eng->xo = 64;
		eng->yo = -eng->xo * eng->ntan;
	}
	if (eng->ra == 0 || eng->ra == PI)
	{
		eng->rx = eng->player_x;
		eng->ry = eng->player_y;
		eng->dof = eng->map_y;
	}
}

void	shoot_rays_vert(t_cub3d *eng)
{
	while (eng->dof < eng->map_y)
	{
		eng->mx = (int)(eng->rx) >> 6;
		eng->my = (int)(eng->ry) >> 6;
		eng->mp = eng->my * eng->map_x + eng->mx;
		if (eng->mp >= 0 && eng->mp < eng->map_x * \
		eng->map_y && eng->map[eng->mp] == '1')
		{
			if (!dda_vert(eng))
				break ;
		}
		else if (eng->mp % eng->map_x == 0 || eng->mp % \
		eng->map_x == eng->map_x - 1 || eng->mp < eng->map_x || eng->mp > \
		(eng->map_x * eng->map_y) - eng->map_x || eng->mp < 0)
		{
			eng->dis_v = 100000;
			break ;
		}
		else
		{
			eng->rx += eng->xo;
			eng->ry += eng->yo;
			eng->dof += 1;
		}
	}
}

void	check_distance_v_h(t_cub3d *eng)
{
	if (eng->dis_v < eng->dis_h)
	{
		eng->active_texture = eng->program->mlx_textures[3];
		if (eng->player_x < eng->vx)
			eng->active_texture = eng->program->mlx_textures[2];
		eng->dis_t = eng->dis_v;
		eng->rx = eng->vx;
		eng->ry = eng->vy;
	}
	if (eng->dis_h < eng->dis_v)
	{
		eng->active_texture = eng->program->mlx_textures[1];
		if (eng->player_y < eng->hy)
			eng->active_texture = eng->program->mlx_textures[0];
		eng->dis_t = eng->dis_h;
		eng->rx = eng->hx;
		eng->ry = eng->hy;
	}
}
