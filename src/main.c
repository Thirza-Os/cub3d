#include "../include/cub3d.h"
#include "../include/engine.h"


char	*map[] = {
	"111111",
	"100101",
	"101001",
	"1100N1",
	"111111"
};


int	main(int argc, char *argv[])
{
	t_game_state	*state;
	(void)argc;
	(void)argv;
	// if (argc != 2)
	// 	print_error("Invalid argument(s)");
	// // parse_input(argc, argv);
	// // draw_game()
	// return (0);

	state = ft_calloc(1, sizeof(*state));
	if (state == NULL)
	{
		err_handler("state", state);
		return (EXIT_FAILURE);
	}
	state->map = map;
	state->map_size[0] = 6;
	state->map_size[1] = 5;
	if (init_state(state) != true)
		return (EXIT_FAILURE);
	printf("player_x: %f, player_y: %f\n", state->player->pos.row, state->player->pos.col);
	printf("player facing: %c\n", state->player->faceing);
	run_game(state);
}
