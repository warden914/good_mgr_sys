#ifndef _USER_MGR_H_
#define _USER_MGR_H_

#include <time.h>

typedef struct
{
	int job_number;
	char user_name[31];
	char sex[8];
	char user_ID[20];
	char user_pass[33];
	long phone_num;
	time_t reg_time;			//注册时间	
	time_t last_login_time;		//最近一次登陆时间
}user_info;

typedef user_info elem_user;

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

typedef struct lend_d
{
	int	number;
	int borer_job_number;
	int good_gid;
	int lend_cnt;
	time_t lend_time;
	char state[11];
	time_t return_time;
	char note[100];
}lend;

typedef	lend elem_lend;
typedef good elem_type;

typedef struct node_t
{
	elem_type data;
	struct node_t* next;
}node;

typedef struct node_n
{
	elem_user data;
    struct node_n* next;
}node2;

typedef struct node_l
{
	elem_lend data;
	struct node_l* next;
}node3;

extern node* good_list;
extern node2* user_list;
extern node3* lend_list;

void in_file();
void change_pass(node2* l);
//void user_update(node2* l);

#endif
