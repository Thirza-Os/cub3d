#include "../../include/cub_parser.h"
#include "cub_structs.h"

// Offsets used to calculate the index of the neighboring cells.
// Add offset to x/y count = get the indices x/y neighbor.
static	bool	check_surrounding_pos(int row, int col, t_program *program)
{
	int			row_offset;
	int			col_offset;
	int			row_neighbor;
	int			col_neighbor;
	t_ivector	max_map;

	max_map = program->player->max_map;
	row_offset = -1;
	while (row_offset <= 1)
	{
		col_offset = -1;
		while (col_offset <= 1)
		{
			row_neighbor = row + row_offset;
			col_neighbor = col + col_offset;
			if (row_neighbor < 0 || row_neighbor > max_map.row \
				|| col_neighbor < 0 || col_neighbor > max_map.col \
					|| program->player->map[row_neighbor][col_neighbor] == ' ')
				return (false);
			col_offset++;
		}
		row_offset++;
	}
	return (true);
}

// Player & 0: can not be surrounded by any blank spaces
// Check only cells with 'N' or '0'
// Check if the surrounding point is out of bounds or empty
bool	check_surrounded_walls(t_program *program)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row < program->player->max_map.row)
	{
		col = 0;
		if (program->player->map[row] == NULL)
			break ;
		while (col < program->player->max_map.col)
		{
			if (ft_strchr(PLAYER_POS, program->player->map[row][col]) != NULL \
				|| program->player->map[row][col] == '0')
			{
				if (check_surrounding_pos(row, col, program) != true)
					return (false);
			}
			col++;
		}
		row++;
	}
	return (true);
}
