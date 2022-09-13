#ifndef _l_LIST_H_
#define _l_LIST_H_

node3* create_l(void);							//创建头节点
void push_l_back(node3* l, elem_lend data);	//添加尾节点


void show_l();						//打印
void show_l3(node3* l,int data);		//单查

void in_l_file();								//写入data文件
void load_l_data(void);						//文件内容转入链表
void lend_add();							//增



#endif
