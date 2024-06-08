#include "../include/cub3d.h"
#include "../include/engine.h"

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
	if (init_state(state) != true)
		return (EXIT_FAILURE);
}
