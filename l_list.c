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
		n->next = NULL;
		n->data.number = l->data.number;
	
	//找到链表的尾节点
	while(l->next != NULL)
	{
		l = l->next;
	}
	
	//在尾部插入新节点
	l->next = n;
}

//修改(更新)链表节点数据
//int update(node3 * l, elem_lend data)

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
void show_l(node3 * l)
{
	l = l->next;
	while( l != NULL)
	{
		printf("%d.\n",l->data.number);
		printf("借用人工号: %d  \n",l->data.borer_job_number);
		printf("借出物资编号: %d  \n",l->data.good_gid);
		printf("借出数量: %d  \n",l->data.lend_cnt);
		printf("借出时间: %ld  \n",l->data.lend_time);
		printf("是否归还: %s  \n",l->data.state);
		printf("归还时间: %ld  \n",l->data.return_time);
		printf("备    注: %s\n",l->data.note);
		l = l->next;
		printf("\n");
	}
	printf("\n");

}

//精准查找
void show_l3(node3 * l)
{
	node3* c = l;
	unsigned int good_ID;
	system("clear");
	while(1)
	{
		l = c;
		printf("************************************\n");
	    printf("*     正在进行[精确查找]操作       *\n");
		printf("*----------------------------------*\n");
		printf("*   请输入想要查找的[物资编号]     *\n");
        printf("*        退出查找请输入[0]         *\n");
		printf("************************************\n");
		printf("请输入:");
		scanf("%d",&good_ID);
		if(good_ID == 0) return;

		l = l->next;
		while( l != NULL)
		{
			if(l->data.good_gid == good_ID)
			{	
				printf("%d.\n",l->data.number);
				printf("借用人工号: %d  \n",l->data.borer_job_number);
				printf("借出物资编号: %d  \n",l->data.good_gid);
				printf("借出数量: %d  \n",l->data.lend_cnt);
				printf("借出时间: %ld  \n",l->data.lend_time);
				printf("是否归还: %s  \n",l->data.state);
				printf("归还时间: %ld  \n",l->data.return_time);
				printf("备    注: %s\n",l->data.note);
				l = l->next;
				printf("\n");
			}
			l = l->next;
		}
	
		if(l == NULL)
		{
			printf("\n暂无编号[%d]借归记录!\n\n",good_ID);
		}
		else if(l != NULL)
		{
			printf("************************************\n");
			printf("*   已经找到编号[%d]物资记录如上   *\n",good_ID);
			printf("************************************\n\n");
		}
	}
}


void in_l_file()
{
	FILE* fp = fopen("./lend_data","wb");
	good g;

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
	lend d;
	fp = fopen("./lend_data","rb");

	if(fp == NULL) return;

	while(fread(&d,sizeof(d),1,fp))
	{
		push_back(lend_list, d);
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

/*
int main()
{
	lend_list = create();
	load_l_data();
	show(lend_list);
	
	
	show3(lend_list);
}
*/
