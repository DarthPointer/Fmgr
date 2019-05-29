#pragma once

#include "malloc.h"

struct strg  //вспомогательная структура, элемент списка-строки
{
	char body[10] = { 0 };
	strg *next = 0;
};

struct str
{
	strg *first = 0, *last = 0;
	UI len;
};

struct word
{
	str body;
	word *next = 0;
};

struct wlist
{
	word *first = 0, *last = 0;
	UI num;
};

void inl(strg &a, char &l)
{
	int c = getchar();
	l = 0;
	while ((l - 10)*(c != '\n'))
	{
		a.body[l++] = c;
		if (l != 10)
		{
			c = getchar();
		}
	}
	if (l < 10)
	{
		a.body[l] = 0;
	}
}

void inl(str &a)
{
	char l;
	a.first = (strg*)malloc(sizeof(strg));
	a.last = a.first;
	inl(*a.first, l);
	a.len = l;
	a.first->next = 0;
	while (l == 10)
	{
		a.last->next = (strg*)malloc(sizeof(strg));
		a.last = a.last->next;
		a.last->next = 0;
		inl(*a.last, l);
		a.len += l;
	}
}

void finl(strg &a, char &l, int &c, FILE *f)
{
	c = getc(f);
	l = 0;
	while ((l - 10)*(c != '\n')*(c != -1))
	{
		a.body[l++] = c;
		if (l != 10)
		{
			c = getc(f);
		}
	}
	if (l < 10)
	{
		a.body[l] = 0;
	}
}

void finl(str &a, int &c, FILE *f)
{
	char l;
	a.first = (strg*)malloc(sizeof(strg));
	a.last = a.first;
	finl(*a.first, l, c, f);
	a.len = l;
	a.first->next = 0;
	while ((l == 10)*(c != '\n')*(c != -1))
	{
		a.last->next = (strg*)malloc(sizeof(strg));
		a.last = a.last->next;
		a.last->next = 0;
		finl(*a.last, l, c, f);
		a.len += l;
	}
}

void inw(strg &a, char &l, int &c)
{
	c = getchar();
	l = 0;
	while ((l != 10)*(c != '\n')*(c != ' '))
	{
		a.body[l++] = c;
		if (l != 10)
		{
			c = getchar();
		}
	}
	if (l < 10)
	{
		a.body[l] = 0;
	}
}

void inw(str &a, int &c)
{
	char l;
	a.first = (strg*)malloc(sizeof(strg));
	a.last = a.first;
	inw(*a.first, l, c);
	a.len = l;
	a.first->next = 0;
	while ((l == 10)*(c != '\n')*(c != ' '))
	{
		a.last->next = (strg*)malloc(sizeof(strg));
		a.last = a.last->next;
		a.last->next = 0;
		inw(*a.last, l, c);
		a.len += l;
	}
}

void inw(wlist &a)
{
	a.num = 1;
	int c;
	a.first = (word*)malloc(sizeof(word));
	a.last = a.first;
	a.first->next = 0;
	inw(a.first->body, c);
	while (c != '\n')
	{
		a.num++;
		a.last->next = (word*)malloc(sizeof(word));
		a.last = a.last->next;
		a.last->next = 0;
		inw(a.last->body, c);
	}
}



void copy(str &a, char *&p)
{
	p = (char*)calloc(a.len + 1, sizeof(char));
	strg *ptr = a.first;
	char j = 0;
	for (UI i = 0; i < a.len; i++)
	{
		p[i] = ptr->body[j++];
		if (j == 10)
		{
			j = 0;
			ptr = ptr->next;
		}
	}
	p[a.len] = 0;
}

void copy(wlist &a, char **&p, UI &l)
{
	l = a.num;
	p = (char**)calloc(a.num, sizeof(char*));
	word *ptr = a.first;
	for (UI i = 0; i < l; i++)
	{
		copy(ptr->body, p[i]);
		ptr = ptr->next;
	}
}



bool cmp(strg &a, strg &b)
{
	char i = 0;
	bool f = 1;
	while ((i < 10) * (f))
	{
		if ((!a.body[i]) * (!b.body[i]))
		{
			f = 1;
		}
		f = (a.body[i] == b.body[i++]);
	}
	return f;
}

bool cmp(str &a, str &b)
{
	strg *p1 = a.first, *p2 = b.first;
	bool f = (a.len == b.len);
	while ((p1 != 0)*(f))
	{
		f = cmp(*p1, *p2);
		p1 = p1->next;
		p2 = p2->next;
	}
	return f;
}

bool cmp(char *a, char *b)
{
	bool f = 1;
	while (((*a != 0) + (*b != 0))*(f))
	{
		if (*a != *b)
		{
			f = 0;
		}
		a++;
		b++;
	}
	return f;
}



void wipe(str &a)
{
	strg *c = a.first, *n = 0;
	while (c)
	{
		n = c->next;
		free(c);
		c = n;
	}
	a.first = 0;
	a.last = 0;
}