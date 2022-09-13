#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "user_mgr.h"
#include <string.h>

node3* lend_list = NULL;

//创建一个链表
node3* create_l(void)
{
	node3* n = (node3*)malloc(sizeof(node3));
	n->next = NULL;
	n->data.number = 0;
	//printf("************************************\n");
	return n;
}


//	在链表尾部插入节点
void push_l_back(node3* l, elem_lend data)
{
	l->data.number++;
	//创建一个新节点
	node3* n = (node3*)malloc(sizeof(node3));
	
		n->data = data;
		n->data.number = l->data.number;
		n->next = NULL;
	
	//找到链表的尾节点
	while(l->next != NULL)
	{
		l = l->next;
	}
	
	//在尾部插入新节点
	l->next = n;
}

/*		//暂定是否需要
//删除某个节点
int RemoveNode(node3 * l)
{
	int number;
	//定义一个指针，用于记录，链表接起来之后，再free它
	node3 * p = NULL;
	
		system("clear");
		printf("************************************\n");
        printf("*         管理员操作系统           *\n");
        printf("*----------------------------------*\n");
        printf("*     正在进行[删除物资]操作       *\n");
        printf("*----------------------------------*\n");
        printf("*         请按照提示输入           *\n");
        printf("*        退出修改请输入[0]         *\n");
        printf("************************************\n");
        printf("\n请输入要[删除]的物资编号:");
        scanf("%d", &number);
		if(number == 0) return 0;

	//找到带删除节点的前驱节点
	//如果待删除节点存在，循环结束后，l为待删除节点的前驱节点的指针
	while(l->next != NULL && l->next->data.gid != number)	
		l = l->next;
	
	
	//目标节点不存在，删除失败
	if(l->next == NULL)
	{
		printf("\n编号[%d]物资不存在或已被删除!\n\n",number);
		return -1;
	}
	
	//将待删除节点的前驱后继连接起来，否则链表会断链
	p = l->next;
	l->next = p->next;
	free(p);

	//删除成功
	printf("删除编号[%d]物资成功!\n\n",number);
	return 1;
}	
*/

//打印链表中所有节点的数据
void show_l(node3 * l,int i)
{
	l = l->next;

	if(l == NULL )
	{
		printf("-----暂无记录-----\n");
	}
	while( l != NULL)
	{
		if(l->data.borer_job_number);
		{
			printf("%d.\n",l->data.number);
			printf("借用人工号: %d  \n",l->data.borer_job_number);
			printf("借出物资编号: %d  \n",l->data.good_gid);
			printf("借出数量: %d  \n",l->data.lend_cnt);
			printf("借出时间: ");
			get_date(l->data.lend_time);
			printf("是否归还: %s  \n",l->data.state);
			printf("归还时间: ");
			get_date(l->data.return_time);
			printf("备    注: %s\n",l->data.note);
			printf("\n");
		}
			l = l->next;
		//	printf("\n");
	}
	printf("\n");

}

//打印借出记录
void show_l3(node3* c, int job_num)
{
	node3* l = c->next;

	system("clear");

	//l = lend_list->next;

	if(l == NULL)
	{
		printf("\n--------暂无借出记录!-------\n\n");
		sleep(2);
		return;
	}

	printf("************************************\n");
	printf("*       已经找到借出记录如下       *\n");
	printf("************************************\n\n");

	while( l != NULL)
	{	
	//	printf("123\n");
		if( l->data.borer_job_number ==  job_num)
		{	
			printf("%d.\n",l->data.number);
			printf("借用人工号: %d  \n",l->data.borer_job_number);
			printf("借出物资编号: [%d]  \n",l->data.good_gid);
			printf("借出数量: %d  \n",l->data.lend_cnt);
			printf("借出时间: ");
			get_date(l->data.lend_time);
			printf("是否归还: %s  \n",l->data.state);
			printf("归还时间: ");
			get_date(l->data.return_time);
			printf("备    注: %s\n",l->data.note);
			printf("************************************\n\n");
			printf("\n");
			break;
		}
		l = l->next;
	}
//	printf("\n\n任意输入返回上一级……\n");
//	getchar();
}


