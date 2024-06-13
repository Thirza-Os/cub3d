/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_me.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/08 18:38:41 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 19:07:22 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static	void	free_player(t_player *player)
{
	if (player == NULL)
		return ;
	if (player->dda == NULL)
		return ;
	free(player->dda);
	free(player);
}

static	void	free_mlx(t_mlx_state *mlx)
{
	if (mlx == NULL)
		return ;
	mlx_terminate(mlx->mlx);
}

void	free_game_state(t_game_state *state)
{
	if (state == NULL)
		return ;
	free_player(state->player);
	free_mlx(state->mlx);
}
