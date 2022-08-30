#ifndef _USER_MGR_H_
#define _USER_MGR_H_

#include <time.h>

typedef struct
{
	int job_number;
	char user_name[31];
	char user_ID[20];
	char user_pass[33];
	time_t reg_time;			//注册时间	
	time_t last_login_time;		//最近一次登陆时间
}user_info;

typedef struct
{
	char user_name[31];
	char user_pass[33];
	time_t reg_time;			//注册时间	
	time_t last_login_time;		//最近一次登陆时间

}admin_t;

typedef struct good_d
{
	int gid;
	char good_name[31];
	int total;
	int rest;
}good;

typedef good elem_type;

typedef struct node_t
{
	elem_type data;
	struct node_t* next;
}node;

node* good_list = NULL;

#endif