void show_l4(node3 * l,int i)
{
	l = l->next;

	if(l == NULL )
	{
		printf("???\n");
	}
	while( l != NULL)
	{
		if(l->data.borer_job_number);
		{
			printf("%d.\n",l->data.number);
			printf("借用人工号: %d  \n",l->data.borer_job_number);
			printf("借出物资编号: %d  \n",l->data.good_gid);
			printf("借出数量: %d  \n",l->data.lend_cnt);
			printf("借出时间: ");
			get_date(l->data.lend_time);
			printf("是否归还: %s  \n",l->data.state);
			printf("归还时间: ");
			get_date(l->data.return_time);
			printf("备    注: %s\n",l->data.note);
			printf("\n");
		}
			l = l->next;
		//	printf("\n");
	}
	printf("\n");

}


//打印物资信息
void show_good(node* l, int good_ID)
{
	node* c = l;
		l = l->next;

		while( l != NULL)
		{
			if(l->data.gid == good_ID)
			{	
				printf("\n");
				printf("物资编号: %d  \n",l->data.gid);
				printf("物资名称: %s  \n",l->data.good_name);
				printf("总量: %d  \n",l->data.total);
				printf("余量: %d  \n",l->data.rest);
				printf("\n");
				break;
			}
			l = l->next;
		}

		if(l == NULL) printf("编号[%d]物资不存在或已经被删除!\n");
		sleep(2);
}


void in_l_file()
{
	FILE* fp = fopen("./lend_data","wb");
	lend d;

	node3* l = lend_list->next;
	while(l != NULL)
	{
		fwrite(&(l->data),sizeof(lend),1,fp);
		l = l->next;
	}
	fclose(fp);
	return;
}

void load_l_data(void)
{
	FILE* fp = NULL;  
	elem_lend d;
	fp = fopen("./lend_data","rb");

	if(fp == NULL) 	return;


	while(fread(&d,sizeof(d),1,fp))
	{
		push_l_back(lend_list, d);
		
		printf("%d\n",d.borer_job_number);
			printf("%d\n",d.good_gid);
			printf("%d\n",d.lend_cnt);
			printf("%d\n",d.number);
			printf("%d\n",d.lend_cnt);
			printf("%ld\n",d.lend_time);
			printf("%s\n",d.state);
			printf("%ld\n",d.return_time);

	}
	fclose(fp);
}

/*
void good_lend()
{
	int check;
	good g;
	while(1)
	{
		printf("************************************\n");
		printf("*         管理员操作系统           *\n");
		printf("*----------------------------------*\n");
		printf("*     正在进行[增加物资]操作       *\n");
		printf("*----------------------------------*\n");
		printf("*     请按照提示输入物资信息       *\n");
		printf("************************************\n");

		printf("物资编号:");
		scanf("%d",&check);

		p
		if(check_goods_gid(check) == 1)
		{
		
		g.gid = check;
			break;
		}
		else printf("\n此编号物资已经存在,请重新输入!\n");
	}
   
		printf("物资名称:");
		scanf("%s",g.good_name);
     
		printf("物资总数:");
		scanf("%d",&g.total);
		g.rest = g.total;
		push_back(good_list, g);
}
*/

