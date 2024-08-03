/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/27 21:28:19 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/03 22:10:54 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/engine.h"

static bool	hitting_wall(t_game_state *state, int x, int y)
{
	if (state->map->map[y][x] != '0')
		return (true);
	return (false);
}

void key_hook(void *param)
{
    t_game_state *state;

    state = param;
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(state->mlx->mlx);

    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_W))
    {
		double	current_pos_x;
		double	dx;
		double	dy;
		double	spacing;

		current_pos_x = state->dda->player_pos.x;
		dx = state->dda->player_dir.x * MOVESPEED * 1;
		if (dx > 0)
			spacing = 0.32;
		else
			spacing = -0.32;
		if (!hitting_wall(state, state->dda->player_pos.x + dx + spacing, state->dda->player_pos.y))
			state->dda->player_pos.x += dx;

		dy = state->dda->player_dir.y * MOVESPEED * 1;
		if (dy > 0)
			spacing = 0.32;
		else
			spacing = -0.32;
		if (!hitting_wall(state, current_pos_x, state->dda->player_pos.y + dy + spacing))
			state->dda->player_pos.y += dy;

		dda(state);
    }
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_S)) {
		double	current_pos_x;
		double	dx;
		double	dy;
		double	spacing;

		current_pos_x = state->dda->player_pos.x;
		dx = state->dda->player_dir.x * MOVESPEED * -1;
		if (dx > 0)
			spacing = 0.32;
		else
			spacing = -0.32;
		if (!hitting_wall(state, state->dda->player_pos.x + dx + spacing, state->dda->player_pos.y))
			state->dda->player_pos.x += dx;

		dy = state->dda->player_dir.y * MOVESPEED * -1;
		if (dy > 0)
			spacing = 0.32;
		else
			spacing = -0.32;
		if (!hitting_wall(state, current_pos_x, state->dda->player_pos.y + dy + spacing))
			state->dda->player_pos.y += dy;

		dda(state);
	}

    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_A))
    {
		double	current_pos_x;
		double	dx;
		double	dy;
		double	spacing;

		current_pos_x = state->dda->player_pos.x;
		dx = -(state->dda->player_dir.y * MOVESPEED * -1);
		if (dx > 0)
			spacing = 0.32;
		else
			spacing = -0.32;
		if (!hitting_wall(state, state->dda->player_pos.x + dx + spacing, state->dda->player_pos.y))
			state->dda->player_pos.x += dx;
		dy = state->dda->player_dir.x * MOVESPEED * -1;
		if (dy > 0)
			spacing = 0.32;
		else
			spacing = -0.32;
		if (!hitting_wall(state, current_pos_x, state->dda->player_pos.y + dy + spacing))
			state->dda->player_pos.y += dy;
		dda(state);

	}

    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_D))
    {	double	current_pos_x;
		double	dx;
		double	dy;
		double	spacing;

		current_pos_x = state->dda->player_pos.x;
		dx = -(state->dda->player_dir.y * MOVESPEED * 1);
		if (dx > 0)
			spacing = 0.32;
		else
			spacing = -0.32;
		if (!hitting_wall(state, state->dda->player_pos.x + dx + spacing, state->dda->player_pos.y))
			state->dda->player_pos.x += dx;
		dy = state->dda->player_dir.x * MOVESPEED * 1;
		if (dy > 0)
			spacing = 0.32;
		else
			spacing = -0.32;
		if (!hitting_wall(state, current_pos_x, state->dda->player_pos.y + dy + spacing))
			state->dda->player_pos.y += dy;
		dda(state);

	}

    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_LEFT)) {
		t_vector old_dir;
		double	 old_plane_x;
		int dir = -1;

		old_dir.x = state->dda->player_dir.x;
		state->dda->player_dir.x = state->dda->player_dir.x * cos(ROTSPEED * dir) - state->dda->player_dir.y * sin(ROTSPEED * dir);
		state->dda->player_dir.y = old_dir.x * sin(ROTSPEED * dir) + state->dda->player_dir.y * cos(ROTSPEED * dir);
		old_plane_x = state->dda->plane_x;
		state->dda->plane_x = state->dda->plane_x * cos(ROTSPEED * dir) - state->dda->plane_y * sin(ROTSPEED * dir);
		state->dda->plane_y = old_plane_x * sin(ROTSPEED * dir) + state->dda->plane_y * cos(ROTSPEED * dir);

		dda(state);
	}

	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_RIGHT)) {
		t_vector old_dir;
		double	 old_plane_x;
		int dir = 1;

		old_dir.x = state->dda->player_dir.x;
		state->dda->player_dir.x = state->dda->player_dir.x * cos(ROTSPEED * dir) - state->dda->player_dir.y * sin(ROTSPEED * dir);
		state->dda->player_dir.y = old_dir.x * sin(ROTSPEED * dir) + state->dda->player_dir.y * cos(ROTSPEED * dir);
		old_plane_x = state->dda->plane_x;
		state->dda->plane_x = state->dda->plane_x * cos(ROTSPEED * dir) - state->dda->plane_y * sin(ROTSPEED * dir);
		state->dda->plane_y = old_plane_x * sin(ROTSPEED * dir) + state->dda->plane_y * cos(ROTSPEED * dir);

		dda(state);
	}
}
