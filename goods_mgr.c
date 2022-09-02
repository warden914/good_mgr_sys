#include <stdio.h>
#include <unistd.h>
#include "md5.h"
#include "user_mgr.h"
#include <string.h>
#include <stdlib.h>
#include "g_list.h"
#include "u_list.h"

int is_ad_first_run(void);
//int is_user_first_run(node *l, int number);
void admin_login();
void user_login();
int ad_login_check(const char *user_name, const char *user_pass);
void admin_sys();
//int is_user_first_run(void);
//int is_user_exist(node2 *l, int number);
user_info* find_user(node2 *l, const int number);
void user_login_update(node2* l, user_info* data);
void user_sys();


admin_t ad;

int main()
{
	int i, a;
	char c;
	system("clear");

	user_list = create_u();
	load_u_data();
	
	//lend_list = create_l();
	load_l_data();

	good_list = create();
	load_data();

	while (1)
	{
		system("clear");
		fflush(stdin);
		printf("************************************\n");
		printf("*      欢迎使用库存管理系统        *\n");
		printf("*----------------------------------*\n");
		printf("*      管理员登陆   请输入1        *\n");
		printf("*      普通用户登陆 请输入2        *\n");
		printf("*      退出         请输入0        *\n");
		printf("************************************\n");
		printf("\n   请输入:");
		a = scanf("%d", &i);

		while (a == 0)
		{
			fprintf(stderr, "\n   输入错误，请重新输入\n");
			printf("   请输入:");
			while ((c = getchar()) != EOF && c != '\n')
				;
			a = scanf("%d", &i);
		}

		switch (i)
		{
		case 1: //管理员登录
		{
			admin_login();
		}
		break;

		case 2: //用户登录
		{
			user_login();
		}
		break;

		case 3: //待开发
		{
		}
		break;

		case 0: //退出
		{
			return 0;
		}
		}
	}
}

void admin_login()
{
	system("clear");
	char user_name[31], user_pass[31], user_pass_check[31];
	printf("************************************\n");
	printf("*      欢迎使用库存管理系统        *\n");
	printf("*----------------------------------*\n");
	printf("*     正在登录管理员操作系统       *\n");
	printf("*                                  *\n");
	printf("*     请根据提示输入对应信息       *\n");
	printf("*                                  *\n");
	printf("************************************\n");
	printf("用户名:");
	scanf("%s", user_name);
	//输入密码没有回显
	strcpy(user_pass, getpass("密码: "));

	/*
	if(strcmp(user_name,"admin") != 0 || strcmp(user_pass,"123456"))
	{
		printf("用户名或密码错误，登陆失败!\n");
		printf("\n正在返回上一级……\n");
		sleep(2);
		return;
	}
	*/

	if (is_ad_first_run())
	{
		//首次登陆成功
		if (strcmp(user_name, "admin") != 0 || strcmp(user_pass, "123456"))
		{
			printf("用户名或密码错误，登陆失败!\n");
			printf("\n正在返回上一级……\n");
			sleep(2);
			return;
		}

		printf("\n为了系统安全，请重新设置管理员用户名和密码");
		printf("\n管理员用户名:");
		scanf("%s", user_name);

		while (1)
		{
			strcpy(user_pass, getpass("管理员密码:"));
			strcpy(user_pass_check, getpass("再次输入密码:"));

			if (strcmp(user_pass, user_pass_check) != 0)
			{
				printf("\n两次输入的密码不一致,请重新输入\n");
			}
			if (strcmp(user_pass, "123456") == 0)
			{
				printf("\n密码不安全,请重新设置!\n");
			}
			else
			{
				printf("密码设置成功!\n");
				break;
			}
		}

		strcpy(ad.user_name, user_name);
		md5_encode(user_pass, strlen(user_pass), ad.user_pass);
		// admin.user_role = 0;
		ad.reg_time = ad.last_login_time = time(NULL);

		FILE *fp = fopen("./ad_data", "wb");

		if (fp == NULL)
		{
			perror("open ad_data fail");
		}

		fwrite(&ad, sizeof(ad), 1, fp);

		fclose(fp);

		printf("\n设置管理员用户名和密码成功!\n");
		printf("正在返回上一级，请重新登陆\n");
		sleep(2);
		return;
	}
	else
	{
		//非首次登录
		if (!ad_login_check(user_name, user_pass))
		{
			printf("用户名或密码错误，登录失败!\n");
			printf("\n正在返回上一级……\n");
			sleep(2);
			return;
		}
		ad.last_login_time = time(NULL);
		// update_user_info();
	}
	admin_sys();
}

int is_ad_first_run(void)
{
	FILE *fp = fopen("./ad_data", "rb");

	if (fp == NULL)
		return 1;

	fclose(fp);

	return 0;
}

