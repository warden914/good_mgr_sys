#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "user_mgr.h"
#include <string.h>

node* good_list = NULL;

//创建一个链表
node* create(void)
{
	node* n = (node*)malloc(sizeof(node));
	n->next = NULL;
	//printf("************************************\n");
	return n;
}


//	在链表尾部插入节点
void push_back(node* l, elem_type data)
{
	//创建一个新节点
	node* n = (node*)malloc(sizeof(node));
	
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
void insert(node* l,unsigned int pos)
{
	//创建一个新节点
	node * n = (node*)malloc(sizeof(node));
	

	//找到要插入新节点的位置
	while(pos-- && l->next != NULL)l = l->next;

	//在上面找到的节点之后插入新节点
	n->next = l->next;
	l->next = n;

}

//修改(更新)链表节点数据

int update(node * l)
{
	char new_name[31];
	int number, i, new_total, new_rest, choose1,lock;
	node* gi = (node*)malloc(sizeof(node));
	FILE* fp = fopen("./good_data","rb");
	good g;

		//system("clear");
        printf("************************************\n");
        printf("*         管理员操作系统           *\n");
        printf("*----------------------------------*\n");
        printf("*     正在进行[修改物资]操作       *\n");
        printf("*----------------------------------*\n");
        printf("*         请按照提示输入           *\n");
        printf("*        退出修改请输入[0]         *\n");
        printf("************************************\n");
        printf("\n请输入要修改的物资编号:");
        scanf("%d", &number);
        if(number == 0) return;
		//check_goods_name(number);
		
		l = l->next;
		//遍历good_list
		while(l != NULL)
		{
			if(l->data.gid == number) 
			{
				lock = 1;
				break;
			}
			l = l->next;
			lock = 0;
		}

		if(lock == 0)
		{
			printf("\n");
			printf("************************************\n");
			printf("*   编号[%d]物资不存在或已被删除!  *\n",number);
			printf("*----------------------------------*\n");
			printf("*     继续[1]           退出[0]    *\n");
			printf("请输入:");
			scanf("%d",&choose1);
			
			if(choose1 == 1)
			{
				return 1;
			}
			if(choose1 == 0) 
			{
				return -1;
			}
		}
			//找到了，就修改它，返回1
		while(1)
		{	
			system("clear");
			printf("************************************\n");
			printf("*       已经找到编号[%d]物资!      *\n",number);
		    printf("*----------------------------------*\n");
			printf("*        请选择要修改的信息:       *\n");
		    printf("*----------------------------------*\n");
			printf("*    修改名称         请输入1      *\n");
			printf("*    修改总量         请输入2      *\n");
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
					printf("*         正在修改[物资名称]       *\n");
					printf("*----------------------------------*\n");
					printf("*   原[物资名称]: %s               *\n",l->data.good_name);
					printf("************************************\n");
					printf("请输入新[物资名称]:");
					scanf("%s",new_name);
					if(strcpy(l->data.good_name,new_name))
					{
						printf("修改成功!\n\n");
					}
				}break;
			
				case 2:
                {   
					//修改总量
            		system("clear");
                    printf("************************************\n");
                    printf("*         正在修改[物资总量]       *\n");
                    printf("*----------------------------------*\n");
                    printf("*注意! [余量] 会随着[总量]而变更   *\n");
                    printf("*----------------------------------*\n");
                    printf("*   原[物资总量]: %d               *\n",l->data.total);
                    printf("************************************\n");
                    printf("请输入新[物资总量]:");
                    scanf("%d",&new_total);
				
					l->data.total = new_total;

					if(new_total < l->data.rest) 
					{
						l->data.rest = new_total;
					}
					else 
					{
						l->data.rest = l->data.rest + new_total - l->data.total;				
					}
						printf("修改成功!\n\n");
                }break;
			
				case 0:
                {   
                }break;
			}//结束外层while
			break;
		}
		fclose(fp);
}


//删除某个节点
int RemoveNode(node * l)
{
	//定义一个指针，用于记录，链表接起来之后，再free它
	node * p = NULL;
	
	//找到带删除节点的前驱节点
	//如果待删除节点存在，循环结束后，l为待删除节点的前驱节点的指针
	while(l->next != NULL)	
		l = l->next;
	
	//目标节点不存在，删除失败
	if(l->next == NULL)return 0;
	
	//将待删除节点的前驱后继连接起来，否则链表会断链
	p = l->next;
	l->next = p->next;
	free(p);

	//删除成功
	return 1;
}	


//打印链表中所有节点的数据
void show(node * l)
{
	l = l->next;
	while( l != NULL)
	{
		printf("编号: %d  \n",l->data.gid);
		printf("名称: %s  \n",l->data.good_name);
		printf("总量: %d  \n",l->data.total);
		printf("剩余数量: %d  \n",l->data.rest);
		l = l->next;
	}
	printf("\n");

}

void show2(node* l)
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


int check_goods_name(const int good_gid)
{
        FILE* fp = NULL;
        int check_success = 1;
		good g;

        fp = fopen("./good_data", "rb");

        if(fp == NULL) return 1;

        while(fread(&g, sizeof(good), 1, fp))
        {
            if(good_gid == g.gid)
            {
                // 用户名已经存在
                check_success = 0;
                break;
            }
        }

        fclose(fp);
        return check_success;
}


void in_file()
{
	FILE* fp = fopen("./good_data","wb");
	good g;

	node* l = good_list->next;
	while(l != NULL)
	{
		fwrite(&(l->data),sizeof(good),1,fp);
		l = l->next;
	}
	fclose(fp);
	return;
}

void load_data(void)
{
	FILE* fp = NULL;
	good g;
	fp = fopen("./good_data","rb");

	if(fp == NULL) return;

	while(fread(&g,sizeof(g),1,fp))
	{
		push_back(good_list, g);
	}

	fclose(fp);
}

void good_add()
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

		if(check_goods_name(check) == 1)
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

int main()
{
	good_list = create();
	load_data();
	//good_add();
	//in_file();
//	push_back(good_list);
//	push_back(good_list);
	//push_back(n1);
//	push_back(n1);
	update(good_list);
	in_file();
//	show(good_list);
	show2(good_list);
}

