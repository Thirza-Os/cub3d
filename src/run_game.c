/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/19 22:03:10 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/07/31 21:53:49 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/engine.h"
#include "libft.h"
#include <stdint.h>
#include <string.h>

// void	get_draw_info(t_game_state *state)
// {
// 	t_dda	*dda;
//
// 	dda = state->dda;
// 	if (dda->side_dist_x == 1)
// 		dda->prep_wall_dist = dda->side_dist_x - dda->delta_dist_x;
// 	else
// 		dda->prep_wall_dist = dda->side_dist_y - dda->delta_dist_y;
//
// 	dda->line.heigth = (int)(SCREENHEIGHT / dda->prep_wall_dist);
// 	dda->line.start = -dda->line.heigth / 2 + SCREENHEIGHT / 2;
// 	if (dda->line.start < 0) {
// 		dda->line.start = 0;
// 	}
//
// 	dda->line.end = dda->line.heigth / 2 + SCREENHEIGHT / 2;
// 	if (dda->line.end >= SCREENHEIGHT) {
// 		dda->line.end = SCREENHEIGHT - 1;
// 	}
// }

void get_draw_info(t_game_state *state)
{
    t_dda *dda = state->dda;

    // Calculate distance to the wall
    if (dda->current_side == 1)
        dda->prep_wall_dist = (dda->map_pos.x - dda->player_pos.x + (1 - dda->step_map_x) / 2) / dda->ray_dir.x;
    else
	{
        dda->prep_wall_dist = (dda->map_pos.y - dda->player_pos.y + (1 - dda->step_map_y) / 2) / dda->ray_dir.y;
	}

	if (dda->prep_wall_dist <= 0.0001) {
		printf("Error: Invalid prep_wall_dist value: %.6f\n", dda->prep_wall_dist);
		dda->prep_wall_dist = 0.0001;  // Assign a small non-zero value to avoid division by zero
	}
    dda->line.heigth = (int)(SCREENHEIGHT / dda->prep_wall_dist);
    dda->line.start = -dda->line.heigth / 2 + SCREENHEIGHT / 2;
    if (dda->line.start < 0) {
        dda->line.start = 0;
    }
    dda->line.end = dda->line.heigth / 2 + SCREENHEIGHT / 2;
    if (dda->line.end >= SCREENHEIGHT) {
        dda->line.end = SCREENHEIGHT - 1;
    }
}

void set_dda(t_game_state *state, int col)
{
    t_dda *dda = state->dda;
    dda->camera_x = 2 * col / (double)SCREENWIDTH - 1;
    dda->ray_dir.x = dda->player_dir.x + dda->plane_x * dda->camera_x;
    dda->ray_dir.y = dda->player_dir.y + dda->plane_y * dda->camera_x;
    dda->map_pos.x = (int)dda->player_pos.x;
    dda->map_pos.y = (int)dda->player_pos.y;
    dda->delta_dist_x = (dda->ray_dir.x == 0) ? INFINITY : fabs(1 / dda->ray_dir.x);
    dda->delta_dist_y = (dda->ray_dir.y == 0) ? INFINITY : fabs(1 / dda->ray_dir.y);
}
// void	set_dda(t_game_state *state, int col)
// {
// 	t_dda	*dda;
//
// 	dda = state->dda;
// 	dda->camera_x = 2 * col / (double)SCREENWIDTH - 1;
// 	dda->ray_dir.x = dda->player_dir.x + dda->plane_x * dda->camera_x;
// 	dda->ray_dir.y = dda->player_dir.y + dda->plane_y * dda->camera_x;
// 	dda->map_pos.x = (int)dda->player_pos.x;
// 	dda->map_pos.y = (int)dda->player_pos.y;
// 	if (dda->ray_dir.x == 0)
// 		dda->delta_dist_x = INFINITY;
// 	else
// 		dda->delta_dist_x = fabs(1 / dda->ray_dir.x);
//
// 	if (dda->ray_dir.y == 0)
// 		dda->delta_dist_y = INFINITY;
// 	else
// 		dda->delta_dist_y = fabs(1 / dda->ray_dir.y);
// }

void set_steps(t_game_state *state)
{
    t_dda *dda = state->dda;
    dda->step_map_x = 1;
    dda->step_map_y = 1;
    if (dda->ray_dir.x < 0)
    {
        dda->step_map_x = -1;
        dda->side_dist_x = (dda->player_pos.x - dda->map_pos.x) * dda->delta_dist_x;
    }
    else
        dda->side_dist_x = (dda->map_pos.x + 1.0 - dda->player_pos.x) * dda->delta_dist_x;
    if (dda->ray_dir.y < 0)
    {
        dda->step_map_y = -1;
        dda->side_dist_y = (dda->player_pos.y - dda->map_pos.y) * dda->delta_dist_y;
    }
    else
        dda->side_dist_y = (dda->map_pos.y + 1.0 - dda->player_pos.y) * dda->delta_dist_y;
}
// static	void	set_steps(t_game_state *state)
// {
// 	t_dda		*dda;
//
// 	dda = state->dda;
// 	dda->step_map_y = 1;
// 	dda->step_map_x = 1;
// 	if (dda->ray_dir.x < 0)
// 	{
// 		dda->step_map_x = -1;
// 		dda->side_dist_x = (dda->player_pos.x - dda->map_pos.x) * dda->delta_dist_x;
// 	}
// 	else
// 		dda->side_dist_x = (dda->map_pos.x + 1.0 - dda->player_pos.x) * dda->delta_dist_x;
// 	if (dda->ray_dir.y < 0)
// 	{
// 		dda->step_map_y = -1;
// 		dda->side_dist_y = (dda->player_pos.y - dda->map_pos.y) * dda->delta_dist_y;
// 	}
// 	else
// 		dda->side_dist_y = (dda->map_pos.y + 1.0 - dda->player_pos.y) * dda->delta_dist_y;
// }

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

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	dda(t_game_state *state)
{
	size_t	col_index;

	col_index = 0;
	ft_memset(state->mlx->image->pixels, 255, SCREENWIDTH * SCREENHEIGHT * sizeof(uint32_t));
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
		printf("Player position: x = %f, y = %f\n", state->dda->player_pos.x, state->dda->player_pos.y); // Debug print
		// line < 0
		while (row < state->dda->line.start && row < SCREENHEIGHT)
		{
			mlx_put_pixel(state->mlx->image, col_index, row, ft_pixel(0, 0, 255, 255));
			// mlx_put_pixel(state->mlx->image, row, col_index, ft_pixel(0, 0, 255, 255));
			row++;
		}

		printf("row: %d, line: %d, screen: %d\n", row, state->dda->line.end, SCREENHEIGHT);
		row = state->dda->line.end;  // + 1 misschien
		// line is meer dan screenheight
		while (row < SCREENHEIGHT && row >= 0)
		{
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
	state->dda->player_dir.x = values[0][0];
	state->dda->player_dir.y = values[0][1];
	state->dda->plane_x = values[0][2];
	state->dda->plane_y = values[0][3];

	dda(state);
	mlx_loop_hook(state->mlx->mlx, key_hook, (void *)state);
	mlx_loop(state->mlx->mlx);
	mlx_terminate(state->mlx->mlx);
}
