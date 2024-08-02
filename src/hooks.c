/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/27 21:28:19 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/02 20:53:03 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/engine.h"
#include <math.h>

void key_hook(void *param)
{
    t_game_state *state;

    state = param;
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(state->mlx->mlx);
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_W))
    {
        if (state->map->map[(int)state->dda->player_pos.y + 1][(int)state->dda->player_pos.x] == '0') {
			// double	current_pos_x;
			double	dx;
			double	dy;
			// double	spacing;

			// current_pos_x = state->dda->player_pos.x;
			dx = state->dda->player_dir.x * MOVESPEED * 1;
			// if (dx > 0)
			// 	spacing = 0.32;
			// else
			// 	spacing = -0.32;
			state->dda->player_pos.x += dx;
			dy = state->dda->player_dir.y * MOVESPEED * 1;
			// if (dy > 0)
			// 	spacing = 0.32;
			// else
			// 	spacing = -0.32;
			state->dda->player_pos.y += dy;
			dda(state);
        }
    }
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_S))
    {
        if (state->map->map[(int)state->dda->player_pos.y + 1][(int)state->dda->player_pos.x] == '0') {
			// double	current_pos_x;
			double	dx;
			double	dy;
			// double	spacing;

			// current_pos_x = state->dda->player_pos.x;
			dx = state->dda->player_dir.x * MOVESPEED * 1;
			// if (dx > 0)
			// 	spacing = 0.32;
			// else
			// 	spacing = -0.32;
			state->dda->player_pos.x -= dx;
			dy = state->dda->player_dir.y * MOVESPEED * 1;
			// if (dy > 0)
			// 	spacing = 0.32;
			// else
			// 	spacing = -0.32;
			state->dda->player_pos.y -= dy;
			dda(state);
        }
    }
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_A))
    {
        if (state->map->map[(int)state->dda->player_pos.y][(int)state->dda->player_pos.x - 1] == '0') {
			// double	current_pos_x;
			double	dx;
			double	dy;
			// double	spacing;

			// current_pos_x = dda->player_pos.x;
			dx = -(state->dda->player_dir.y * MOVESPEED * 1);
			// if (dx > 0)
			// 	spacing = 0.32;
			// else
			// 	spacing = -0.32;
			state->dda->player_pos.x -= dx;
			dy = state->dda->player_dir.x * MOVESPEED * 1;
			// if (dy > 0)
			// 	spacing = 0.32;
			// else
			// 	spacing = -0.32;
			state->dda->player_pos.y -= dy;

            dda(state);
        }
    }
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_D))
    {
        if (state->map->map[(int)state->dda->player_pos.y][(int)state->dda->player_pos.x + 1] == '0') {
			// double	current_pos_x;
			double	dx;
			double	dy;
			// double	spacing;

			// current_pos_x = dda->player_pos.x;
			dx = -(state->dda->player_dir.y * MOVESPEED * 1);
			// if (dx > 0)
			// 	spacing = 0.32;
			// else
			// 	spacing = -0.32;
			state->dda->player_pos.x += dx;
			dy = state->dda->player_dir.x * MOVESPEED * 1;
			// if (dy > 0)
			// 	spacing = 0.32;
			// else
			// 	spacing = -0.32;
			state->dda->player_pos.y += dy;

            dda(state);
            // state->dda->player_pos.x += 1;
            // printf("Moved right to: player_pos.x = %f\n", state->dda->player_pos.x); // Debug print
            // dda(state);
        }
    }
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_LEFT)) {
		printf("Draai links\n");
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
		printf("Draai rechts\n");
		t_vector old_dir;
		double	 old_plane_x;
		int dir = 1;


		old_dir.x = state->dda->player_dir.x;
		state->dda->player_dir.x = state->dda->player_dir.x * cos(ROTSPEED * dir) - \
			state->dda->player_dir.y * sin(ROTSPEED * dir);
		state->dda->player_dir.y = old_dir.x * sin(ROTSPEED * dir) + \
			state->dda->player_dir.y * cos(ROTSPEED * dir);
		old_plane_x = state->dda->plane_x;
		state->dda->plane_x = state->dda->plane_x * cos(ROTSPEED * dir) - \
			state->dda->plane_y * sin(ROTSPEED * dir);
		state->dda->plane_y = old_plane_x * sin(ROTSPEED * dir) + \
			state->dda->plane_y * cos(ROTSPEED * dir);

		dda(state);
	}
}
