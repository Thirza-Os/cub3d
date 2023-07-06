/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:08:32 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/06 14:10:31 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

void	determine_ra(t_cub3d *eng, int direction);

int	shoot_ray_key(t_cub3d *eng, int direction)
{
	int	i;

	i = 0;
	determine_ra(eng, direction);
	while (i < 5)
	{
		calc_angle_hori(eng);
		shoot_ray_hori(eng);
		calc_angle_vert(eng);
		shoot_rays_vert(eng);
		check_distance_v_h(eng);
		if (eng->dis_t < 15)
			return (1);
		eng->ra += 0.1;
		i++;
	}
	return (0);
}

void	forward_backwards(mlx_key_data_t keydata, t_cub3d *eng)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT \
	|| keydata.action == MLX_PRESS))
	{
		if (shoot_ray_key(eng, 1) == 0)
		{
			eng->player_x += eng->pdx;
			eng->player_y += eng->pdy;
		}
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT \
	|| keydata.action == MLX_PRESS))
	{
		if (shoot_ray_key(eng, 2) == 0)
		{
			eng->player_x -= eng->pdx;
			eng->player_y -= eng->pdy;
		}
	}
}

void	move_left_right(mlx_key_data_t keydata, t_cub3d *eng)
{
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT \
	|| keydata.action == MLX_PRESS))
	{
		if (shoot_ray_key(eng, 3) == 0)
		{
			eng->player_x += cos(eng->player_a - PI / 2) * 5;
			eng->player_y += sin(eng->player_a - PI / 2) * 5;
		}
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT \
	|| keydata.action == MLX_PRESS))
	{
		if (shoot_ray_key(eng, 4) == 0)
		{
			eng->player_x -= cos(eng->player_a - PI / 2) * 5;
			eng->player_y -= sin(eng->player_a - PI / 2) * 5;
		}
	}
}

void	look_left_right(mlx_key_data_t keydata, t_cub3d *eng)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT \
	|| keydata.action == MLX_PRESS))
	{
		eng->player_a -= 0.1;
		if (eng->player_a < 0)
			eng->player_a += 2 * PI;
		eng->pdx = cos(eng->player_a) * 5;
		eng->pdy = sin (eng->player_a) * 5;
	}
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT \
	|| keydata.action == MLX_PRESS))
	{
		eng->player_a += 0.1;
		if (eng->player_a > 2 * PI)
			eng->player_a -= 2 * PI;
		eng->pdx = cos(eng->player_a) * 5;
		eng->pdy = sin (eng->player_a) * 5;
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *eng_void)
{
	t_cub3d	*eng;

	eng = (t_cub3d *)eng_void;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(eng->mlx_p);
	forward_backwards(keydata, eng);
	look_left_right(keydata, eng);
	move_left_right(keydata, eng);
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_W || keydata.key == \
	MLX_KEY_S || keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_LEFT \
	|| keydata.key == MLX_KEY_RIGHT) && (keydata.action == MLX_PRESS \
	|| keydata.action == MLX_REPEAT))
	{
		draw2dmap(eng);
		create_player(eng);
		draw_rays(eng);
	}
}
