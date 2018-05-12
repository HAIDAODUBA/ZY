#ifndef __PLGAME__
#define __PLGAME__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

#include <signal.h>
#include <time.h>
#include <curses.h>
#include <pthread.h>
#include "kernel_list.h"

typedef struct plane_body
{
	int x;
	int y;
	int plane_head;
	struct plane_body *next;
}Plane_body;

typedef struct bullet
{
	int x;
	int y;
	struct list_head list;
}Bullet;

typedef struct obstacle
{
	int x;
	int y;
	int crash;
	int have;
	struct list_head list;
}Obstacle;

Obstacle *obs;
Bullet *bul;
pthread_mutex_t m;
pthread_t tid,tid1,tid2,tid3;
int flag;

int init_plane(Plane_body *head);
int plane_move(Plane_body *head);
Obstacle *init_obstacle();
void *obstacle_create(void *arg);
int show_obstacle();
int plane_direction(Plane_body *head);
void graph_init(Plane_body *head);
int show_plane(Plane_body *head);
void *obstacle_move(void *arg);
//void obs_move(int sig);
Bullet *init_bullet(Plane_body *head);
int bullet_shut(Plane_body *head);
void *bullet_move(void *arg);
int show_bullet();
void *game_graph_refesh(void *arg);
int hit_obs();
int hit_plane(Plane_body *head);
#endif