int is_user_first_run(node2 *l, int number)
{
	l = l->next;
	while (l != NULL)
	{
		if (l->data.job_number == number)
		{
			if (l->data.last_login_time - 1 < 0)
			{
				return 1;
			}
			else
				return 0;
		}
		l = l->next;
	}
	return 0;
}

int ad_login_check(const char *user_name, const char *user_pass)
{
	FILE *fp = NULL;
	admin_t ad1;
	char user_pass_md5[33];
	int check_success = 0;

	fp = fopen("./ad_data", "rb");

	if (fp == NULL)
		return 0;

	md5_encode(user_pass, strlen(user_pass), user_pass_md5);

	if (fread(&ad1, sizeof(ad1), 1, fp) == 1)
	{
		if (strcmp(user_name, ad1.user_name) == 0 && strcmp(user_pass_md5, ad1.user_pass) == 0)
		{
			// 登录验证成功
			ad = ad1;
			check_success = 1;
			// break;
		}
	}
	fclose(fp);
	return check_success;
}

int user_login_check(node2* l, int number, char* pass)
{
	char md5_pass[33];
	int check = 0;
	user_info* ui;
	
	ui = find_user(l, number);
	if(ui == NULL)
	  return 0;

	md5_encode(pass, strlen(pass), md5_pass);

	l = l->next;
	while(l != NULL)
	{
		if(strcmp(md5_pass, pass) == 0 && l->data.job_number == number)
		{
			check = 1;
			return check;
		}
		l = l->next;
	}
	return check;
}

void admin_sys()
{
	int i, a, c;
	while (1)
	{
		system("clear");
		printf("************************************\n");
		printf("*         管理员操作系统           *\n");
		printf("*----------------------------------*\n");
		printf("*     修改用户名和密码   请输入1   *\n");
		printf("*                                  *\n");
		printf("*     添加普通用户       请输入2   *\n");
		printf("*     删除普通用户       请输入3   *\n");
		printf("*     修改普通用名       请输入4   *\n");
		printf("*     查询用户信息       请输入5   *\n");
		printf("*                                  *\n");
		printf("*     增加物资信息       请输入6   *\n");
		printf("*     删除物资信息       请输入7   *\n");
		printf("*     修改物资信息       请输入8   *\n");
		printf("*     查询物资信息       请输入9   *\n");
		printf("*     退出管理员登录     请输入0   *\n");
		printf("************************************\n");
		printf("\n   请输入:");
		a = scanf("%d", &i);
		while (a == 0)
		{
			fprintf(stderr, "\n   输入错误，请重新输入\n");
			printf("   请输入:");
			while ((c = getchar()) != EOF && c != '\n')
				;
			a = scanf("%d", &i);
		}

		switch (i)
		{
		case 1:
		{
			//修改用户名和密码
		}
		break;

		case 2:
		{
			//添加用户
			user_add(user_list);
			user_in_file();
		}
		break;

		case 3:
		{
			//删除用户
			user_del(user_list);
			user_in_file();
		}
		break;

		case 4:
		{
			//修改普通用户
			user_update(user_list);
			user_in_file();
		}
		break;

		case 5:
		{
			//查询用户信息
			int op;
			while(1)
			{
				printf("\n\n想以哪种方式查询?\n");
				printf("1. 查询全部  2.工号查询\n");
				printf("0. 返回上一级\n");
				printf("请输入:");
				scanf("%d", &op);
				if (op == 0)
					break;

				switch (op)
				{
				case 1:
				{
					show_all_user(user_list);
				}
				break;

				case 2:
				{
					show_user2(user_list);
				}
				break;
				}
			}
		}
		break;

		case 6:
		{
			//增加物资信息
			good_add(good_list);
			in_file();
		}
		break;

		case 7:
		{
			//删除物资
			RemoveNode(good_list);
			in_file();
		}
		break;

		case 8:
		{
			//修改物资信息
			update(good_list);
			in_file();
		}
		break;

		case 9:
		{
			//查询物资信息
			int op;
			printf("想以哪种方式查询?\n");
			printf("1. 查询全部  2.编号查询\n");
			printf("0. 返回上一级\n");
			printf("请输入:");
			scanf("%d", &op);
			if (op == 0)
				break;

			switch (op)
			{
			case 1:
			{
				show(good_list);
			}
			break;

			case 2:
			{
				show3(good_list);
			}
			break;
			}
		}
		break;

		case 0:
		{
			return;
		}
		break;
		}
	}
}

user_info* find_user(node2 *l, const int number)
{
	l = l->next;
	while (l != NULL)
	{
		if (l->data.job_number == number)
		{
				return &(l->data);
		}
		else return NULL;
		l = l->next;
	}
	return NULL;
}

