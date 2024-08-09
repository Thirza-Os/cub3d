/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 01:11:31 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/09 02:45:32 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static	void	_clean_mlx(t_mlx_state *mlx_state)
{
	size_t	row;

	if (mlx_state == NULL)
		return ;
	mlx_delete_image(mlx_state->mlx, mlx_state->img);
	mlx_terminate(mlx_state->mlx);
	if (mlx_state->img_buffer != NULL)
	{
		row = 0;
		while (row < SCR_WIDTH && mlx_state->img_buffer[row] != NULL)
		{
			free(mlx_state->img_buffer[row]);
			row++;
		}
		free(mlx_state->img_buffer);
	}
	row = 0;
	while (row < MAX_IMGS)
	{
		if (mlx_state->textures[row] != NULL)
			mlx_delete_texture(mlx_state->textures[row]);
		row++;
	}
	free(mlx_state);
}

static	void	_clean_player(t_player *player)
{
	size_t	row;

	if (player == NULL)
		return ;
	if (player->map != NULL)
	{
		row = 0;
		while (row < player->row_size)
		{
			free(player->map[row]);
			row++;
		}
		free(player->map);
	}
	free(player);
}

static	void	_clean_dda(t_dda *dda)
{
	if (dda == NULL)
		return ;
	free(dda);
}

void	clean_cub(t_program *program, t_player *player)
{
	if (program == NULL)
		return ;
	_clean_mlx(program->mlx_state);
	_clean_player(player);
	_clean_dda(program->dda);
	free(program);
}
