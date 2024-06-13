#include "../include/engine.h"
#include <math.h>

// denk dat plane nooit is gezet
void	set_dda(t_game_state *state, int row)
{
	t_dda	*dda;

	dda = state->dda;
	dda->camera_col = 2 * (row /(double)SCREENWIDTH) - 1;
	dda->ray_dir.row = state->player->pos.row + (dda->plane.row * dda->camera_col);
	dda->ray_dir.col = state->player->pos.col + (dda->plane.col * dda->camera_col);
	if (dda->ray_dir.col == 0)
		dda->delta_dist.col = INFINITY;
	else
		dda->delta_dist.col = fabs(1 / dda->ray_dir.col);
	if (dda->ray_dir.row == 0)
		dda->delta_dist.row = INFINITY;
	else
		dda->delta_dist.row = fabs(1 / dda->ray_dir.row);
}

static void	set_steps(t_game_state *state)
{
	t_dda	*dda;

	dda = state->dda;
	if (dda->ray_dir.col < 0)
	{
		dda->stepper.col = -1;
		dda->side_dist.col = (state->player->pos.col - dda->pos.col) * dda->delta_dist.col;
	}
	else
	{
		dda->stepper.col = 1;
		dda->side_dist.col = (dda->pos.col + 1 - state->player->pos.col) * dda->delta_dist.col;
	}
	if (dda->ray_dir.row < 0)
	{
		dda->stepper.row = -1;
		dda->side_dist.row = (state->player->pos.row - dda->pos.row) * dda->delta_dist.row;
	}
	else
	{
		dda->stepper.row = 1;
		dda->side_dist.row = (dda->pos.row + 1 - state->player->pos.row) * dda->delta_dist.row;
	}
}

static	void	check_collision(t_game_state *state)
{
	t_dda	*dda;

	dda = state->dda;
	while (1)
	{
		if (dda->side_dist.col < dda->side_dist.row)
		{
			dda->side_dist.col += dda->delta_dist.col;
			dda->pos.col += dda->stepper.col;
			dda->side = 1;
		}
		else
		{
			dda->side_dist.row += dda->delta_dist.row;
			dda->pos.row += dda->stepper.row;
			dda->side = 2;
		}

		// voor nu ik heb een segfault
		if ((int)dda->pos.row < 6 && (int)dda->pos.col < 6)
		{
			if (state->map[(int)dda->pos.row][(int)dda->pos.col] == '1')
				break ;
		}
		else
		{
			printf("Dit is niet goed col of row...\n");
			printf("row: %d, col: %d\n", (int)dda->pos.row, (int)dda->pos.col);
			break ;
		}
	}
}

void	dda(t_game_state *state)
{
	size_t	col_index;

	col_index = 0;
	// while (col_index < SCREENWIDTH)
	while (col_index < 6)
	{
		set_dda(state, col_index);
		set_steps(state);
		check_collision(state);
		col_index++;
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
			printf("put pixel: %f, %f\n", state->player->pos.col + col, state->player->pos.row + row);
			mlx_put_pixel(state->mlx->image, state->player->pos.col + col, state->player->pos.row + row, ft_pixel(0, 255, 0, 255));
			col++;
		}
		row++;
	}
}

void	run_game(t_game_state *state)
{
	dda(state);
	// draw_player(state);
	// mlx_loop_hook(state->mlx->mlx, key_hook, state);
	// mlx_loop(state->mlx->mlx);
}
