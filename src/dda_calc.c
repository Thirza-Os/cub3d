#include "../include/engine.h"

static void	set_step_and_sidedist(t_dda *dda)
{
	if (dda->ray_dir.col < 0)
	{
		dda->step_map_x = -1;
		dda->side_dist_x = \
				(dda->player_pos.col - dda->map_pos.x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_map_x = 1;
		dda->side_dist_x = (dda->map_pos.x + 1 - dda->player_pos.col) * dda->delta_dist_x;
	}
	if (dda->ray_dir.row < 0)
	{
		dda->step_map_y = -1;
		dda->side_dist_y = (dda->player_pos.row - dda->map_pos.y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_map_y = 1;
		dda->side_dist_y = (dda->map_pos.y + 1 - dda->player_pos.row) * dda->delta_dist_y;
	}
}

static void	loop_till_collision(t_game_state *state)
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
		if (state->map->map[dda->map_pos.y][dda->map_pos.x] == '1')
			break ;
	}
}

void	dda_per_x(t_game_state *game, int x)
{
	t_dda	*dda;

	dda = game->dda;
	dda->camera_x = 2 * (x / (double)SCREENWIDTH) - 1;
	dda->ray_dir.col = dda->player_dir.col + (dda->plane_x * dda->camera_x);
	dda->ray_dir.row = dda->player_dir.row + (dda->plane_y * dda->camera_x);
	dda->map_pos.x = (int)dda->player_pos.col;
	dda->map_pos.y = (int)dda->player_pos.row;
	if (dda->ray_dir.col == 0)
		dda->delta_dist_x = INT32_MAX;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir.col);
	if (dda->ray_dir.row == 0)
		dda->delta_dist_y = INT32_MAX;
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir.row);
	set_step_and_sidedist(dda);
	loop_till_collision(game);
}

void	draw_info_calc(t_game_state *state)
{
	double	perp_wall_dist_inverse;
	t_dda	*dda;

	dda = state->dda;
	if (dda->current_side == 1)
		dda->prep_wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dda->prep_wall_dist = dda->side_dist_y - dda->delta_dist_y;
	perp_wall_dist_inverse = 1 / dda->prep_wall_dist;
	if (perp_wall_dist_inverse == INFINITY)
		dda->line.heigth = SCREENHEIGHT;
	else
		dda->line.heigth = (int)(perp_wall_dist_inverse * SCREENHEIGHT);
	dda->line.start = (SCREENHEIGHT / 2) - (dda->line.heigth / 2);
	dda->line.end = (SCREENHEIGHT / 2) + (dda->line.heigth / 2);
}
