/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/27 21:28:19 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/07/31 21:57:11 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/engine.h"

void key_hook(void *param)
{
    t_game_state *state;

    state = param;
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(state->mlx->mlx);
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_UP))
    {
        if (state->map->map[(int)state->dda->player_pos.y - 1][(int)state->dda->player_pos.x] == '0') {
            state->dda->player_pos.y -= 1;
            printf("Moved up to: player_pos.y = %f\n", state->dda->player_pos.y); // Debug print
            dda(state);
        }
    }
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_DOWN))
    {
        if (state->map->map[(int)state->dda->player_pos.y + 1][(int)state->dda->player_pos.x] == '0') {
            state->dda->player_pos.y += 1;
            printf("Moved down to: player_pos.y = %f\n", state->dda->player_pos.y); // Debug print
            dda(state);
        }
    }
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_LEFT))
    {
        if (state->map->map[(int)state->dda->player_pos.y][(int)state->dda->player_pos.x - 1] == '0') {
            state->dda->player_pos.x -= 1;
            printf("Moved left to: player_pos.x = %f\n", state->dda->player_pos.x); // Debug print
            dda(state);
        }
    }
    if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_RIGHT))
    {
        if (state->map->map[(int)state->dda->player_pos.y][(int)state->dda->player_pos.x + 1] == '0') {
            state->dda->player_pos.x += 1;
            printf("Moved right to: player_pos.x = %f\n", state->dda->player_pos.x); // Debug print
            dda(state);
        }
    }
}
// void	key_hook(void *param)
// {
// 	t_game_state	*state;
//
// 	state = param;
// 	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(state->mlx->mlx);
// 	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_UP))
// 	{
// 		if (state->map->map[(int)state->dda->player_pos.y - 1][(int)state->dda->player_pos.x] == '0') {
// 			state->dda->player_pos.y -= 1;
// 			dda(state);
// 			printf("Hello up\n");
// 		}
// 	}
// 	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_DOWN))
// 	{
// 		if (state->map->map[(int)state->dda->player_pos.y + 1][(int)state->dda->player_pos.x] == '0') {
// 			state->dda->player_pos.y += 1;
// 			dda(state);
// 		}
// 	}
// 	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_LEFT))
// 	{
// 		if (state->map->map[(int)state->dda->player_pos.y][(int)state->dda->player_pos.x - 1] == '0') {
// 			state->dda->player_pos.x -= 1;
// 			dda(state);
// 		}
// 	}
// 	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_RIGHT))
// 	{
// 		if (state->map->map[(int)state->dda->player_pos.y][(int)state->dda->player_pos.x + 1] == '0') {
// 			state->dda->player_pos.x += 1;
// 			dda(state);
// 		}
// 	}
// }
