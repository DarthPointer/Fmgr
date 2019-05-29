#pragma once

#include <stdio.h>




void getulli(ULLI &a, bool &err) //Checking for overflow
{
	char buff;
	bool finish = 0, first = 1;
	a = 0;
	err = 0;
	do 
	{
		buff = getchar();
		if ((buff > 47)*(buff < 58))
		{
			first = 0;
			if (a < ULLI(1844674407370955162))
			{
				a *= 10;
				if (ULLI(MULLI - buff + 48) >= a)
				{
					a += buff - 48;
				}
				else
				{
					err = 1;
				}
			}
			else
			{
				err = 1;
			}
		}
		else if ((buff == '\n')*(!first))
		{
			finish = 1;
		}
		else
		{
			err = 1;
		}
	} while ((!finish)*(!err));
	FLUSH;
}

void requlli(ULLI &a, char *request, bool &err)
{
	printf("%s", request);
	getulli(a, err);
}




void getui(UI &a, bool &err)
{
	char buff = getchar();
	bool finish = 0, first = 1;
	a = 0;
	err = 0;
	do
	{
		if ((buff > 47)*(buff < 58))
		{
			first = 0;
			if (a < 6533u)
			{
				a *= 10;
				if (UI(MUI - buff + 48) >= a)
				{
					a += buff - 48;
				}
				else
				{
					err = 1;
				}
			}
			else
			{
				err = 1;
			}
		}
		else if ((buff == 0)*(!first))
		{
			finish = 1;
		}
		else
		{
			err = 1;
		}
		buff++;
	} while ((!finish)*(!err));
}

void requi(UI &a, char *request, bool &err)
{
	printf("%s", request);
	getui(a, err);
}