#pragma once

#include "strg.h"

void input(char *fname, ULLI l)
{
	FILE *f = fopen(fname, "w");
	printf("%s\n", "Ввод файла:");
	for (ULLI i = 0; i < l; i++)
	{
		str a;
		inl(a);
		char *p;
		copy(a, p);
		fprintf(f, "%s\n", p);
	}
	printf("%s\n", "Ввод закончен");
	fclose(f);
}

void mixlines(char *fn1, char *fn2, char *resn, UI n, bool &err)
{
	FILE *f1 = fopen(fn1, "r"), *f2 = fopen(fn2, "r"), *res = fopen(resn, "w");
	if (bool(f1)*bool(f2))
	{
		err = 0;
		int c1 = 0, c2 = 0;
		UI i = 0;
		printf("%s\n", "Результат: ");
		while ((c1 != -1) + (c2 != -1))
		{
			str s;
			char *p;
			if ((c1 != -1)*((i < n)) + (c2 == -1))
			{
				finl(s, c1, f1);
			}
			else
			{
				finl(s, c2, f2);
			}
			if (s.len)
			{
				copy(s, p);
				fprintf(res, "%s\n", p);
				printf("%s\n", p);
			}
			wipe(s);
			i++;
			if (i == (2 * n))
			{
				i = 0;
			}
		}
		printf("%s\n", "----------");
	}
	else
	{
		err = 1;
	}
}

void ralign(char *fn, char *resn, bool &err)
{
	FILE *f = fopen(fn, "r"), *res = fopen(resn, "w");
	if (f)
	{
		err = 0;
		printf("%s\n", "Результат:");
		str s;
		char *p;
		int c = 0;
		UI max = 0;
		while (c != -1)
		{
			finl(s, c, f);
			if (s.len > max)
			{
				max = s.len;
			}
			wipe(s);
		}
		fclose(f);
		f = fopen(fn, "r");
		c = 0;
		while (c != -1)
		{
			finl(s, c, f);
			for (UI i = s.len; i < max; i++)
			{
				putc(' ', res);
				putchar(' ');
			}
			copy(s, p);
			fprintf(res, "%s\n", p);
			printf("%s\n", p);
			wipe(s);
		}
		fclose(res);
		printf("%s\n", "----------");
	}
	else
	{
		err = 1;
	}
}

void find(char *fn, char *word, ULLI &pos, bool &b, bool &err)
{
	char *p = word;
	pos = 0;
	ULLI cpos = 0;
	b = 0;
	FILE *f = fopen(fn, "r");
	if (f)
	{
		err = 0;
		int c = getc(f), prev = '\n';
		while ((c != -1) * (!b))
		{
			if (pos == cpos)
			{
				if ((*p == c)*((prev == '\n')+(prev == ' ')))
				{
					p++;
				}
				else
				{
					pos++;
				}
				cpos++;
			}
			else
			{
				cpos++;
				if (!*p)
				{
					if ((c == '\n')+(c == ' '))
					{
						b = 1;
					}
					else
					{
						cpos++;
						pos = cpos;
						p = word;
					}
				}
				else if (*p == c)
				{
					p++;
				}
				else
				{
					pos = cpos;
					p = word;
				}
			}
			prev = c;
			c = getc(f);
		}
		if (!*p)
		{
			b = 1;
		}
		printf("%s\n", "----------");
	}
	else
	{
		err = 1;
	}
}

void countsymbs(char *fn, bool &err)
{
	FILE *f = fopen(fn, "r");
	if (f)
	{
		printf("%s\n", "Найденные символы:");
		err = 0;
		ULLI codes[256] = { 0 }, sum = 0, diff = 0;
		int c = getc(f);
		while (c != -1)
		{
			codes[c]++;
			c = getc(f);
		}
		for (int i = 0; i < 256; i++)
		{
			if (codes[i])
			{
				sum += codes[i];
				diff++;
				if (i < 32)
				{
					printf("(%d): ", i);
				}
				else
				{
					printf("\"%c\": ", i);
				}
				printf("%llu  ", codes[i]);
				for (ULLI j = 0; j < codes[i]; j++)
				{
					printf("%c", '+');
				}
				printf("%c", '\n');
			}
		}
		printf("%s: %llu, %s: %llu\n", "Итого", sum, "различных", diff);
		printf("%s\n", "----------");
	}
	else
	{
		err = 1;
	}
}

