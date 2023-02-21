#include "cub3d.h"

static void	check_surrounding_pos(int y_count, int x_count, t_program *program)
{
	int	di;
	int	dj;
	int	ni;
	int	nj;

	di = -1;
	while (di <= 1)
	{
		dj = -1;
		while (dj <= 1)
		{
			ni = y_count + di;
			nj = x_count + dj;
			if (ni < 0 || ni >= program->max_xy.y || nj < 0 || \
				nj >= program->max_xy.x || program->map[ni][nj] == ' ')
			{
				print_error("Map is not surrounded");
			}
			dj++;
		}
		di++;
	}
}

// player & 0: can not be surrounded by any blank spaces
// Check only cells with 'N' or '0'
// Check if the surrounding point is out of bounds or empty
void	check_surrounded_walls(t_program *program)
{
	int	y_count;
	int	x_count;

	y_count = 0;
	x_count = 0;
	while (y_count < program->max_xy.y)
	{
		x_count = 0;
		while (x_count < program->max_xy.x)
		{
			if (ft_strchr(PLAYER_POS, program->map[y_count][x_count]) != NULL \
				|| program->map[y_count][x_count] == '0')
				check_surrounding_pos(y_count, x_count, program);
			x_count++;
		}
		y_count++;
	}
}
