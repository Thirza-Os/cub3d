/* ************************************************************************** */
/*                                                                           */
/*                                                        ::::::::            */
/*   rickmain.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 10:54:03 by rbrune        #+#    #+#                 */
/*   Updated: 2023/02/28 13:40:38 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../engine.h"

void	draw_square(t_cub3d *eng, int x, int y, unsigned int color)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = x;
	while (tmp_x < x + 7)
	{
		tmp_y = y;
		while (tmp_y < y + 7)
		{
			mlx_put_pixel(eng->g_img_p, tmp_x, tmp_y, color);
			mlx_put_pixel(eng->g_img_p, x + 7, tmp_y, 0xFF6666FF);
			tmp_y++;
		}
		mlx_put_pixel(eng->g_img_p, tmp_x, y + 7, 0xFF6666FF);
		tmp_x++;
	}
}

void	draw_ray(t_cub3d *eng, int x, int y, unsigned int color)
{
	int	cords[4];

	cords[0] = eng->player_x;
	cords[1] = eng->player_y;
	cords[2] = x;
	cords[3] = y;
	draw_line_2d(eng, cords, color);
}

void	create_player(t_cub3d *eng)
{
	int	i;
	int	j;

	i = -3;
	while (i < 3)
	{
		j = -3;
		while (j < 3)
		{
			mlx_put_pixel(eng->g_img_p, (eng->player_x / 8)+ i, \
			(eng->player_y / 8) + j, 0x005099FF);
			j++;
		}
		i++;
	}
}

void	drawgame(t_program *program)
{
	t_cub3d	eng;

	eng.map = malloc(sizeof(char *) * program->max_xy.y * program->max_xy.x);
	int y = 0;
	int i = 0;
	while (y < program->max_xy.y)
	{
		int x = 0;
		while (x < program->max_xy.x)
		{
			eng.map[i] = program->map[y][x];
			x++;
			i++;
		}
		y++;
	}
	eng.program = program;
	eng.color = 0;
	eng.player_a = PI;
	eng.pdx = cos(eng.player_a) * 5;
	eng.pdy = sin(eng.player_a) * 5;
	extract_mlx_pixels(eng.program);
	eng.player_x = program->start_pos.x * 64;
	eng.player_y = program->start_pos.y * 64;
	eng.mlx_p = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	eng.g_img_p = mlx_new_image(eng.mlx_p, WIDTH, HEIGHT);
	mlx_image_to_window(eng.mlx_p, eng.g_img_p, 0, 0);
	mlx_key_hook(eng.mlx_p, &my_keyhook, (void *)&eng);
	draw2DMap(&eng);
	create_player(&eng);
	draw_rays(&eng);
	mlx_loop(eng.mlx_p);
}
