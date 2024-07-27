/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/27 21:28:19 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/07/27 21:57:52 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/engine.h"

void	key_hook(void *param)
{
	t_game_state	*state;

	state = param;
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(state->mlx->mlx);
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_UP))
	{
		state->dda->player_pos.y -= 1;
		dda(state);
	}
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_DOWN))
	{
		state->dda->player_pos.y += 1;
		dda(state);
	}
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_LEFT))
	{
		if (state->dda->map_pos.x - 1 != 1) {
			state->dda->player_pos.x -= 1;
			state->dda->map_pos.x -= 1;
			dda(state);
		}
	}
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_RIGHT))
	{
		if (state->dda->map_pos.x + 1 != 1) {
			state->dda->player_pos.x += 1;
			state->dda->map_pos.x += 1;
			dda(state);
		}
	}
}
