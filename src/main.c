#include "cub3d.h"
#include "../engine.h"

void	drawgame(t_program *program);

int	main(int argc, char *argv[])
{
	t_program	program;
	if (argc != 2)
		print_error("Invalid argument(s)");
	program = parser(argv);
	drawgame(&program);
	return (0);
}