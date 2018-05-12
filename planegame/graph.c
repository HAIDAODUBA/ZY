#include "plane_game.h"

int show_plane(Plane_body *head)
{
	Plane_body *p = head;
	pthread_mutex_lock(&m);
	while(p->next != NULL)
	{
		mvaddstr(p->y, p->x, "0");
		p = p->next;
	}
	pthread_mutex_unlock(&m);
	refresh();
}

int show_obstacle()
{
	struct list_head *p;
	Obstacle *q;
	list_for_each(p, &obs->list)
	{
		q = list_entry(p, Obstacle, list);
		mvaddstr(q->y, q->x, "1"); refresh();
	}
}

int show_bullet()
{
	Bullet *p;
	list_for_each_entry(p, &bul->list, list)
	{
		mvaddstr(p->y, p->x, "2"); refresh();
	}
}

void graph_init(Plane_body *head)
{
	initscr();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	show_plane(head);

}

void *game_graph_refesh(void *arg)
{
	while(1)
	{
		if(flag == 1) break;
		Plane_body *head = (Plane_body *)arg;
		clear();
		show_plane(head);
		show_obstacle();
		show_bullet();
		refresh();
		usleep(10000);
	}
	
}

