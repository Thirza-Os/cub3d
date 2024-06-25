#include "../include/engine.h"

void	dda_loop(void *param)
{
	t_game_state	*state;
	int				col;

	state = param;
	col = 0;
	while (col < SCREENWIDTH)
	{
		dda_per_x(state, col);
		draw_info_calc(state);
		print_dda(state->dda);
		col++;
	}
}
