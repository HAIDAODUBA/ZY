#include "plane_game.h"

int main(int argc, char const *argv[])
{
	Plane_body *head = malloc(sizeof(Plane_body));
	init_plane(head);
	obs = init_obstacle();
	bul = init_bullet(head);

	graph_init(head);

	pthread_mutex_init(&m, NULL);

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);//设置线程的取消必须在创建之前

	pthread_create(&tid, NULL, obstacle_move, (void *)head);
	pthread_create(&tid1, NULL, obstacle_create, NULL);
	pthread_create(&tid2, NULL, game_graph_refesh, (void*) head);
	pthread_create(&tid3, NULL, bullet_move, NULL);

	

	plane_direction(head);

	getch();
	endwin();
	return 0;
}