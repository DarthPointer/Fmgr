#pragma once

#include "strg.h"

void input(char *fname, ULLI l)
{
	FILE *f = fopen(fname, "w");
	printf("%s\n", "���� �����:");
	for (ULLI i = 0; i < l; i++)
	{
		str a;
		inl(a);
		char *p;
		copy(a, p);
		fprintf(f, "%s\n", p);
	}
	printf("%s\n", "���� ��������");
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
		printf("%s\n", "���������: ");
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
		printf("%s\n", "���������:");
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
		printf("%s\n", "��������� �������:");
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
		printf("%s: %llu, %s: %llu\n", "�����", sum, "���������", diff);
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
			printf("%s\n", "������� \"exit\" �� ��������� ����������");
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
					printf("%s\n", "������");
				}
				else
				{
					input(p[1], n);
				}
			}
			else
			{
				printf("%s\n", "\"input\" ������� 2 ��������� (��� ����� � ���������� �����)");
				printf("%s", "��� �����: ");
				str a;
				inl(a);
				bool b;
				char *fname;
				copy(a, fname);
				requlli(n, "���������� ����: ", b);
				if (b)
				{
					printf("%s\n", "������");
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
				printf("%s\n", "������");
			}
			else
			{
				mixlines(p[1], p[2], p[3], n, err);
				if (err)
				{
					printf("%s\n", "������");
				}
			}
		}
		else
		{
			printf("%s\n", "������� \"mixlines\" ������� 4 ��������� (����� ������ 1, 2 � ������, ������ �����������");
			str s;
			char *f1, *f2, *res;
			printf("%s", "������� ��� ������� ��������� �����: ");
			inl(s);
			copy(s, f1);
			wipe(s);
			printf("%s", "������� ��� ������� ��������� �����: ");
			inl(s);
			copy(s, f2);
			wipe(s);
			printf("%s", "������� ��� ��������� �����: ");
			inl(s);
			copy(s, res);
			bool b;
			requi(n, "������� ������ ����������: ", b);
			if (b)
			{
				printf("%s\n", "������");
			}
			else
			{
				bool err;
				mixlines(f1, f2, res, n, err);
				if (err)
				{
					printf("%s\n", "������");
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
				printf("%s\n", "������");
			}
		}
		else
		{
			printf("%s\n", "������� \"ralign\" ������� 2 ��������� (����� ��������� � ��������� ������)");
			str s;
			char *f1, *f2;
			printf("%s", "������� ��� ��������� �����: ");
			inl(s);
			copy(s, f1);
			wipe(s);
			printf("%s", "������� ��� ��������� �����: ");
			inl(s);
			copy(s, f2);
			bool err;
			ralign(f1, f2, err);
			if (err)
			{
				printf("%s\n", "������");
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
				printf("%s\n", "������");
			}
			else if (f)
			{
				printf("%s \"%s\" %s %llu\n", "�����", p[2], "������� �� �������", pos);
			}
			else
			{
				printf("%s \"%s\" %s\n", "�����", p[2], "�� �������");
			}
		}
		else
		{
			printf("%s\n", "������� \"find\" ������� 2 ��������� (��� ����� � ����� ��� ������)");
			str s;
			char *fn, *word;
			printf("%s", "������� ��� �����: ");
			inl(s);
			copy(s, fn);
			wipe(s);
			printf("%s", "������� ����� ��� ������: ");
			inl(s);
			copy(s, word);
			bool err;
			find(fn, word, pos, f, err);
			if (err)
			{
				printf("%s\n", "������");
			}
			else if (f)
			{
				printf("%s \"%s\" %s %llu\n", "�����", word, "������� �� �������", pos);
			}
			else
			{
				printf("%s \"%s\" %s\n", "�����", word, "�� �������");
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
				printf("%s\n", "������");
			}
		}
		else
		{
			printf("%s\n", "������� \"countsymbs\" ������� 1 �������� (��� �����)");
			str s;
			char *f;
			printf("%s", "������� ��� �����: ");
			inl(s);
			copy(s, f);
			countsymbs(f, err);
			if (err)
			{
				printf("%s\n", "������");
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