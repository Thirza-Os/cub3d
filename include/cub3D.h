/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 03:48:59 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/09 03:49:01 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"

# include "./cub_structs.h"

bool	init_mlx(t_program *program);
void	clean_cub(t_program *program, t_player *player);

#endif
