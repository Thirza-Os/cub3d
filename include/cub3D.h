/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 03:48:59 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/09 04:36:26 by lvan-gef      ########   odam.nl         */
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
void	clean_cub(t_program *program, t_player *player);

#endif
