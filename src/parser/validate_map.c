/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by tosinga       #+#    #+#                 */
/*   Updated: 2024/08/22 16:12:26 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "libft.h"

static	int	check_characters(char const *map, const char *g_positions[])
{
	int					index;
	char				start_dir;

	start_dir = '\0';
	if (_check_chars(map, &start_dir) != true)
		return (-1);
	if (start_dir == '\0')
	{
		ft_putendl_fd("Invalid map: No Player", 2);
		return (-1);
	}
	index = 0;
	while (g_positions[index])
	{
		if (*g_positions[index] == start_dir)
			break ;
		index++;
	}
	return (index);
}

static	bool	set_map_size(char const *map, t_program *program)
{
	size_t		counter;
	size_t		col;
	t_player	*player;

	counter = 0;
	col = 0;
	player = program->player;
	while (map[counter] != '\0')
	{
		if (map[counter] == '\n')
		{
			player->max_map.row++;
			if ((int)col > player->max_map.col)
				player->max_map.col = col;
			col = 0;
		}
		else
			col++;
		counter++;
	}
	if (player->max_map.row < 3)
		return (false);
	return (true);
}

static	bool	fill_map(char const *map, t_program *program)
{
	char		**temp_map;
	int			row;
	t_player	*player;

	player = program->player;
	temp_map = ft_split(map, '\n');
	if (temp_map == NULL)
	{
		ft_putstr_fd("Failed to split the map\n", 2);
		return (false);
	}
	if (_create_map(program) != true)
		return (false);
	row = 0;
	while (row < player->max_map.row)
	{
		ft_memcpy(player->map[row], temp_map[row], ft_strlen(temp_map[row]));
		_replace_spaces(player, row, temp_map);
		row++;
	}
	free_char_arr(temp_map);
	return (true);
}

static	bool	fill_player(t_program *program)
{
	int	col;
	int	row;

	row = 0;
	while (row < program->player->max_map.row)
	{
		col = 0;
		while (col < program->player->max_map.col)
		{
			if (ft_strchr(PLAYER_POS, program->player->map[row][col]) != NULL)
			{
				program->player->player_pos.col = col;
				program->player->player_pos.row = row;
				return (true);
			}
			col++;
		}
		row++;
	}
	ft_putstr_fd("Failed to find player position\n", 2);
	return (false);
}

bool	validate_map(char const *map, t_program *program)
{
	int					pos;
	static const char	*g_positions[] = {"N", "S", "W", "E"};

	pos = check_characters(map, g_positions);
	if (pos == -1)
		return (false);
	program->player->starting_dir = *g_positions[pos];
	if (set_map_size(map, program) != true)
	{
		ft_putendl_fd("Map is to small to play...", 2);
		return (false);
	}
	if (fill_map(map, program) != true)
		return (false);
	if (fill_player(program) != true)
		return (false);
	if (check_surrounded_walls(program) != true)
	{
		ft_putstr_fd("Map is not surrounded\n", 2);
		return (false);
	}
	return (true);
}
