#include "cub3d.h"

// map bigger than int max??

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
	program->floor_rgb = (int *)malloc(sizeof (int));  //1 (16 bytes) ROOT LEAK: 0x7f9946e0dac0 [16]
	program->ceiling_rgb = (int *)malloc(sizeof (int)); // 1 (16 bytes) ROOT LEAK: 0x7f9946e0dac0 [16]
	convert_rgb(elements[F], program->floor_rgb);
	convert_rgb(elements[C], program->ceiling_rgb);
}

// void	fill_gaps(char *map)
// {
// 	int	i;

// 	i = 0;
// 	while (map[i])
// 	{
// 		if (map[i] == ' ')
// 			map[i] = '1';
// 		i++;
// 	}
// 	printf("%s\n", map);
// }

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
	int max_x;
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
// map: surrounded by walls!!
// player: surrounded by 1/0??


// if ANY of surrounding 8 are whitespace/not 0/N/E/W/S = it must be a 1

void	check_surrounded_walls(char *map, t_program *program)
{
	int	num_elements;
	int	x;
	int y;
	int left;
	int right;
	int bottom;
	int top;

	num_elements = program->max_xy.x * program->max_xy.y;

	while (i < num_elements)
	{
		x = i % program->max_xy.x;
		y = i % program->max_xy.x;

		// Left (what if it does not exist: seg?)
		if (x > 0)
		{
			left = i - 1;
			if (map[left] != ' ' && left >=0)
				if (map [i])
		}
	}
}

void	validate_map(char *map, t_program *program)
{
	program->spawning_pos = check_characters(map);
	find_max_xy(map, program);
	printf("%i\n", program->max_xy.x);
	printf("%i\n", program->max_xy.y);
	check_surrounded_walls(map, program);
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
		// parse_textures(elements);
}

