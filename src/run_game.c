/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/19 22:03:10 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/07/09 18:01:53 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/engine.h"

void	get_draw_info(t_game_state *state)
{
	double	wall_dist;
	t_dda	*dda;

	dda = state->dda;
	if (dda->side_dist_x == 1)
		dda->prep_wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dda->prep_wall_dist = dda->side_dist_y - dda->delta_dist_y;
	wall_dist = 1 / dda->prep_wall_dist;
	if (wall_dist == INFINITY)
		dda->line.heigth = SCREENHEIGHT;
	else
		dda->line.heigth = (int)(wall_dist * SCREENHEIGHT);
	dda->line.start = (SCREENHEIGHT / 2) - (dda->line.heigth / 2);
	dda->line.end = (SCREENHEIGHT / 2) + (dda->line.heigth / 2);
}

void	set_dda(t_game_state *state, int col)
{
	t_dda	*dda;

	dda = state->dda;
	dda->camera_x = 2 * (col / (double)SCREENWIDTH) - 1;
	dda->ray_dir.row = state->player->pos.row + (dda->plane_x * dda->camera_x);
	dda->ray_dir.col = state->player->pos.col + (dda->plane_x * dda->camera_x);
	dda->player_pos.row = (int)state->player->pos.row;
	dda->player_pos.col = (int)state->player->pos.col;
	if (dda->ray_dir.row == 0)
		dda->delta_dist_x = INFINITY;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir.row);
	if (dda->ray_dir.col == 0)
		dda->delta_dist_x = INFINITY;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir.col);
}

static	void	set_steps(t_game_state *state)
{
	t_dda		*dda;
	t_player	*player;

	dda = state->dda;
	player = state->player;
	dda->step_map_y = 1;
	dda->step_map_x = 1;
	if (dda->ray_dir.col < 0)
	{
		dda->step_map_x = -1;
		dda->side_dist_x = (player->pos.col - dda->player_pos.col) * dda->delta_dist_x;
	}
	else
		dda->side_dist_x = (dda->player_pos.col + 1.0 - player->pos.col) * dda->delta_dist_x;
	if (dda->ray_dir.row < 0)
	{
		dda->step_map_y = -1;
		dda->side_dist_y = (player->pos.row - dda->player_pos.row) * dda->delta_dist_y;
	}
	else
		dda->side_dist_y = (dda->player_pos.row + 1.0 - player->pos.row) * dda->delta_dist_y;
}

static	void	check_collision(t_game_state *state)
{
	t_dda	*dda;

	dda = state->dda;
	while (1)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->player_pos.col += dda->step_map_x;
			dda->current_side = 1;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->player_pos.row += dda->step_map_y;
			dda->current_side = 2;
		}
		if (state->map->map[(int)dda->player_pos.row][(int)dda->player_pos.col] == '1')
			break ;
	}
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	dda(t_game_state *state)
{
	size_t	col_index;

	// print_player(state->player);
	col_index = 0;
	while (col_index < SCREENWIDTH)
	{
		set_dda(state, col_index);
		set_steps(state);
		check_collision(state);
		get_draw_info(state);
		print_dda(state->dda);
		int row;

		row = 0;
		printf("row: %d, line: %d, screen: %d\n", row, state->dda->line.start, SCREENHEIGHT);
		// line < 0
		while (row < state->dda->line.start && row < SCREENHEIGHT)
		{
			printf("plafon\n");
			mlx_put_pixel(state->mlx->image, col_index, row, ft_pixel(0, 0, 255, 255));
			// mlx_put_pixel(state->mlx->image, row, col_index, ft_pixel(0, 0, 255, 255));
			row++;
		}

		printf("row: %d, line: %d, screen: %d\n", row, state->dda->line.end, SCREENHEIGHT);
		row = state->dda->line.end;  // + 1 misschien
		// line is meer dan screenheight
		while (row < SCREENHEIGHT)
		{
			printf("vloer\n");
			mlx_put_pixel(state->mlx->image, col_index, row, ft_pixel(255, 0, 0, 255));
			// mlx_put_pixel(state->mlx->image, row, col_index, ft_pixel(255, 0, 0, 255));
			row++;
		}
		col_index++;
	}
}

void	run_game(t_game_state *state)
{
	const double	values[4][4] = {{0, -1, 0.66, 0}, {1, 0, 0, 0.66}, \
									{0, 1, -0.66, 0}, {-1, 0, 0, -0.66}};

	// hardcoded for N pos
	state->dda->ray_dir.col = values[0][0];
	state->dda->ray_dir.row = values[0][1];
	state->dda->plane_x = values[0][2];
	state->dda->plane_y = values[0][3];

	dda(state);
	// mlx_loop(state->mlx->mlx);
	// mlx_terminate(state->mlx->mlx);
}
