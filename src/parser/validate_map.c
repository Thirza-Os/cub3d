#include "../../include/cub_parser.h"
#include "libft.h"

static	int	check_characters(char *map, t_player *player) {
	static	const	char	*g_positions[] = G_POSITIONS;
	int						index;
	char					start_dir;

	index = 0;
	start_dir = player->starting_dir;
	while (map[index])
	{
		if ((ft_strchr(PLAYER_POS, map[index]) != NULL) && start_dir == '\0')
		{
			start_dir = map[index];
			index++;
		}
		if (ft_strchr(VALID_MAP_CHARS, map[index]) != NULL)
			index++;
		else
			return (-1);
			// print_error("Invalid map: wrong character input");
	}
	if (!start_dir)
		return (-1);
		// print_error("Invalid map: No player input");
	index = 0;
	while (g_positions[index])
	{
		if (*g_positions[index] == start_dir)
			break ;
		index++;
	}
	return (index);
}

static	bool	set_map_size(char *map, t_program *program)
{
	int	counter;
	int	max_row;
	int	max_col;
	int	max_x_counter;

	max_row = 0;
	max_col = 0;
	max_x_counter = 0;
	counter = 0;
	while (map[counter])
	{
		if (map[counter] != '\n')
			max_x_counter++;
		if (map[counter] == '\n')
		{
			max_row++;
			if (max_x_counter > max_col)
				max_col = max_x_counter;
			max_x_counter = 0;
		}
		counter++;
	}
	if (max_x_counter > max_col)
		max_col = max_x_counter;
	if (max_row < 3)
		return (false);
		// print_error("Invalid map: Map not big enough");
	program->player->max_map.row = max_row;
	program->player->max_map.col = max_col;
	return (true);
}

static	bool	fill_map(char *map, t_program *program)
{
	char	**temp_map;
	char	**dst_map;
	int		row;

	temp_map = ft_split(map, '\n');
	if (temp_map == NULL)
	{
		ft_putstr_fd("Failed to split the map\n", 2);
		return (false);
	}
	dst_map = ft_calloc(program->player->max_map.row + 1, sizeof(char *));
	if (dst_map == NULL)
	{
		ft_putstr_fd("Failed to calloc rows", 2);
		return (false);
	}
	row = 0;
	while (row < program->player->max_map.row)
	{
		dst_map[row] = ft_calloc(program->player->max_map.col + 1, sizeof(char));
		if (dst_map[row] == NULL)
		{
			ft_putstr_fd("Failed to calloc cols", 2);
			return (false);
		}
		ft_memset(dst_map[row], ' ', program->player->max_map.row);
		ft_memcpy(dst_map[row], temp_map[row], ft_strlen(temp_map[row]));
		row++;
	}
	// ft_free(temp_map);
	// free(map);
	program->player->map = dst_map;
	return (true);
}

static	bool	fill_player(t_program *program)
{
	int	count_col;
	int	count_row;

	count_row = 0;
	while (count_row < program->player->max_map.row)
	{
		count_col = 0;
		while (count_col < program->player->max_map.col)
		{
			if (ft_strchr(PLAYER_POS, program->player->map[count_row][count_col]) != NULL)
			{
				program->player->player_pos.col = count_col;
				program->player->player_pos.row = count_row;
				return (true);
			}
			count_col++;
		}
		count_row++;
	}
	ft_putstr_fd("Failed to find player position\n", 2);
	return (false);
}

bool	validate_map(char *map, t_program *program)
{
	int	pos;
	static	const	char	*g_positions[] = G_POSITIONS;

	pos = check_characters(map, program->player);
	if (pos == -1)
		return (false);
	program->player->starting_dir = *g_positions[pos];
	if (set_map_size(map, program) != true)
		return (false);
	if (fill_map(map, program) != true)
		return (false);
	if (fill_player(program) != true)
		return (false);
	if (check_surrounded_walls(program) != true)
		return (false);
	return (true);
}
