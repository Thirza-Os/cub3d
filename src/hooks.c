#include "../include/engine.h"

void key_hook(void *param)
{
	t_game_state *state = param;

	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(state->mlx->mlx);
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_UP))
	{
		printf("move up\n");
		state->mlx->image->instances[0].y -= 1;
	}
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_DOWN))
	{
		printf("move down\n");
		state->mlx->image->instances[0].y += 1;
	}
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_LEFT))
	{
		printf("move left\n");
		state->mlx->image->instances[0].x -= 1;
	}
	if (mlx_is_key_down(state->mlx->mlx, MLX_KEY_RIGHT))
	{
		printf("move right\n");
		state->mlx->image->instances[0].x += 1;
	}
}
