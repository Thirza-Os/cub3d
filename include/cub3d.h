/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:25 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/09/11 03:19:21 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "./cub_dda.h"
# include "./cub_parser.h"
# include "./cub_structs.h"

# include "../libft/include/libft.h"

# include "../MLX42/include/MLX42/MLX42.h"

/**
* @brief  Init mlx and the resources
*
* @param program The state of the program (t_program*)
*
* @return true | false
*/
bool	init_mlx(t_program *program);

/**
* @brief  free the memory of the program and set the exit code
*
* @param data      The state of the program(t_program*) as a (void*)
* @param exit_code The code which the program ends with (int)
*/
void	free_cub(void *data, int exit_code);

/**
* @brief  Free a char array
*
* @param arr The array to be set free (char**)
*/
void	free_char_arr(char **arr);

void	_free_player(t_player *player);
void	_free_cub(void *data);

#endif
