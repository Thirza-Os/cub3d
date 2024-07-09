#include "../include/engine.h"

void	pre_dda_values_init(t_game_state *state)
{
	int				i;
	const char		dirs[4] = "NESW";
	const double	values[4][4] = {{0, -1, 0.66, 0}, {1, 0, 0, 0.66}, \
									{0, 1, -0.66, 0}, {-1, 0, 0, -0.66}};
	t_dda	*dda;

	i = 0;
	dda = state->dda;
	while (i < 4)
	{
		if (dirs[i] == state->player->faceing)
		{
			dda->player_dir.col = values[i][0];
			dda->player_dir.row = values[i][1];
			dda->plane_x = values[i][2];
			dda->plane_y = values[i][3];
			break ;
		}
		i++;
	}
    state->dda = dda;
}

bool	dda_init(t_game_state *state)
{
	t_dda	*dda;

	dda = ft_calloc(1, sizeof(*state->dda));
	if (dda == NULL)
	{
		ft_putendl_fd("Failed to create a placeholder for dda", 2);
		return (false);
	}
	dda->player_pos.col = state->player->pos.col + 0.5;
	dda->player_pos.row = state->player->pos.row + 0.5;
	const double	values[4][4] = {{0, -1, 0.66, 0}, {1, 0, 0, 0.66}, \
									{0, 1, -0.66, 0}, {-1, 0, 0, -0.66}};
    dda->player_dir.col = values[0][0];
    dda->player_dir.row = values[0][1];
    dda->plane_x = values[0][2];
    dda->plane_y = values[0][3];
    state->dda = dda;
    printf("waarom??? %f,%f\n", state->dda->plane_y, state->dda->plane_x);
	// pre_dda_values_init(state);
	// if (set_texture_struct(dda))
	// {
	// 	print_error("texture fail\n");
	// 	return (NULL);
	// }
	return (true);
}
