#include <stdio.h>
#include <time.h>



void get_date(long t)
{
	time_t test = time(NULL);
	if(t - 1 < 0)
	{
		printf("NULL\n");
		return;
	}

	long hour, minute, second, weekday;
	second = t % 60;
	minute = t / 60 % 60;
	hour = (t / 3600 + 8) % 24;
	weekday = (t / (24 * 3600) + 4) % 7;

	

	t = t + 8 * 3600;
	long total_days = t / (24 * 60 * 60);

	int year = 1970, month = 1, day = 1, i;

	for(i = 0; i < total_days; i++)
	{
		day++;

		switch(month)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			if(day > 31)
			{
				month++;
				day = 1;
			}
			break;

			case 12:
			if(day > 31)
			{
				year++;
				month = 1;
				day = 1;
			}
			break;

			case 4:
			case 6:
			case 9:
			case 11:
			if(day > 30)
			{
				month++;
				day = 1;
			}
			break;

			case 2:

			if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
			{
				// 闰年
				if(day > 29)
				{
					month++;
					day = 1;
				}
			}
			else
			{
				// 平年
				if(day > 28)
				{
					month++;
					day = 1;
				}
			}

			break;
		}
		
	}

	printf("%d年%d月%d日", year, month, day);
	//printf("%ld:%02ld:%02ld 星期%ld\n", hour, minute, second, weekday);
	printf("星期%ld %ld:%02ld:%02ld\n", weekday, hour, minute, second);

	return;
}
