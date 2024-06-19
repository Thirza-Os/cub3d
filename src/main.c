#include "../include/cub3d.h"
#include "../include/engine.h"
#include "libft.h"


// char	*map[] = {
// 	"111111",
// 	"100101",
// 	"101001",
// 	"1100N1",
// 	"100011",
// 	"111111"
// };

char *map = "111111\n100101\n101001\n1100N1\n100011\n11111\n";

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
	state->map = ft_calloc(1, sizeof(*state->map));
	state->map->map = ft_split(map, '\n');
	state->map->max_row = 6;
	state->map->max_col = 6;

	if (init_state(state) != true)
		return (EXIT_FAILURE);
	printf("player_x: %f, player_y: %f\n", state->player->pos.row, state->player->pos.col);
	printf("player facing: %c\n", state->player->faceing);
	run_game(state);
}