void lend_add(node3* l, elem_user* data )
{
	lend d;
	int check_gid = 0,check = 1 , i;
	while(1)
	{
		system("clear");
		printf("************************************\n");
		printf("*           员工操作系统           *\n");
	    printf("*----------------------------------*\n");
		printf("*            工号[%d]            *\n",data->job_number);
		printf("*----------------------------------*\n");
		printf("*     正在进行[借出物资]操作       *\n");
		printf("*      返回上级, 请输入[0]         *\n");
		printf("************************************\n");

		d.borer_job_number = data->job_number;
		d.number = 0;

		while(check != 0)
		{

			while(1)

			{
				printf("想要借出的[物资编号]:");
				scanf("%d", &check_gid);
				if(check_gid != 0 && check_g_gid(good_list, check_gid) != 0)
				{
					//显示此编号物资
					show_good(good_list, check_gid);
					d.good_gid = check_gid;
					break;
				}else 
				  if(check_gid == 0) 
				{
					return;
				}

				printf("\n编号[%d]物资不存在或已被删除!\n",check_gid);
				printf("\n请重新输入\n\n");
			}
		


			while(1)
			{
				printf("想要借出的[物资数量]:");
				scanf("%d", &check);

				if(check == 0) return;

				i = lendgood(good_list, check_gid, check);

				if(i == 1)
				{
					in_file();
					break;
				}
				else if(i == 0)
				{
					printf("\n\n物资库存不足，请重新选择借出数量!\n\n");
				}
			}

			d.lend_cnt = check;
			d.lend_time = time(NULL);
			strcpy(d.state, "未归还");
			d.return_time = 0;
	
			printf("备注: (回车结束输入)\n");
			scanf("%s", d.note);

			push_l_back(lend_list,d);

			in_l_file();

		FILE* fp = NULL;
		lend d;

		/*
		fp = fopen("./lend_data","rb");

		if(fp == NULL) return;

		while(fread(&d,sizeof(d),1,fp))
		{
			printf("**\n");
			printf("%d\n",d.borer_job_number);
			printf("%d\n",d.good_gid);
			printf("%d\n",d.lend_cnt);
			printf("%d\n",d.number);
			printf("%d\n",d.lend_cnt);
			printf("%ld\n",d.lend_time);
			printf("%s\n",d.state);
			printf("%ld\n",d.return_time);
			printf("%s\n",d.note);
			printf("**\n");
		}
		fclose(fp);
		*/
			
			printf("\n\n已成功借出!\n");
			printf("正在返回上一级……\n");

			sleep(2);
			break;
		}
	}
}

void lend_return(node3* l, elem_user* data )
{
	lend d;
	node3* p;
	int check_gid = 0,check = 1 , i,cho;
	while(1)
	{
		system("clear");
		printf("************************************\n");
		printf("*           员工操作系统           *\n");
	    printf("*----------------------------------*\n");
		printf("*            工号[%d]            *\n",data->job_number);
		printf("*----------------------------------*\n");
		printf("*     正在进行[归还物资]操作       *\n");
		printf("*      返回上级, 请输入[0]         *\n");
		printf("************************************\n");

		p = l->next;
		l = l->next;

		while(check != 0)
		{
			while(1)
			{
				l = p;
				printf("想要归还的[物资编号]:");
				scanf("%d", &check_gid);
				if(check_gid == 0) return;
			

				while(l != NULL)
				{
					if(l->data.borer_job_number == data->job_number && check_gid == l->data.good_gid)
					{
						//显示此编号物资
						show_l3(lend_list, data->job_number);
						printf("是否[归还]以上记录的物资?\n");
						printf("确认(1) 取消(0)\n");
						scanf("%d",&cho);
						if(cho == 0) return;
						else
						  if(cho == 1)
						  {
								if(returngood(good_list, l->data.good_gid, l->data.lend_cnt) == 1)
								{
									strcpy(l->data.state,"已归还");
									l->data.return_time = time(NULL);
									in_l_file();
									printf("\n归还成功!\n");
									printf("正在返回上一级……\n");
									sleep(2);
								}
								else 
								{
									printf("\n归还失败!\n");
									printf("正在返回上一级……\n");
									sleep(2);
								}

						  }
						return;
					}
					l = l->next;
				}

				printf("\n暂无编号[%d]借出记录!\n",check_gid);
				printf("\n请重新输入\n\n");
			}
		}
	}

}



/*
int main()
{
	lend_list = create();
	load_l_data();
	show_l(lend_list);

	lend_add(lend_list)
	
	show_l3(lend_list);
}
*/


