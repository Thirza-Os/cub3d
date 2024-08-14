#include "cub3d.h"

// Offsets used to calculate the index of the neighboring cells.
// Add offset to x/y count = get the indices x/y neighbor.
static void	check_surrounding_pos(int y_count, int x_count, t_program *program)
{
	int	y_offset;
	int	x_offset;
	int	y_neighbor;
	int	x_neighbor;

	y_offset = -1;
	while (y_offset <= 1)
	{
		x_offset = -1;
		while (x_offset <= 1)
		{
			y_neighbor = y_count + y_offset;
			x_neighbor = x_count + x_offset;
			if (y_neighbor < 0 || y_neighbor >= program->max_xy.y \
				|| x_neighbor < 0 || x_neighbor >= program->max_xy.x \
					|| program->map[y_neighbor][x_neighbor] == ' ')
			{
				print_error("Map is not surrounded");
			}
			x_offset++;
		}
		y_offset++;
	}
}

// Player & 0: can not be surrounded by any blank spaces
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
