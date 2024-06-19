#include "../include/engine.h"

void	print_player(t_player *player) {
	if (player == NULL) {
		printf("Geen player!");
		return ;
	}

	printf("row      : %.6f, col      : %.6f\n", player->pos.row, player->pos.col);
	printf("row delta: %.6f, col delta: %.6f\n", player->d_pos.row, player->d_pos.col);
	printf("angle    : %.6f\n", player->angle);
	printf("facing   : %c\n", player->faceing);
}

void	print_dda(t_dda *dda) {
	if (dda == NULL) {
		printf("Geen dda\n");
	}

	printf("plane row     : %.6f, plane col     : %.6f\n", dda->plane.row, dda->plane.col);
	printf("plane row     : %.6f, plane col     : %.6f\n", dda->plane.row, dda->plane.col);
	printf("cam col       : %.6f\n", dda->camera_col);
	printf("ray dir row   : %.6f, ray dir col   : %.6f\n", dda->ray_dir.row, dda->ray_dir.col);
	printf("delta dist row: %.6f, delta dist col: %.6f\n", dda->delta_dist.row, dda->delta_dist.col);
	printf("stepper row   : %.6f, stepper col   : %.6f\n", dda->stepper.row, dda->stepper.col);
	printf("side dist row : %.6f, side dist col : %.6f\n", dda->side_dist.row, dda->side_dist.col);
	printf("pos row       : %.6f, pos col       : %.6f\n", dda->pos.row, dda->pos.col);
	printf("prep wall     : %.6f\n", dda->prep_wall);
	printf("side          : %i\n", dda->side);
	printf("draw heigth   : %i\n", dda->line.heigth);
	printf("draw start    : %i\n", dda->line.start);
	printf("draw end      : %i\n", dda->line.end);
}
