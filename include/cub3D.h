/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:25 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/20 19:55:29 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "./cub_structs.h"
# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

bool	init_mlx(t_program *program);
void	clean_cub(void *data, int exit_code);
void	_clean_player(t_player *player);
void	_free_helper(char **str, char **str1);
void	free_char_arr(char **arr);
bool	clean_parser(char **elements, bool state);

#endif
