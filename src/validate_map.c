#include "cub3d.h"

int	check_characters(char *map)
{
	int		i;
	char	flag_player;

	i = 0;
	flag_player = '\0';
	while (map[i])
	{
		if ((ft_strchr(PLAYER_POS, map[i]) != NULL) && flag_player == '\0')
		{
			flag_player = map[i];
			i++;
		}
		if (ft_strchr(VALID_MAP_CHARS, map[i]) != NULL)
			i++;
		else
			print_error("Invalid map: wrong character input");
	}
	if (!flag_player)
		print_error("Invalid map: No player input");
	i = 0;
	while (g_positions[i])
	{
		if (*g_positions[i] == flag_player)
			break ;
		i++;
	}
	return (i);
}

void	find_max_xy(char *map, t_program *program)
{
	int	counter;
	int	max_y;
	int	max_x;
	int	max_x_counter;

	max_y = 1;
	max_x = 0;
	max_x_counter = 0;
	counter = 0;
	while (map[counter])
	{
		if (map[counter] != '\n')
			max_x_counter++;
		if (map[counter] == '\n')
		{
			max_y++;
			if (max_x_counter > max_x)
				max_x = max_x_counter;
			max_x_counter = 0;
		}
		counter++;
	}
	if (max_x_counter > max_x)
		max_x = max_x_counter;
	if (max_y < 3)
		print_error("Invalid map: Map not big enough");
	program->max_xy.y = max_y;
	program->max_xy.x = max_x;
}

void	fill_map(char *map, t_program *program)
{
	char	**temp_map;
	char	**dst_map;
	int		y_counter;

	y_counter = 0;
	temp_map = ft_split(map, '\n');
	dst_map = ft_calloc(program->max_xy.y, sizeof(char *));
	while (y_counter < program->max_xy.y)
	{
		dst_map[y_counter] = ft_calloc(program->max_xy.x + 1, sizeof(char));
		ft_memset(dst_map[y_counter], ' ', program->max_xy.x);
		ft_memcpy(dst_map[y_counter], temp_map[y_counter], \
			ft_strlen(temp_map[y_counter]));
		y_counter++;
	}
	ft_free(temp_map);
	free(map);
	program->map = dst_map;
}

void	validate_map(char *map, t_program *program)
{
	program->spawning_pos = check_characters(map);
	find_max_xy(map, program);
	fill_map(map, program);
	check_surrounded_walls(program);
}
