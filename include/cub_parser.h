/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parser.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:32:48 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/09/11 03:11:43 by lvan-gef      ########   odam.nl         */
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

/**
* @brief  A helper function to parse the input
*
* @param arg     The path to the map              (char*)
* @param program The current state of the program (t_program*)
*
* @return true | false
*/
bool	parser(char *arg, t_program *program);


/**
* @brief  Check if the path ends with .cub
*
* @param arg The path to the map (char*)
*
* @return true | false
*/
bool	check_cub(char *arg);

/**
* @brief  Tokenize the content of the map
*
* @param argv  The path to the map (char*)
*
* @return char** | NULL
*/
char	**tokenize_input(char *argv);

/**
* @brief  Check if we have all identifiers for the game
*
* @param elements The parsed elements (char**)
*
* @return true | false
*/
bool	validate_nr_of_identifiers(char **elements);

/**
* @brief  Check if image is a png file
*
* @param elements  The parsed elements              (char**)
* @param program   The current state of the program (t_program*)
*
* @return true | false
*/
bool	validate_paths(char **elements, t_program *program);

/**
* @brief  Check and set the rgb values for Floor and Ceiling
*
* @param elements  The parsed elements (char**)
* @param program   The current state of the program (t_program*)
*
* @return true | false
*/
bool	validate_rgb_input(char **elements, t_program *program);

/**
* @brief  Check if map is valid and set it
*
* @param map      The raw map (char*)
* @param program  The current state of the program (t_program*)
*
* @return true | false
*/
bool	validate_map(const char *map, t_program *program);

char	*_ft_strjoin_cub3d(char *s1, char const *s2);
char	*_parse_ident(char **elements, int index, const char *line);
bool	_check_rgb_input(char **elements);
bool	_check_token(const char *line, char **elements, bool flag);
bool	_check_chars(const char *map, char *start_dir);
bool	_create_map(t_program *program);
bool	_check_png(char *arg);
bool	_check_surrounded_walls(char **map);
int		_atorgb(const char *str);
void	_set_map(t_player *player, char **temp_map);

#endif
