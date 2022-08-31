#ifndef _U_LIST_H_
#define _U_LIST_H_

void change_pass(node2* l);
void user_add();
void load_u_data(void);
void user_in_file();
int check_user_number(const int number);
void show_user2(node2 * l);
void show_all_user(node2 * l);
int user_del(node2 * l);
int user_update(node2 * l);
void user_push_back(node2* l, elem_user data);
node2* create_u(void);


#endif
