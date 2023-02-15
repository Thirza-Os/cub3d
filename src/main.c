#include "cub3d.h"


int	main(int argc, char *argv[])
{
	if (argc != 2)
		print_error("Invalid argument(s)");
	parse_input(argc, argv);
	// draw_game()
	return (0);
}

// int main(int argc, char *argv[])
// {
// 	main2(argc, argv);
// 	while(1);
// }