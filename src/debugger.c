#include "../include/engine.h"

void	print_player(t_player *player) {
	if (player == NULL) {
		printf("Geen player!");
		return ;
	}

	printf("row      : %.6f, col      : %.6f\n", player->pos.y, player->pos.x);
	printf("row delta: %.6f, col delta: %.6f\n", player->d_pos.y, player->d_pos.x);
	printf("angle    : %.6f\n", player->angle);
	printf("facing   : %c\n", player->faceing);
}

void	print_dda(t_dda *dda) {
	if (dda == NULL) {
		printf("Geen dda\n");
	}

	printf("plane row     : %.6f, plane col     : %.6f\n", dda->plane_x, dda->plane_y);
	printf("cam col       : %.6f\n", dda->camera_x);
	printf("ray dir row   : %.6f, ray dir col   : %.6f\n", dda->ray_dir.y, dda->ray_dir.x);
	printf("delta dist row: %.6f, delta dist col: %.6f\n", dda->delta_dist_x, dda->delta_dist_y);
	printf("stepper row   : %.6d, stepper col   : %.6d\n", dda->step_map_x, dda->step_map_y);
	printf("side dist row : %.6f, side dist col : %.6f\n", dda->side_dist_x, dda->side_dist_y);
	printf("pos row       : %.6f, pos col       : %.6f\n", dda->player_pos.y, dda->player_pos.x);
	printf("prep wall     : %.6f\n", dda->prep_wall_dist);
	printf("side row      : %.6f, side col      : %.6f\n", dda->side_dist_x, dda->side_dist_y);
	printf("draw heigth   : %i\n", dda->line.heigth);
	printf("draw start    : %i\n", dda->line.start);
	printf("draw end      : %i\n", dda->line.end);
	printf("\n");
}
