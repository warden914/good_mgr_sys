#ifndef _G_LIST_H_
#define _G_LIST_H_

node* create(void);							//创建头节点
void push_back(node* l, elem_type data);	//添加尾节点
int update(node * l);						//改
int RemoveNode(node * l);					//删
void show(node * l);						//打印
void show3(node * l);						//单查
int check_goods_gid(const int good_gid);	//检查编号重复
void in_file();								//写入data文件
void load_data(void);						//文件内容转入链表
void good_add();							//增



#endif
