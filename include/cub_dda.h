/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_dda.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:25 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/20 21:32:34 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_DDA_H
# define CUB_DDA_H

# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

# include "./cub_structs.h"
# include "../libft/include/libft.h"

t_dda	*init_dda(t_player *player);
void	render(void *data);
void	dda_info(t_dda *dda, t_player *player, int col);
void	textures(t_mlx_state *mlx_state, t_dda *dda, int col);
void	hooks(void *param);
bool	hit_wall(char **map, int row, int col);
void	fill_buffer(t_mlx_state *mlx_state, t_dda *dda, \
					const t_player *player, int col);

void	print_dda(const t_dda *dda);

#endif
