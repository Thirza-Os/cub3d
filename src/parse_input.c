#include "cub3d.h"

// handles one enter

void	validate_structure_paths(char **elements, t_program *program)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!check_png(elements[i]) || (ft_strncmp("./", elements[i], 2) != 0))
			print_error("Incorrect filepath input!");
		program->textures[i] = ft_strdup(elements[i]);
		free (elements[i]);
		i++;
	}
}

void	convert_digits(char **input, int *colors)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		colors[i] = ft_atorgb(input[i]);
		if (colors[i] < 0)
			print_error("Incorrect RGB input");
		i++;
	}
}

void	convert_rgb(char *input, int *colors)
{
	char	**split_elements;
	char	*temp;
	int		i;

	i = 0;
	split_elements = ft_split(input, ',');
	while (split_elements[i])
		i++;
	if (i != 3)
		print_error("Incorrect RGB input");
	i = 0;
	while (split_elements[i])
	{
		temp = ft_strtrim(split_elements[i], WHITESPACE);
		free(split_elements[i]);
		split_elements[i] = temp;
		i++;
	}
	convert_digits(split_elements, colors);
	ft_free(split_elements);
	free(input);
}

void	validate_rgb_input(char **elements, t_program *program)
{
	convert_rgb(elements[F], program->floor_rgb);
	convert_rgb(elements[C], program->ceiling_rgb);
}

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
// player & 0: can not be surrounded by any blank spaces
// Check only cells with 'N' or '0'
// Check if the surrounding point is out of bounds or empty
void	check_surrounded_walls(t_program *program)
{
	int	y_counter;
	int	x_counter;

	y_counter = 0;
	x_counter = 0;
	while (y_counter < program->max_xy.y)
	{
		x_counter = 0;
		while (x_counter < program->max_xy.x)
		{
			if (ft_strchr(PLAYER_POS, program->map[y_counter][x_counter]) != NULL || program->map[y_counter][x_counter] == '0') 
			{
				int di = -1;
				while (di <= 1) 
				{
					int dj = -1;
					while (dj <= 1) 
					{
						int ni = y_counter + di;
						int nj = x_counter + dj;
						if (ni < 0 || ni >= program->max_xy.y || nj < 0 || nj >= program->max_xy.x || program->map[ni][nj] == ' ') 
						{
							print_error("Map is not surrounded");
						}
						dj++;
					}
					di++;
				}
			}
			x_counter++;
		}
		y_counter++;
	}
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

void	validate_nr_of_identifiers(char **elements)
{
	int	i;

	i = 0;
	while (i < SIZE + 1)
	{
		if (elements[i] == NULL)
			print_error("Missing object input");
		i++;
	}
}

void	parse_input(char **elements)
{
	int			i;
	t_program	program;

	i = 0;
	validate_nr_of_identifiers(elements);
	validate_structure_paths(elements, &program);
	validate_rgb_input(elements, &program);
	validate_map(elements[SIZE], &program);
}

