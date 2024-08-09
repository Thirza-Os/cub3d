/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 01:13:58 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/09 02:40:18 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include "../include/dda.h"

int32_t	pixel_select(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