void user_login()
{
	system("clear");
	int number, i, j;
	user_info* user = NULL;
	//node2* mid = (node2*)malloc(sizeof(node));
		
	char user_name[31], user_pass[31], user_pass_check[31];
	printf("************************************\n");
	printf("*      欢迎使用库存管理系统        *\n");
	printf("*----------------------------------*\n");
	printf("*      正在登录用户操作系统        *\n");
	printf("*                                  *\n");
	printf("*     请根据提示输入对应信息       *\n");
	printf("*                                  *\n");
	printf("************************************\n");
	printf("工号:");
	scanf("%d", &number);

	user = find_user(user_list, number);
	if(user != NULL)
	{
		printf("%d \n%s\n %s\n %s\n",user->job_number,user->user_name, user->user_ID,user->user_pass);
	}
	else if(user == NULL) 
	{
		printf("\n用户不存在!\n\n");
		printf("\n正在返回主菜单，请重新登录!\n\n");
		sleep(2);
		return;
	}


	//输入密码没有回显
	strcpy(user_pass, getpass("密码:"));
	
	if(is_user_first_run(user_list, number))
	{
		for(i = strlen(user->user_ID);i > 0; i--)
		{   
			for(j = 6;j >= 1;j--)
			{
				user_pass[j-1] = user->user_ID[i];
				//strcpy(user_pass, user->user_ID);
				//user_pass[j-1] = user->user_ID[i-1];
			}   
		}

		md5_encode(user_pass, strlen(user_pass), user_pass_check);

		if(user->job_number != number || strcmp(user_pass_check,user->user_pass))
		{
			printf("用户名或密码错误，登录失败!\n");
			printf("\n正在返回上一级……\n");
			sleep(2);
			return;
		}
		
		printf("\n为了系统安全，请重新设置用户密码\n");
		
		while(1)
		{
			strcpy(user_pass,getpass("用户新密码:"));
			strcpy(user_pass_check,getpass("再次输入密码:"));
			
			if(strcmp(user_pass, user_pass_check) != 0)
			{
				printf("\n两次输入的密码不一致，请重新输入!\n");
			}
			else if(strcmp(user_pass, user_pass_check) == 0 && strcmp(user_pass, "123456") != 0)
			{
				printf("密码设置成功!\n");
				printf("正在返回上一级，请重新登录\n");
				md5_encode(user_pass, strlen(user_pass), user->user_pass);
				sleep(2);
				break;
			}

			if(strcmp(user_pass, "123456") == 0)
			{
				printf("\n密码不安全，请重新设置!\n");
			}
			
		}
		//md5_encode(user_pass, strlen(user_pass), user->user_pass);

		user->last_login_time = time(NULL);
		user_login_update(user_list, user);
		user_in_file();

	}
	else if(!is_user_first_run(user_list, number))
	{
		user->last_login_time = time(NULL);
		user_login_update(user_list, user);
		user_in_file();
		user_sys(user,&user);
	}
}

void user_login_update(node2* l, user_info* data)
{
	l = l->next;
	while(l != NULL)
	{
		if(l->data.job_number == data->job_number)
		{
			l->data = *data;
		}
		l = l->next;
	}
}

void user_sys(node2* l, elem_user data)
{
	int i, a, c;
	while (1)
	{
		system("clear");
		printf("************************************\n");
		printf("*           员工操作系统           *\n");
		printf("*----------------------------------*\n");
		printf("*			 工号[%d]            *\n");
		printf("*----------------------------------*\n");
	  //printf("*     修改用用户信息     请输入1   *\n");
		printf("*     查询当前信息       请输入2   *\n");
		printf("*                                  *\n");
		printf("*     借出物资           请输入3   *\n");
		printf("*     查询[借出]记录     请输入4   *\n");
		printf("*                                  *\n");
		printf("*     归还物资           请输入5   *\n");
		printf("*     查询[归还]记录     请输入6   *\n");
		printf("*                                  *\n");
		printf("*     退出当前用户登录   请输入0   *\n");
		printf("************************************\n");
		printf("\n   请输入:");
		a = scanf("%d", &i);
		while (a == 0)
		{
			fprintf(stderr, "\n   输入错误，请重新输入\n");
			printf("   请输入:");
			while ((c = getchar()) != EOF && c != '\n')
				;
			a = scanf("%d", &i);
		}

		switch(i)
		{
			case 1:
				{	
					//修改当前用户信息
					

				}break;

			case 2:
				{

				}break;

			case 3:
				{

				}break;

			case 4:
				{

				}break;

			case 5:
				{

				}break;

			case 6:
				{

				}break;

			case 0:
				{
					return;
				}break;

		}
	}
}
