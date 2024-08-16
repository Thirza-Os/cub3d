#ifndef CUB_PARSER_H
# define CUB_PARSER_H

#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#include "./cub_structs.h"

# include "../libft/include/libft.h"

bool	parser(char *arg, t_program *program);
bool	check_cub(char *arg);
char	**tokenize_input(char *argv);
bool	validate_nr_of_identifiers(char **elements);
bool	validate_structure_paths(char **elements, t_program *program);
bool	check_png(char *arg);
int		ft_atorgb(const char *str);
bool	validate_rgb_input(char **elements, t_program *program);
bool	validate_map(char *map, t_program *program);
bool	check_surrounded_walls(t_program *program);

#endif
