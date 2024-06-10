#include "../include/engine.h"
#include <math.h>


void	dda(t_game_state *state)
{
	float	start_ray[2];
	start_ray[0] = state->player->pos[0];
	start_ray[1] = state->player->pos[1];

	float	ray_dir[2];
	ray_dir[0] = (state->player->pos[0] / CELLSIZE) - state->player->pos[0];
	ray_dir[1] = (state->player->pos[1] / CELLSIZE) - state->player->pos[1];

	float unit_step[2];
	unit_step[0] = sqrt(1 + (ray_dir[1] / ray_dir[0]) * (ray_dir[1] / ray_dir[0]));
	unit_step[1] = sqrt(1 + (ray_dir[0] / ray_dir[1]) * (ray_dir[0] / ray_dir[1]));

	float map_check[2];
	map_check[0] = start_ray[0];
	map_check[1] = start_ray[1];

	float stepper[2];
	float ray_len[2];


	if (ray_dir[0] < 0)
	{
		stepper[0] = -1;
		ray_len[0] = (start_ray[0] - map_check[0]) * unit_step[0];
	}
	else {
		stepper[0] = 1;
		ray_len[0] = (map_check[0] + 1 - start_ray[0]) * unit_step[0] ;
	}

	if (ray_dir[1] < 0)
	{
		stepper[1] = -1;
		ray_len[1] = (start_ray[0] - map_check[0]) * unit_step[1];
	}
	else {
		stepper[1] = 1;
		ray_len[1] = (map_check[0] + 1);
	}



}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_player(t_game_state *state)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < 16)
	{
		col = 0;
		while (col < 16)
		{
			printf("put pixel: %f, %f\n", state->player->pos[0] + col, state->player->pos[1] + row);
			mlx_put_pixel(state->mlx->image, state->player->pos[0] + col, state->player->pos[1] + row, ft_pixel(0, 255, 0, 255));
			col++;
		}
		row++;
	}
}

void	run_game(t_game_state *state)
{
	draw_player(state);
	mlx_loop_hook(state->mlx->mlx, key_hook, state);
	mlx_loop(state->mlx->mlx);
}
