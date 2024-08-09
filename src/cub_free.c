/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 01:11:31 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/09 22:19:01 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include "cub_structs.h"

static	void	_clean_mlx(t_mlx_state *mlx_state)
{
	size_t	row;

	if (mlx_state == NULL)
		return ;
	mlx_delete_image(mlx_state->mlx, mlx_state->img);
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
	mlx_close_window(mlx_state->mlx);
	mlx_terminate(mlx_state->mlx);
	free(mlx_state);
}


static	void	_clean_dda(t_dda *dda)
{
	if (dda == NULL)
		return ;
	_clean_player(dda->player);
	free(dda);
}

void	_clean_player(t_player *player)
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

void	clean_cub(void *data)
{
	t_program	*program;

	program = data;
	if (program == NULL)
		return ;
	_clean_dda(program->dda);
	_clean_mlx(program->mlx_state);
	free(program);
	exit(0);
}
