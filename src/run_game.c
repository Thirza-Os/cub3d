/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/18 15:30:19 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/18 15:30:21 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/engine.h"
#include <math.h>

void set_dda(t_game_state *state, int col) {
    t_dda *dda = state->dda;

    dda->camera_col = 2 * (col / (double)SCREENWIDTH) - 1;
    dda->ray_dir.row = state->player->pos.row + dda->plane.row * dda->camera_col;
    dda->ray_dir.col = state->player->pos.col + dda->plane.col * dda->camera_col;

    dda->pos.row = (int)state->player->pos.row;
    dda->pos.col = (int)state->player->pos.col;

    dda->delta_dist.row = (dda->ray_dir.row == 0) ? MAXFLOAT : fabs(1 / dda->ray_dir.row);
    dda->delta_dist.col = (dda->ray_dir.col == 0) ? MAXFLOAT : fabs(1 / dda->ray_dir.col);
}

static void set_steps(t_game_state *state) {
    t_dda *dda = state->dda;

    if (dda->ray_dir.col < 0) {
        dda->stepper.col = -1;
        dda->side_dist.col = (state->player->pos.col - dda->pos.col) * dda->delta_dist.col;
    } else {
        dda->stepper.col = 1;
        dda->side_dist.col = (dda->pos.col + 1.0 - state->player->pos.col) * dda->delta_dist.col;
    }

    if (dda->ray_dir.row < 0) {
        dda->stepper.row = -1;
        dda->side_dist.row = (state->player->pos.row - dda->pos.row) * dda->delta_dist.row;
    } else {
        dda->stepper.row = 1;
        dda->side_dist.row = (dda->pos.row + 1.0 - state->player->pos.row) * dda->delta_dist.row;
    }
}

static void check_collision(t_game_state *state) {
    t_dda *dda = state->dda;

    while (1) {
        if (dda->side_dist.col < dda->side_dist.row) {
            dda->side_dist.col += dda->delta_dist.col;
            dda->pos.col += dda->stepper.col;
            dda->side = 1;
        } else {
            dda->side_dist.row += dda->delta_dist.row;
            dda->pos.row += dda->stepper.row;
            dda->side = 2;
        }

        if ((size_t)dda->pos.row < state->map_size.row && (size_t)dda->pos.col < state->map_size.col) {
            printf("Cur pos: %d, %d\n", (int)dda->pos.row, (int)dda->pos.col);
            if (state->map[(int)dda->pos.row][(int)dda->pos.col] == '1') {
                break;
            }
        } else {
            printf("Dit is niet goed col of row...\n");
            printf("row: %d, col: %d\n", (int)dda->pos.row, (int)dda->pos.col);
            break;
        }
    }
}

void dda(t_game_state *state) {
    size_t col_index;

    col_index = 0;
    while (col_index < SCREENWIDTH) {
        printf("Current iter: %zu\n", col_index);
        set_dda(state, col_index);
        set_steps(state);
        check_collision(state);
        col_index++;
    }
}

void	run_game(t_game_state *state)
{
	dda(state);
}
