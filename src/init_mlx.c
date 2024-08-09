/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:23:54 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/09 22:24:02 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static	bool	_init_buffer(t_mlx_state *mlx_state)
{
	int	row;

	mlx_state->img_buffer = ft_calloc(SCR_HEIGHT + 1, sizeof(uint32_t *));
	if (mlx_state->img_buffer == NULL)
	{
		perror("img_buffer rows");
		return (false);
	}
	row = 0;
	while (row < SCR_HEIGHT)
	{
		mlx_state->img_buffer[row] = ft_calloc(SCR_WIDTH + 1, sizeof(uint32_t));
		if (mlx_state->img_buffer[row] == NULL)
		{
			perror("img_buffer cols");
			return (false);
		}
		row++;
	}
	return true;
}

static	bool	_init_texture(t_mlx_state *mlx_state, char **paths)
{
	size_t	index;

	index = 0;
	while (index < MAX_IMGS)
	{
		mlx_state->textures[index] = mlx_load_png(paths[index]);
		if (mlx_state->textures[index] == NULL)
		{
			perror(mlx_strerror(mlx_errno));
			return false;
		}
		index++;
	}
	return (true);
}

bool	init_mlx(t_program *program)
{
	program->mlx_state = ft_calloc(1, sizeof(*program->mlx_state));
	if (program->mlx_state == NULL)
	{
		perror("init mlx_state");
		return (false);
	}
	program->mlx_state->mlx = mlx_init(SCR_WIDTH, SCR_HEIGHT, "test", true);
	if (!program->mlx_state->mlx)
	{
		perror(mlx_strerror(mlx_errno));
		return (false);
	}
	program->mlx_state->img = mlx_new_image(program->mlx_state->mlx, SCR_WIDTH, SCR_HEIGHT);
	if (!program->mlx_state->img)
	{
		perror(mlx_strerror(mlx_errno));
		return (false);
	}
	if (mlx_image_to_window(program->mlx_state->mlx, program->mlx_state->img, 0, 0) == -1)
	{
		perror(mlx_strerror(mlx_errno));
		return (false);
	}
	if (_init_buffer(program->mlx_state) != true)
		return (false);
	if (_init_texture(program->mlx_state, program->paths) != true)
		return (false);
	return (true);
}
