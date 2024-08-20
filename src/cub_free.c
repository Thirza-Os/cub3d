/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:13 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/20 21:29:42 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	free(dda);
}

void	_free_player(t_player *player)
{
	int	row;

	if (player == NULL)
		return ;
	if (player->map != NULL)
	{
		row = 0;
		while (row < player->max_map.row)
		{
			free(player->map[row]);
			row++;
		}
		free(player->map);
	}
	free(player);
}

void	free_cub(void *data, int exit_code)
{
	t_program	*program;
	int			index;

	program = data;
	if (program == NULL)
		return ;
	_clean_dda(program->dda);
	_clean_mlx(program->mlx_state);
	_free_player(program->player);
	index = 0;
	while (index < MAX_IMGS)
	{
		free(program->paths[index]);
		index++;
	}
	free(program);
	exit(exit_code);
}

void	_free_cub(void *data)
{
	free_cub(data, 0);
}
