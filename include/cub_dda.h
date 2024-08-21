/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_dda.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:25 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/21 03:47:39 by lvan-gef      ########   odam.nl         */
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

/**
* @brief  Init the dda struct with default values
*
* @param player The current state of player (t_player*)
*
* @return t_dda* | NULL
*/
t_dda	*init_dda(t_player *player);

/**
* @brief  The main loop of the program
*
* @param data The current state of program (void*)
*/
void	render(void *data);

/**
* @brief  Calculate the data for the frame
*
* @param dda    The current state of dda    (t_dda*)
* @param player The current state of player (t_player*)
* @param col    Current pixel of the frame  (int)
*/
void	dda_info(t_dda *dda, t_player *player, int col);

/**
* @brief  Set a pixel to the right pixel of the texture
*
* @param mlx_state The current state of mlx (t_mlx_state*)
* @param dda       The current state of dda (t_dda*)
* @param col       The current pixel        (int)
*/
void	textures(t_mlx_state *mlx_state, t_dda *dda, int col);

/**
* @brief  Set the key bindings for the game
*
* @param param The program (t_program*) as a (void*)
*/
void	hooks(void *param);

/**
* @brief  Check if current cord is a wall
*
* @param map The current map (char**)
* @param row The current row (int)
* @param col The current col (int)
*
* @return true | false
*/
bool	hit_wall(char **map, int row, int col);

/**
* @brief  Set the new frame
*
* @param mlx_state The current state of xml    (t_mlx_state*)
* @param dda       The current state of dda    (t_dda*)
* @param player    The current state of player (t_player*)
* @param col       The current col             (int)
*/
void	fill_buffer(t_mlx_state *mlx_state, t_dda *dda, \
					const t_player *player, int col);

#endif
