#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "user_mgr.h"
#include <string.h>
#include "md5.h"
#include <unistd.h>

node2* user_list = NULL;

//创建一个链表
node2* create_u(void)
{
	node2* n = (node2*)malloc(sizeof(node2));
	n->next = NULL;
	//printf("************************************\n");
	return n;
}


//	在链表尾部插入节点
void user_push_back(node2* l, elem_user data)
{
	//创建一个新节点
	node2* n = (node2*)malloc(sizeof(node2));
	
		n->data = data;
		n->next = NULL;
	
	//找到链表的尾节点
	while(l->next != NULL)
	{
		l = l->next;
	}
	
	//在尾部插入新节点
	l->next = n;
}

//在链表中任意位置插入节点
void insert(node2* l,unsigned int pos)
{
	//创建一个新节点
	node2 * n = (node2*)malloc(sizeof(node2));
	

	//找到要插入新节点的位置
	while(pos-- && l->next != NULL)l = l->next;

	//在上面找到的节点之后插入新节点
	n->next = l->next;
	l->next = n;

}

//修改(更新)链表节点数据

int user_update(node2 * l)
{
	char new_name[31], new_ID[20],choose1,lock = 0;
	int number, i;
	node2* ui = NULL;
	ui = l->next;
	good g;

	while(1)
	{
		l = ui;
		//system("clear");
        printf("************************************\n");
        printf("*         管理员操作系统           *\n");
        printf("*----------------------------------*\n");
        printf("*   正在进行[修改用户信息]操作     *\n");
        printf("*----------------------------------*\n");
        printf("*         请按照提示输入           *\n");
        printf("*        退出修改请输入[0]         *\n");
        printf("************************************\n");
        printf("\n请输入要[修改]的用户[工号]:");
        scanf("%d", &number);
        if(number == 0) return;
		//check_goods_name(number);
		
		//遍历good_list
		while(l != NULL)
		{
			if(l->data.job_number == number) 
			{
				lock = 1;
				break;
			}
			l = l->next;
		}

		if(lock == 0)
		{
			printf("\n");
			printf("************************************\n");
			printf("*   工号[%d]用户不存在或已被删除!  *\n",number);
			printf("*----------------------------------*\n");
			printf("*     继续[1]           退出[0]    *\n");
			printf("请输入:");
			scanf("%d",&choose1);
			
			if(choose1 == 1)
			{
				l = ui;
			}

			if(choose1 == 0) 
			{
				return -1;
			}
		}

			//找到了，就修改它，返回1
		while(lock == 1)
		{	
			system("clear");
			printf("************************************\n");
			printf("*      已经找到工号[%d]用户!       *\n",number);
		    printf("*----------------------------------*\n");
			printf("*        请选择要修改的信息:       *\n");
		    printf("*----------------------------------*\n");
			printf("*    修改姓名         请输入1      *\n");
			printf("*    修改身份证号     请输入2      *\n");
			printf("*    修改密码         请输入3      *\n");
		  //printf("*    修改当前余量     请输入3      *\n");
			printf("*    返回上一级       请输入0      *\n");
			printf("************************************\n");
			printf("请输入:");
			scanf("%d",&i);

			switch(i)
			{
				case 1:
				{
				//修改名
				system("clear");
				printf("************************************\n");
				printf("*         正在修改[用户姓名]       *\n");
				printf("*----------------------------------*\n");
				printf("*   原[用户姓名]: %s               *\n",l->data.user_name);
				printf("************************************\n");
				printf("请输入新的[用户姓名]:");
				scanf("%s",new_name);
				if(strcpy(l->data.user_name,new_name))
					{
						printf("修改成功!\n\n");
					}
				}break;
			
				case 2:
                {   
				//修改身份证号
            	system("clear");
                printf("************************************\n");
                printf("*      正在修改[用户身份证号]      *\n");
                printf("*----------------------------------*\n");
				printf("*   原[身份证号]: %d               *\n",l->data.user_ID);
                printf("************************************\n");
                printf("请输入新[身份证号]:");
                scanf("%s",new_ID);
				
				if(strcpy(l->data.user_ID,new_ID))
				{
						printf("修改成功!\n\n");
				}
				}break;
			
				case 3:
				{
					change_pass(l);
					
				}break;

				case 0:
                {   
					return;
                }break;

				default: printf("\n输出错误，请重新输入!\n\n");

			}
		}//结束外层while
			break;
	}
}
		



//删除某个节点

int user_del(node2 * l)
{
	int number;
	//定义一个指针，用于记录，链表接起来之后，再free它
	node2 * p = NULL;
	
		system("clear");
		printf("************************************\n");
        printf("*         管理员操作系统           *\n");
        printf("*----------------------------------*\n");
        printf("*     正在进行[删除用户]操作       *\n");
        printf("*----------------------------------*\n");
        printf("*         请按照提示输入           *\n");
        printf("*        退出修改请输入[0]         *\n");
        printf("************************************\n");
        printf("\n请输入要[删除]的用户工号:");
        scanf("%d", &number);
		if(number == 0) return 0;

	//找到带删除节点的前驱节点
	//如果待删除节点存在，循环结束后，l为待删除节点的前驱节点的指针
	while(l->next != NULL && l->next->data.job_number != number)	
		l = l->next;
	
	
	//目标节点不存在，删除失败
	if(l->next == NULL)
	{
		printf("\n工号[%d]用户不存在或已被删除!\n\n",number);
		return -1;
	}
	
	//将待删除节点的前驱后继连接起来，否则链表会断链
	p = l->next;
	l->next = p->next;
	free(p);

	//删除成功
	printf("删除工号[%d]用户成功!\n\n",number);
	return 1;
}



