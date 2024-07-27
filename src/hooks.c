/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/27 21:28:19 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/07/27 21:29:08 by lvan-gef      ########   odam.nl         */
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
	}
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_DOWN))
	{
		state->dda->player_pos.y += 1;
		dda(state);
	}
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_LEFT))
	{
		state->mlx->image->instances[0].x -= 1;
	}
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_RIGHT))
	{
		state->mlx->image->instances[0].x += 1;
	}
}
