/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 19:39:07 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/03 19:43:01 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/engine.h"

static	void	get_draw_info(t_game_state *state)
{
	t_dda	*dda;

	dda = state->dda;
	if (dda->current_side == 1)
		dda->prep_wall_dist = (dda->map_pos.x - dda->player_pos.x + \
					(1.0 - (double)dda->step_map_x) / 2.0) / dda->ray_dir.x;
	else
		dda->prep_wall_dist = (dda->map_pos.y - dda->player_pos.y + \
					(1.0 - (double)dda->step_map_y) / 2.0) / dda->ray_dir.y;
	dda->line.heigth = (int)(SCREENHEIGHT / dda->prep_wall_dist);
	dda->line.start = -dda->line.heigth / 2 + SCREENHEIGHT / 2;
	if (dda->line.start < 0)
	{
		dda->line.start = 0;
	}
	dda->line.end = dda->line.heigth / 2 + SCREENHEIGHT / 2;
	if (dda->line.end >= SCREENHEIGHT)
	{
		dda->line.end = SCREENHEIGHT - 1;
	}
}

static	void	set_dda(t_game_state *state, int col)
{
	t_dda	*dda;

	dda = state->dda;
	dda->camera_x = 2 * col / (double)SCREENWIDTH - 1;
	dda->ray_dir.x = dda->player_dir.x + dda->plane_x * dda->camera_x;
	dda->ray_dir.y = dda->player_dir.y + dda->plane_y * dda->camera_x;
	dda->map_pos.x = (int)dda->player_pos.x;
	dda->map_pos.y = (int)dda->player_pos.y;
	if (dda->ray_dir.x == 0)
	{
		dda->ray_dir.x = INFINITY;
	}
	else
	{
		dda->ray_dir.x = fabs(1 / dda->ray_dir.x);
	}
	if (dda->ray_dir.y == 0)
	{
		dda->ray_dir.y = INFINITY;
	}
	else
	{
		dda->ray_dir.y = fabs(1 / dda->ray_dir.y);
	}
}

static	void	set_steps(t_game_state *state)
{
	t_dda	*dda;

	dda = state->dda;
	dda->step_map_x = 1;
	dda->step_map_y = 1;
	if (dda->ray_dir.x < 0)
	{
		dda->step_map_x = -1;
		dda->side_dist_x = (dda->player_pos.x - dda->map_pos.x) * \
			dda->delta_dist_x;
	}
	else
		dda->side_dist_x = (dda->map_pos.x + 1.0 - dda->player_pos.x) * \
			dda->delta_dist_x;
	if (dda->ray_dir.y < 0)
	{
		dda->step_map_y = -1;
		dda->side_dist_y = (dda->player_pos.y - dda->map_pos.y) * \
			dda->delta_dist_y;
	}
	else
		dda->side_dist_y = (dda->map_pos.y + 1.0 - dda->player_pos.y) * \
			dda->delta_dist_y;
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
			dda->map_pos.x += dda->step_map_x;
			dda->current_side = 1;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_pos.y += dda->step_map_y;
			dda->current_side = 2;
		}
		if (state->map->map[(int)dda->map_pos.y][(int)dda->map_pos.x] == '1')
			break ;
	}
}

void	dda(t_game_state *state)
{
	size_t	col_index;
	int		row;

	col_index = 0;
	ft_memset(state->mlx->image->pixels, 255, \
			SCREENWIDTH * SCREENHEIGHT * sizeof(uint32_t));
	while (col_index < SCREENWIDTH)
	{
		set_dda(state, col_index);
		set_steps(state);
		check_collision(state);
		get_draw_info(state);
		row = 0;
		while (row < state->dda->line.start && row < SCREENHEIGHT)
		{
			mlx_put_pixel(state->mlx->image, col_index, row, \
				ft_pixel(0, 0, 255, 255));
			row++;
		}
		row = state->dda->line.end;
		while (row < SCREENHEIGHT && row >= 0)
		{
			mlx_put_pixel(state->mlx->image, col_index, row, \
				ft_pixel(255, 0, 0, 255));
			row++;
		}
		col_index++;
	}
}