//打印链表中所有节点的数据
void show_all_user(node2 * l)
{
	l = l->next;
	while( l != NULL)
	{
		printf("    工    号: %d  \n",l->data.job_number);
		printf("    姓    名: %s  \n",l->data.user_name);
		printf("    身份证号: %s  \n",l->data.user_ID);
		printf("    注册时间: ");
		get_date(l->data.reg_time);
		printf("    最近登录: ");
		get_date(l->data.last_login_time);
		l = l->next;
		printf("\n");
	}
	printf("\n");

}

//精准查找
void show_user2(node2 * l)
{
	node2* c = l;
	unsigned int user_number;
	system("clear");
	while(1)
	{
		l = c;
		printf("************************************\n");
	    printf("*     正在进行[精确查找]操作       *\n");
		printf("*----------------------------------*\n");
		printf("*   请输入想要查找的[用户工号]     *\n");
        printf("*        退出查找请输入[0]         *\n");
		printf("************************************\n");
		printf("请输入:");
		scanf("%d",&user_number);
		if(user_number == 0) return;

		l = l->next;
		while( l != NULL)
		{
			if(l->data.job_number == user_number)
			{	
				printf("************************************\n");
				printf("*      已经找到工号[%d]用户信息    *\n",user_number);
				printf("************************************\n\n");
				printf("    工    号: %d  \n",l->data.job_number);
				printf("    姓    名: %s  \n",l->data.user_name);
				printf("    身份证号: %s  \n",l->data.user_ID);
				printf("    注册时间: ");
				get_date(l->data.reg_time);
				printf("    最近登录: ");
				get_date(l->data.last_login_time);
				printf("************************************\n");
				printf("\n");
				break;
			}
			l = l->next;
		}
	
		if(l == NULL)
		{
			printf("\n工号[%d]用户不存在或已被删除!\n\n",user_number);
		}
	}
}

void show2(node2* l)
{
	FILE* fp = NULL;
	
	good g;
	
	fp = fopen("./good_data","rb");

	//	fwrite(&(l->data),sizeof(good),1,fp);
    while(fread(&g,sizeof(good),1,fp))
    {   
        printf("编号: %d  \n",g.gid);
        printf("名称: %s  \n",g.good_name);
        printf("总量: %d  \n",g.total);
        printf("剩余数量: %d  \n",g.rest);
		printf("\n");
    }   
    printf("\n");
	fclose(fp);

}


int check_user_number(const int number)
{
        FILE* fp = NULL;
        int check_success = 1;
		user_info u;

        fp = fopen("./user_data", "rb");

        if(fp == NULL) return 1;

        while(fread(&u, sizeof(user_info), 1, fp))
        {
            if(number == u.job_number)
            {
                // 工号已经存在
                check_success = 0;
                break;
            }
        }

        fclose(fp);
        return check_success;
}


void user_in_file()
{
	FILE* fp = fopen("./user_data","wb");
	user_info u;

	node2* l = user_list->next;
	while(l != NULL)
	{
		fwrite(&(l->data),sizeof(user_info),1,fp);
		l = l->next;
	}
	fclose(fp);
	return;
}

void load_u_data(void)
{
	FILE* fp = NULL;
	user_info u;
	fp = fopen("./user_data","rb");

	if(fp == NULL) return;

	while(fread(&u,sizeof(u),1,fp))
	{
		user_push_back(user_list, u);
	}

	fclose(fp);
}

void user_add()
{
	int check, i, j;
	char user_pass[31], user_pass_check[31];
	user_info u;

		printf("************************************\n");
		printf("*         管理员操作系统           *\n");
		printf("*----------------------------------*\n");
		printf("*     正在进行[添加用户]操作       *\n");
		printf("*----------------------------------*\n");
		printf("*     请按照提示输入物资信息       *\n");
		printf("*       返回上一级请输入[0]        *\n");
		printf("************************************\n");

		while(1)
		{
			printf("用户工号:");
			scanf("%d",&check);
			if(check == 0) return;

			if(check_user_number(check) == 1)
			{
				u.job_number = check;
				break;
			}
			
			printf("\n此用户工号已经存在,请重新输入!\n");
		}

		printf("用户姓名:");	
		scanf("%s",u.user_name);
     
		while(1)
		{   
			printf("身份证号:");
			scanf("%s", u.user_ID);
 
			if(strlen(u.user_ID) >=6)
			{   
				for(i = strlen(u.user_ID);i > 0; i--)
				{   
					for(j = 6;j > 1;j--)
					{   
						user_pass[j-1] = u.user_ID[i];
					} 
				}   
				break;
			}   
			printf("\n-----身份证格式有误,请重新输入!-----\n");
		}
   
		md5_encode(user_pass, strlen(user_pass), u.user_pass);
        u.reg_time = time(NULL);
        u.last_login_time = 0;

		user_push_back(user_list, u);
}

void change_pass(node2* l)
{
	char new_pass[31], new_pass_check[31];
		
		printf("************************************\n");
		printf("*   正在进行[修改用户密码]操作     *\n");
		printf("*----------------------------------*\n");
		printf("*     请按照提示输入物资信息       *\n");
		printf("*       返回上一级请输入[0]        *\n");
		printf("************************************\n");

		while(1)
		{
			strcpy(new_pass, getpass("用户新密码:"));
			strcpy(new_pass_check, getpass("再次输入密码:"));

			if(strcmp(new_pass,new_pass_check) != 0) 
			{
				printf("\n两次输入的密码不一致,请重新输入\n");
				
			}
			if(strcmp(new_pass,"123456") == 0)
			{
				printf("\n密码不安全,请重新设置!\n");

			}
			else 
			{
				printf("密码设置成功!\n");
				break;
			}
		}
		
		md5_encode(new_pass, strlen(new_pass),l->data.user_pass);		
}


