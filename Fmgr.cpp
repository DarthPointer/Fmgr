#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <locale.h>

#include "pasta.h"

#include "CIO.h"
#include "cmdmgr.h"


int main(int argc, char **argv)
{
	setlocale(0, "RUS");
	bool r = 1;
	if (argc == 1)
	{
		printf("%s\n", "Fmgr запущен без параметров - вводите необходимые команды, для выхода введите \"exit\"");
		while (r)
		{
			catchcmd(r);
		}
	}
	else
	{
		operatecmd(r, argv + 1, argc - 1);
	}
    return 0;
}