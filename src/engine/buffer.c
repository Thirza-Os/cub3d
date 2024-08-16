/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:01 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/16 03:11:03 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/dda.h"

static void	_set_floor_ceiling(uint32_t **buffer, t_dda *dda, t_player *player, int col)
{
	int	row;

	row = 0;
	while (row < dda->line.start && row < SCR_HEIGHT)
	{
		buffer[row][col] = player->ceiling_color;
		row++;
	}
	row = dda->line.end + 1;
	while (row < SCR_HEIGHT)
	{
		buffer[row][col] = player->floor_color;
		row++;
	}
}

void	fill_buffer(t_mlx_state *mlx_state, t_dda *dda, t_player *player, int col)
{
	_set_floor_ceiling(mlx_state->img_buffer, dda, player, col);
	textures(mlx_state, dda, col);
}
