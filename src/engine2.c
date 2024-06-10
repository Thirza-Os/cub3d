/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   engine2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/08 18:06:51 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/10 19:05:25 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/engine.h"

static	bool	init_mlx(t_game_state *state)
{
	state->mlx->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "MLX42", true);
	if (!state->mlx->mlx)
	{
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (false);
	}
	state->mlx->image = mlx_new_image(
			state->mlx->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!state->mlx->image)
	{
		mlx_close_window(state->mlx->mlx);
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (false);
	}
	if (mlx_image_to_window(state->mlx->mlx, state->mlx->image, 0, 0) == -1)
	{
		mlx_close_window(state->mlx->mlx);
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (false);
	}
	return (true);
}

static	void	set_player_pos(t_game_state *state)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < state->map_size[0])
	{
		col = 0;
		while (col < state->map_size[1])
		{
			if (ft_strchr("NSEW", state->map[row][col]) != NULL)
			{
				state->player->faceing = state->map[row][col];
				state->player->pos[0] = row;
				state->player->pos[1] = col;
				return ;
			}
			col++;
		}
		row++;
	}
}

bool	err_handler(const char *msg, t_game_state *state)
{
	free_game_state(state);
	ft_putstr_fd("Failed to create a placeholder for ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (false);
}

bool	init_state(t_game_state *state)
{
	state->player = ft_calloc(1, sizeof(*state->player));
	if (state->player == NULL)
		return (err_handler("player", state));
	state->player->ray = ft_calloc(1, sizeof(*state->player->ray));
	if (state->player->ray == NULL)
		return (err_handler("ray", state));
	state->mlx = ft_calloc(1, sizeof(*state->mlx));
	if (state->mlx == NULL)
		return (err_handler("MLX", state));
	set_player_pos(state);
	if (init_mlx(state) != true)
	{
		free_game_state(state);
		return (NULL);
	}
	return (true);
}
