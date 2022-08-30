#include <stdio.h>
#include <unistd.h>
#include "md5.h"
#include "user_mgr.h"
#include <string.h>
#include <stdlib.h>

int is_ad_first_run(void);
void admin_login();
int ad_login_check(const char* user_name, const char* user_pass);
void update_user_info(void);
void admin_sys();
void user_add(void);
int check_user_number(const int user_number);
void user_del(void);
int is_user_first_run(void);
void change_user_info(void);
int user_search(void);


user_info user;
admin_t ad;

int main()
{
	int i,a;
	char c;
	system("clear");

	while(1)
	{
		//system("clear");
		fflush(stdin);
		printf("************************************\n");
		printf("*      欢迎使用库存管理系统        *\n");
		printf("*----------------------------------*\n");
		printf("*      管理员登陆   请输入1        *\n");
		printf("*      普通用户登陆 请输入2        *\n");
		printf("*      退出         请输入0        *\n");
		printf("************************************\n");
		printf("\n   请输入:");
		a =	scanf("%d",&i);
		
		while(a == 0)
		{
			fprintf(stderr, "\n   输入错误，请重新输入\n");
			printf("   请输入:");
			while((c = getchar()) != EOF && c != '\n');
			a = scanf("%d",&i);
		}

		switch(i)
		{
			case 1:				//管理员登录
			{
				admin_login();
			}break;

			case 2:				//用户登录
			{
				//user_login();
			}break;
		
			case 3:	//待开发
			{

			}break;
			
			case 0:				//退出
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
	scanf("%s",user_name);
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

	if(is_ad_first_run())
	{
		//首次登陆成功
		if(strcmp(user_name,"admin") != 0 || strcmp(user_pass,"123456"))
		{
			printf("用户名或密码错误，登陆失败!\n");
			printf("\n正在返回上一级……\n");
			sleep(2);
			return;
		}

		printf("\n为了系统安全，请重新设置管理员用户名和密码");
		printf("\n管理员用户名:");
		scanf("%s",user_name);
		
		while(1)
		{
			strcpy(user_pass, getpass("管理员密码:"));
			strcpy(user_pass_check, getpass("再次输入密码:"));

			if(strcmp(user_pass,user_pass_check) != 0) 
			{
				printf("\n两次输入的密码不一致,请重新输入\n");
				
			}
			if(strcmp(user_pass,"123456") == 0)
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
		md5_encode(user_pass, strlen(user_pass),ad.user_pass);
		//admin.user_role = 0;
		ad.reg_time = ad.last_login_time = time(NULL);

		FILE* fp = fopen("./ad_data","wb");

		if(fp == NULL)
		{
			perror("open ad_data fail");
		}
		
		fwrite(&ad,sizeof(ad),1,fp);

		fclose(fp);

		printf("\n设置管理员用户名和密码成功!\n");
		printf("正在返回上一级，请重新登陆\n");
		sleep(2);
		return;
	}
	else
	{
		//非首次登录
		if(!ad_login_check(user_name,user_pass))
		{
			printf("用户名或密码错误，登录失败!\n");
			printf("\n正在返回上一级……\n");
			sleep(2);
			return;
		}
		ad.last_login_time = time(NULL);
		//update_user_info();
	}
	admin_sys();
}

int is_ad_first_run(void)
{
	FILE* fp = fopen("./ad_data","rb");
	
	if(fp == NULL)	return 1;
	
	fclose(fp);

	return 0;
}

int is_user_first_run(void)
{
    FILE* fp = fopen("./ad_data","rb");
    
    if(fp == NULL)  return 1;
    
    fclose(fp);

    return 0;
}


int ad_login_check(const char* user_name, const char* user_pass)
{
		FILE* fp = NULL;
		admin_t ad1;
		char user_pass_md5[33];
		int check_success = 0;

		fp = fopen("./ad_data", "rb");

		if(fp == NULL) return 0;

		md5_encode(user_pass, strlen(user_pass), user_pass_md5);

		if(fread(&ad1, sizeof(ad1), 1, fp) == 1)
		{
			if(strcmp(user_name, ad1.user_name) == 0 && strcmp(user_pass_md5, ad1.user_pass) == 0)
			{
				// 登录验证成功
				ad = ad1;
				check_success = 1;
				//break;
			}
		}
		fclose(fp);
		return check_success;
}

void update_user_info(void)
{
		FILE* fp = NULL;
		user_info ui;

		fp = fopen("./user_data", "r+b");

		if(fp == NULL)
		{
			perror("open user_data fail");

		}

		while(fread(&ui, sizeof(ui), 1, fp) == 1)
		{
			if(strcmp(user.user_name, ui.user_name) == 0)
			{
				fseek(fp, -sizeof(ui), SEEK_CUR);
				fwrite(&user, sizeof(user), 1, fp);
				break;
			}
		}

		fclose(fp);
}

void admin_sys()
{
	int i,a,c;
	while(1)
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
		a = scanf("%d",&i);
		while(a == 0)
		{
			fprintf(stderr, "\n   输入错误，请重新输入\n");
			printf("   请输入:");
			while((c = getchar()) != EOF && c != '\n');
			a = scanf("%d",&i);
		}

		switch(i)
		{
			case 1:
				{	
					//修改用户名和密码
					
				}break;

			case 2:
				{
					//添加用户
					user_add();

				}break;

			case 3:
				{
					//删除用户
					user_del();
				}break;

			case 4:
				{	
					//修改普通用户
					change_user_info();
					//修改用户
					//user_updata();

				}break;

			case 5:
				{	
					//查询用户信息
					while(1)
					{
						if(user_search() <= 0)break;
					}
				}break;

			case 6:
				{
					//增加物资信息
					good* g1;

				}break;

			case 7:
				{

				}break;

			case 8:
				{

				}break;

			case 9:
				{

				}break;

			case 0:
				{
					return;
				}break;

		}

	}
}


//添加普通用户
void user_add(void)
{
		user_info ui;
		char user_pass[31], user_pass_check[31];
		int i,j,c,number;

		while(1)
		{
		system("clear");
		printf("************************************\n");
		printf("*         管理员操作系统           *\n");
		printf("*----------------------------------*\n");
		printf("*     正在进行[增加用户]操作       *\n");
		printf("*----------------------------------*\n");
		printf("*   请按照提示输入普通用户的信息   *\n");
		printf("*       返回上一级请输入[0]        *\n");
		printf("************************************\n");
					
		while(1)
		{
			printf("用户工号:");
			scanf("%d",&number);
			if(number == 0) return;

			ui.job_number = number;

			if(check_user_number(ui.job_number)) break;

			printf("\n-----工号已存在，请重新输入!-----\n");
		}

		while(1)
		 {
			 printf("用户名:");
			 scanf("%s", ui.user_name);

			 if(check_user_name(ui.user_name)) break;

			 printf("\n-----用户名已存在,请重新输入!-----\n");
		 }

		 while(1)
          {
              printf("身份证号:");
              scanf("%s", ui.user_ID);
 
              if(strlen(ui.user_ID) >=6)
			  {
				  for(i = strlen(ui.user_ID);i > 0; i--)
				  {
					 for(j = 6;j > 1;j--)
					 {
						 user_pass[j-1] = ui.user_ID[i];
					 }
				  }
				  break;
			  }

			  printf("\n-----身份证格式有误,请重新输入!-----\n");
          }


		/*
		while(1)
		{
			strcpy(user_pass, getpass("密码："));
			strcpy(user_pass_check, getpass("再次输入密码："));

			if(strcmp(user_pass, user_pass_check) == 0) break;

			printf("\n两次输入的密码不一致，请重新输入！\n");
		}
		*/

		md5_encode(user_pass, strlen(user_pass), ui.user_pass);
		//ui.user_role = 2;
		ui.reg_time = time(NULL);
		ui.last_login_time = 0;
		FILE* fp = fopen("./user_data", "ab");

		if(fp == NULL)
		{
			perror("open user_data fail");
		}
		if(fwrite(&ui, sizeof(ui), 1, fp) == 1);
		{
			printf("\n添加普通用户成功！\n\n");
		}
		fclose(fp);
	
		fflush(stdin);
		printf("************************************\n");
		printf("-----是否继续进行用户添加操作?------\n");
		printf("*    继续(1)        返回上一级(0)  *\n");
		printf("************************************\n");

		while(1)
		{
			printf("请输入:");
			scanf("%d",&c);
		
			if(c == 1)
			{
				break;
			}else if(c == 0)
			{
				return;
			}
			
			printf("\n------输入错误，请重新输入!------\n\n");
		}
		}
}

int check_user_name(const char* user_name)
{
		FILE* fp = NULL;
		user_info ui;
		int check_success = 1;

		fp = fopen("./user_data", "rb");

		if(fp == NULL) return 1;

		while(fread(&ui, sizeof(ui), 1, fp) == 1)
		{
			if(strcmp(user_name, ui.user_name) == 0)
			{
				// 用户名已经存在
				check_success = 0;
				break;
			}
		}

		fclose(fp);
		return check_success;
}

int check_user_number(const int user_number)
{
		FILE* fp = NULL;
		user_info ui;
		int check_success = 1;

		fp = fopen("./user_data", "rb");

		if(fp == NULL) return 1;

		while(fread(&ui, sizeof(ui), 1, fp) == 1)
		{
			if((user_number - ui.job_number) == 0)
			{
				// 工号已经存在
				check_success = 0;
				break;
			}
		}

		fclose(fp);
		return check_success;
}

void user_del(void)
{
	int user_number;
	while(1)
	{
	//	system("clear");
		printf("************************************\n");
		printf("*         管理员操作系统           *\n");
        printf("*----------------------------------*\n");
		printf("*     正在进行[删除用户]操作       *\n");
        printf("*----------------------------------*\n");
        printf("*   请按照提示输入普通用户的信息   *\n");
		printf("*    返回上一级        请输入[0]   *\n");
		printf("************************************\n");
	
		printf("\n请输入要删除的用户工号:");
		scanf("%d", &user_number);
		if(user_number == 0)return;

	FILE* fp = NULL;
	user_info ui;
	int del_success = 0;

	fp = fopen("./user_data", "r+b");

	if(fp == NULL)
	{
		perror("open user_data fail");
	}
	
	while(fread(&ui, sizeof(ui), 1, fp) == 1)
	{
		if((user_number - ui.job_number) == 0)
		{
			fseek(fp, -sizeof(ui), SEEK_CUR);
			memset(&ui, 0, sizeof(ui));
			fwrite(&ui, sizeof(ui), 1, fp);
			del_success = 1;
			break;
		}
	}

	fclose(fp);

	if(del_success)
		printf("\n删除用户 %d 成功！\n", user_number);
	else
		printf("\n用户 %d 不存在，删除失败！\n", user_number);
		
	}
}


void change_user_info(void)
{
	FILE* fp = NULL;
	user_info ui;
	int user_number,i,hold,last_check;
	char user_pass[31], user_pass_check[31];
	while(1)
	{
		system("clear");
		printf("************************************\n");
		printf("*         管理员操作系统           *\n");
		printf("*----------------------------------*\n");
		printf("*     正在进行[修改用户]操作       *\n");
		printf("*----------------------------------*\n");
		printf("*   请按照提示输入普通用户的信息   *\n");
		printf("*        退出修改请输入[0]         *\n");
		printf("************************************\n");
		printf("\n请输入要修改的用户工号:");
		scanf("%d", &user_number);
		if(user_number == 0) return;

		fp = fopen("./user_data", "rb");

		if(fp == NULL)
		{
			perror("open user_data fail");
			return;
		}
	
			printf("%d\n",ui.job_number);
		while(fread(&ui, sizeof(ui), 1, fp) == 1)
		{
			printf("%d\n",ui.job_number);
			if((user_number - ui.job_number) == 0)
			{
			printf("%d\n",ui.job_number);
				   //找到了，就修改它，返回1
				while(1)
			    {
			printf("************************************\n");
	        printf("*      已经找到工号 %d 的用户!     *\n",user_number);
		    printf("*      请选择要修改的信息:         *\n");
	        printf("*      修改用户名        请输入1   *\n");
			printf("*      修改身份证号      请输入2   *\n");
			printf("*      修改密码          请输入3   *\n");
		  //printf("*      修改以上所有      请输入4   *\n");
			printf("*      返回上一级        请输入0   *\n");
			printf("************************************\n");
			printf("请输入:");
			scanf("%d",&i);
			if(i == 0) break;
				}
			}

			switch(i)
			{   
				case 1:
                {   
                    //修改用户名
                    printf("正在修改用户名……\n");
                    printf("请输入新用户名:");
                    scanf("%s",ui.user_name);

                    //printf("修改成功!\n");
                }break;
    
				case 2:
                {   
                    //修改身份证号
					printf("************************************\n");
                    printf("*     正在修改工号[%d]身份证号     *\n",user_number);
					printf("************************************\n");
                    printf("请输入身份证号:");
                    scanf("%s",ui.user_name);
					
					//printf("修改成功!\n");
                }break;

	            case 3:
                {
                    //修改密码
					printf("************************************\n");
                    printf("*       正在修改工号[%d]密码       *\n",user_number);
					printf("************************************\n");
                    //scanf("%s",user_pass);

					while(1)
			        {
						strcpy(user_pass, getpass("请输入新密码:"));
						strcpy(user_pass_check, getpass("再次输入密码:"));
			             if(strcmp(user_pass,user_pass_check) != 0)
				        {
					        printf("\n两次输入的密码不一致,请重新输入\n");
							printf("继续修改请输入[1]，退出请输入[0]\n");
							scanf("%d",hold);
							if(hold == 1) continue;
							if(hold == 0) break;
			            }

						if(strcmp(user_pass,"123456") == 0)
						{
				            printf("\n密码不安全,请重新设置!\n");
				 
				        }
				        else
				        {
							md5_encode(user_pass, strlen(user_pass), ui.user_pass);
							//printf("修改成功!\n");
				            break;
				        }
					}

				}break;

	            case 4:
                {
					break;
                    //修改用户名
				 	printf("************************************\n");
                    printf("*      正在修改工号[%d]用户名      *\n",user_number);
					printf("************************************\n");
                    printf("请输入新用户名:");
                    scanf("%s",ui.user_name);

                    //printf("修改成功!\n");
                }break;

	            case 0:
                {
                }break;
			}
				
			while(1)
			{
				printf("************************************\n");
				printf("*       是否确认本次所做修改?      *\n");
				printf("*          确认/取消  (y/n)        *\n");
				printf("************************************\n");
				printf("请输入:");
				fflush(stdin);
				getchar();
				char cc;
				scanf("%c",&cc);
				last_check = cc;
				
				if(last_check != 'y' && last_check != 'n')
				{
					printf("*       输入错误，请重新输入       *\n");
				}
				else if(last_check == 'y') 
				{
					fseek(fp, -sizeof(ui), SEEK_CUR);
					if(fwrite(&ui, sizeof(ui), 1, fp) == 1)
					{
						printf("本次修改信息成功写入!\n");
						break;
					}else 
					{
						printf("本次修改写入失败,若需要继续修改，请返回上一级重试!\n");
						break;
					}
				}
				else if(last_check == 'n')
				{
						printf("本次修改取消写入,若需要继续修改，请返回上一级重试!\n");
						break;
				}
			}
				break;
			}
	}
	fclose(fp);
}

int user_search(void)
{
	char c;
	int user_number,i;
	user_info ui;
	FILE* fp = NULL;
	fp = fopen("./user_data","rb");

	while(1)
    {
		system("clear");
        printf("************************************\n");
        printf("*         管理员操作系统           *\n");
        printf("*----------------------------------*\n");
        printf("*     正在进行[查询用户]操作       *\n");
        printf("*----------------------------------*\n");
        printf("*         请按照提示输入           *\n");
		printf("*    返回上一级        请输入[0]   *\n");
        printf("************************************\n");
		printf("想要查找的用户工号:");
		scanf("%d", &user_number);
		getchar();

		if(user_number == 0) return 0;

		while(fread(&ui, sizeof(ui),1,fp) == 1)
		{	
			if(fp == NULL)
			{	
				printf("\nOPEN FILE FAIL!\n");
			}
			
			if((user_number - ui.job_number) == 0)
             {
				 printf("\n");
				 printf("工号:%d\n",ui.job_number);
				 printf("用户名:%s\n",ui.user_name);
				 printf("身份证号:%s\n",ui.user_ID);
				 printf("注册时间:%ld\n",ui.reg_time);
				 printf("最近一次登陆时间:%ld\n",ui.last_login_time);
				 printf("\n");
				 break;
			 }
		}

		while(1)
		{
			printf("************************************\n");
			printf("*-----------是否继续查找?----------*\n");
			printf("*      继续[y]         返回[n]     *\n");
			printf("************************************\n");
			printf("请输入:");
			scanf("%c",&c);
			if(c == 'y') 
			{
				return 1;
			}
			else if(c == 'n') 
			  {
				  return -1;
			  }

			printf("输入错误，请重新输入!\n");
		}
	}

	fclose(fp);
}
