#include "plane_game.h"

int mov_x=0,mov_y=0;

int init_plane(Plane_body *head)
{
	if(head == NULL)
		return -1;

	head->x = 10;
	head->y = 15;
	head->plane_head = 1;

	Plane_body *p = head;
	int i,j,k=2,l=1;
	for(i=head->y+1; i < head->y+3; i++)
	{
		for (j=head->x-l; j < head->x+k; j++)
		{
			Plane_body *body = malloc(sizeof(Plane_body));
			body->x = j;
			body->y = i;
			body->plane_head = 0;

			p->next = body;
			body->next = NULL;
			p = body;
		}
			l++;
			if(k<5) k+=2;
	}
		

		return 0;
 }

Obstacle *init_obstacle()
{
	Obstacle *head = malloc(sizeof(Obstacle));
	INIT_LIST_HEAD(&head->list);

	return head;
}

void *obstacle_create(void *arg)
{
	while(1)
	{
		srand(time(NULL));
		int x = rand()%20+3;
		int y = 1;
		Obstacle *node = malloc(sizeof(Obstacle));
		node->x = x;
		node->y = y;
		node->crash = 0;
		list_add_tail(&node->list, &obs->list);

		usleep(1000000);
	}
	
}

void *obstacle_move(void *arg)
{
	Obstacle *p;
	
	while(1)
	{	
		list_for_each_entry(p, &obs->list, list)
		p->y++;	

		hit_plane((Plane_body *)arg);	
		sleep(1);
	}
	
}

/*
void obs_move(int sig)
{
	Obstacle *p;

	if(sig == SIGALRM)
	{
		list_for_each_entry(p, &obs->list, list)
		{
			p->y++;
		}
		show_obstacle(obs);

		mvaddstr(10,10,"0");refresh();
	}
	alarm(1);
}*/


 int plane_direction(Plane_body *head)
 {
 	int key;

 	while(1)
 	{
	 		switch(key = getch())
	 	{
	 		case KEY_UP: mov_x = 0;
	 					 mov_y = -1;
	 					 break;
	 		case KEY_DOWN: mov_x = 0;
	 					   mov_y = +1;
	 					   break;
	 		case KEY_LEFT: mov_x = -1;
	 					   mov_y = 0;
	 					   break;
	 		case KEY_RIGHT: mov_x = 1;
	 						mov_y = 0;
	 						break;
	 		case 'x': bullet_shut(head);
	 		//default: exit(0);
	 	}
	 	
	 	plane_move(head);
	 	mov_x = 0;
	 	mov_y = 0;
 	}

 	return 0;
 	
 }

int plane_move(Plane_body *head)
{
	Plane_body *p = head;

	if(p->x == 3)
		if(mov_x == -1)
			return 0;
	if(p->x == 20)
		if(mov_x == 1)
			return 0;
	if(p->y == 1)
		if(mov_y == -1)
			return 0;
	if(p->y == 20)
		if(mov_y == 1)
			return 0;

	pthread_mutex_lock(&m);
	while(p->next != NULL)
	{
		p->x += mov_x;
		p->y += mov_y;
		p = p->next;
	}
	pthread_mutex_unlock(&m);
	hit_plane(head);
	return 0;
}

Bullet *init_bullet(Plane_body *head)
{
	Bullet *bul = malloc(sizeof(Bullet));
	INIT_LIST_HEAD(&bul->list); 

	return bul;
}


int bullet_shut(Plane_body *head)
{
		Bullet *node = malloc(sizeof(Bullet));
		node->x = head->x;
		node->y = head->y-1;
		list_add_tail(&node->list, &bul->list);

		return 0;
}

void *bullet_move(void *arg)
{
	Bullet *p = bul,*q;
	while(1)
	{
		list_for_each_entry_safe(p, q, &bul->list, list)	
		{
			p->y--;
			if(p->y == 0) list_del(&p->list);
	    }

		usleep(10000);
		hit_obs();	
	}
}

int hit_obs()
{
	Obstacle *p = obs,*i;
	Bullet *q = bul,*j;
	list_for_each_entry_safe(p, i, &obs->list, list)
	{
		list_for_each_entry_safe(q, j, &bul->list, list)
		{
			if(p->x == q->x && p->y == q->y)
			{			
				list_del(&p->list);			
				list_del(&q->list);
			}	
		}
	}
	return 0;
}

int hit_plane(Plane_body *head)
{
	Obstacle *p = obs,*i;
	Plane_body *q = head;
	flag = 0;
	list_for_each_entry_safe(p, i, &obs->list, list)
	{
		while(q->next != NULL)
		{
			if(p->x == q->x && p->y == q->y)
			{	int j;
				//flag = 1;
				j = pthread_cancel(tid2);
				clear();
				mvaddstr(10,10, "game over!");
				refresh();
				sleep(1);
				endwin();
				exit(0);
			}
			q = q->next;
		}
	}
	return 0;
}


