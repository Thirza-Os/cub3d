/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map_surrounded.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:41 by tosinga       #+#    #+#                 */
/*   Updated: 2024/08/23 03:01:22 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

bool check_surrounded_walls(t_program *program)
{
    t_player *player = program->player;
    int left = player->max_map.col, right = 0;
    int top = 0, bottom = player->max_map.row - 1;

    // Find actual map boundaries
    for (int row = 0; row < player->max_map.row; row++) {
        for (int col = 0; col < player->max_map.col; col++) {
            if (player->map[row][col] != ' ') {
                left = ft_min(left, col);
                right = ft_max(right, col);
                top = row;
                break;
            }
        }
    }

    // Check if boundaries are walls
    for (int col = left; col <= right; col++) {
        if (player->map[top][col] != '1' || player->map[bottom][col] != '1')
            return false;
    }
    for (int row = top; row <= bottom; row++) {
        if (player->map[row][left] != '1' || player->map[row][right] != '1')
            return false;
    }

    // Check if '0' or player is adjacent to space or out of bounds
    for (int row = top; row <= bottom; row++) {
        for (int col = left; col <= right; col++) {
            if (player->map[row][col] == '0' || ft_strchr(PLAYER_POS, player->map[row][col])) {
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        int nr = row + dr;
                        int nc = col + dc;
                        if (nr < top || nr > bottom || nc < left || nc > right ||
                            player->map[nr][nc] == ' ') {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}
