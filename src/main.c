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

// char *map = "111111\n100101\n101001\n1100N1\n100011\n11111\n";
char *map = "\
111111111111111111111111\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000111110000101010001\n\
100000100010000000000001\n\
100000100010000100010001\n\
100000100010000000000001\n\
100000110110000101010001\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000000000000000000001\n\
111111111000000000000001\n\
110100001000000000000001\n\
110000101000000000000001\n\
110100001000000000000001\n\
110111111000000000000001\n\
110000000000000000000001\n\
111111111000000000000001\n\
111111111111111111111111\n";

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
	state->map->max_row = 24;
	state->map->max_col = 24;

	if (init_state(state) != true)
		return (EXIT_FAILURE);
	printf("player_x: %f, player_y: %f\n", state->player->pos.y, state->player->pos.x);
	printf("player facing: %c\n", state->player->faceing);
	run_game(state);
	printf("Hello\n");
}
