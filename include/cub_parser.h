/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parser.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:32:48 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/24 02:39:22 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_PARSER_H
# define CUB_PARSER_H

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

# include "./cub_structs.h"

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
char	*ft_strjoin_cub3d(char *s1, char const *s2);
char	*_parse_ident(char **elements, int index, const char *line);

bool	_check_rgb_input(char **elements);
bool	_check_token(const char *line, char **elements, bool flag);
bool	_check_chars(char *map, char *start_dir);
bool	_create_map(t_program *program);
void	_set_map(t_player *player, char **temp_map);

#endif
