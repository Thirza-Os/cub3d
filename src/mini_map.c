#include "../include/engine.h"


static	draw_player(t_game_state *state)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < 2)
	{
		col = 0;
		while (col < 2)
		{
			col++;
		}
		row++;
	}
}

bool	init_mini_map(t_game_state *state)
{
	state->mlx->mini_map = mlx_new_image(
			state->mlx->mlx, SCREENWIDTH / 3, SCREENHEIGHT / 3);
	if (!state->mlx->mini_map)
	{
		mlx_close_window(state->mlx->mlx);
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (false);
	}
	if (mlx_image_to_window(state->mlx->mlx, state->mlx->mini_map, 0, 0) == -1)
	{
		mlx_close_window(state->mlx->mlx);
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (false);
	}


	return (true);
}