void operatecmd(bool &r, char **p, UI l)
{
	if (cmp(p[0], "exit"))
	{
		if (l != 1)
		{
			printf("%s\n", "Команда \"exit\" не принимает параметров");
		}
		else
		{
			r = 0;
		}
	}
	if (cmp(p[0], "input"))
	{
		{
			ULLI n;
			if (l == 3)
			{
				char *buff = p[2];
				bool finish = 0, first = 1;
				n = 0;
				bool err = 0;
				do
				{
					if ((*buff > 47)*(*buff < 58))
					{
						first = 0;
						if (n < ULLI(1844674407370955162))
						{
							n *= 10;
							if (ULLI(MULLI - *buff + 48) >= n)
							{
								n += *buff - 48;
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
					else if ((*buff == 0)*(!first))
					{
						finish = 1;
					}
					else
					{
						err = 1;
					}
					buff++;
				} while ((!finish)*(!err));
				if (err)
				{
					printf("%s\n", "Ошибка");
				}
				else
				{
					input(p[1], n);
				}
			}
			else
			{
				printf("%s\n", "\"input\" требует 2 параметра (имя файла и количество строк)");
				printf("%s", "Имя файла: ");
				str a;
				inl(a);
				bool b;
				char *fname;
				copy(a, fname);
				requlli(n, "Количество срок: ", b);
				if (b)
				{
					printf("%s\n", "Ошибка");
				}
				else
				{
					input(fname, n);
				}
			}
		}
	}
	else if (cmp(p[0], "mixlines"))
	{
		UI n;
		if (l == 5)
		{
			char *buff = p[4];
			bool finish = 0, first = 1;
			n = 0;
			bool err = 0;
			do
			{
				if ((*buff > 47)*(*buff < 58))
				{
					first = 0;
					if (n < 6533u)
					{
						n *= 10;
						if (UI(MUI - *buff + 48) >= n)
						{
							n += *buff - 48;
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
				else if ((*buff == 0)*(!first))
				{
					finish = 1;
				}
				else
				{
					err = 1;
				}
				buff++;
			} while ((!finish)*(!err));
			if (err)
			{
				printf("%s\n", "Ошибка");
			}
			else
			{
				mixlines(p[1], p[2], p[3], n, err);
				if (err)
				{
					printf("%s\n", "Ошибка");
				}
			}
		}
		else
		{
			printf("%s\n", "Команда \"mixlines\" требует 4 параметра (имена файлов 1, 2 и вывода, период чередований");
			str s;
			char *f1, *f2, *res;
			printf("%s", "Введите имя первого исходного фалйа: ");
			inl(s);
			copy(s, f1);
			wipe(s);
			printf("%s", "Введите имя второго исходного фалйа: ");
			inl(s);
			copy(s, f2);
			wipe(s);
			printf("%s", "Введите имя конечного фалйа: ");
			inl(s);
			copy(s, res);
			bool b;
			requi(n, "Введите период чередваний: ", b);
			if (b)
			{
				printf("%s\n", "Ошибка");
			}
			else
			{
				bool err;
				mixlines(f1, f2, res, n, err);
				if (err)
				{
					printf("%s\n", "Ошибка");
				}
			}
		}
	}
	else if (cmp(p[0], "ralign"))
	{
		if (l == 3)
		{
			bool err;
			ralign(p[1], p[2], err);
			if (err)
			{
				printf("%s\n", "Ошибка");
			}
		}
		else
		{
			printf("%s\n", "Команда \"ralign\" требует 2 параметра (имена исходного и конечного файлов)");
			str s;
			char *f1, *f2;
			printf("%s", "Введите имя исходного файла: ");
			inl(s);
			copy(s, f1);
			wipe(s);
			printf("%s", "Введите имя конечного файла: ");
			inl(s);
			copy(s, f2);
			bool err;
			ralign(f1, f2, err);
			if (err)
			{
				printf("%s\n", "Ошибка");
			}
		}
	}
	else if (cmp(p[0], "find"))
	{
		ULLI pos;
		bool f;
		if (l == 3)
		{
			bool err;
			find(p[1], p[2], pos, f, err);
			if (err)
			{
				printf("%s\n", "Ошибка");
			}
			else if (f)
			{
				printf("%s \"%s\" %s %llu\n", "Слово", p[2], "найдено на позиции", pos);
			}
			else
			{
				printf("%s \"%s\" %s\n", "Слово", p[2], "не найдено");
			}
		}
		else
		{
			printf("%s\n", "Команда \"find\" требует 2 параметра (имя файла и слово для поиска)");
			str s;
			char *fn, *word;
			printf("%s", "Введите имя файла: ");
			inl(s);
			copy(s, fn);
			wipe(s);
			printf("%s", "Введите слово для поиска: ");
			inl(s);
			copy(s, word);
			bool err;
			find(fn, word, pos, f, err);
			if (err)
			{
				printf("%s\n", "Ошибка");
			}
			else if (f)
			{
				printf("%s \"%s\" %s %llu\n", "Слово", word, "найдено на позиции", pos);
			}
			else
			{
				printf("%s \"%s\" %s\n", "Слово", word, "не найдено");
			}
		}
	}
	else if (cmp(p[0], "countsymbs"))
	{
		bool err;
		if (l == 2)
		{
			countsymbs(p[1], err);
			if (err)
			{
				printf("%s\n", "Ошибка");
			}
		}
		else
		{
			printf("%s\n", "Команда \"countsymbs\" требует 1 параметр (имя файла)");
			str s;
			char *f;
			printf("%s", "Введите имя файла: ");
			inl(s);
			copy(s, f);
			countsymbs(f, err);
			if (err)
			{
				printf("%s\n", "Ошибка");
			}
		}
	}
}

void catchcmd(bool &r)
{
	wlist a;
	printf("%s", "~~ ");
	inw(a);
	char **p;
	UI l;
	copy(a, p, l);
	operatecmd(r, p, l);
}