#include <stdio.h>
#include "iterator.h"
#include "dlist.h"


void iterator_if_init(iterator_if_t *p_if, iterator_next_t pfn_next, iterator_prev_t pfn_prev)
{
	p_if->pfn_next = pfn_next;
	p_if->pfn_prev = pfn_prev;
}
void iterator_next(iterator_if_t *p_if, iterator_t *p_iter)
{
	p_if->pfn_next(p_iter);
}
void iterator_prev(iterator_if_t *p_if, iterator_t *p_iter)
{
	p_if->pfn_prev(p_iter);
}
//*****************
typedef struct _dlist_int
{
	dlist_node_t node;
	int data;
} dlist_int_t;
// int list_node_process(void *p_arg, dlist_node_t *p_node)
// {
// 	printf("%d .\r\n", ((dlist_int_t *)p_node)->data);
// 	return 0;
// }
//?????????????
typedef int (*swap_t)(iterator_t it1, iterator_t it2); 
static int _swap(iterator_t it1, iterator_t it2)
{ //
	int data=((dlist_int_t *)it1) -> data;
	((dlist_int_t *)it1) -> data=((dlist_int_t *)it2) -> data;
	((dlist_int_t *)it2) -> data=data;
}
typedef int (*compare_t)(iterator_t it1, iterator_t it2); 
static int _compare(iterator_t it1, iterator_t it2)
{ //
	return ((dlist_int_t *)it1)->data - ((dlist_int_t *)it2)->data;
}
static void __dlist_iterator_next(iterator_t *p_iter)
{
	*p_iter = ((dlist_node_t *)*p_iter)->p_next;
}
static void __dlist_iterator_prev(iterator_t *p_iter)
{
	*p_iter = ((dlist_int_t *)*p_iter)->node.p_prev;
}


void dlist_iterator_if_get(iterator_if_t *p_if)
{
	iterator_if_init(p_if, __dlist_iterator_next, __dlist_iterator_prev);
}
//**************

void iter_sort(iterator_if_t *p_if, iterator_t begin, iterator_t end, compare_t compare, swap_t swap)
{
	int flag = 1;
	iterator_t it1 = begin;
	iterator_t it2 = end;
	iterator_t it_next;
	if (begin == end)
	{
		return;
	}
	iterator_prev(p_if, &it2);
	while (it2 != begin)
	{
		it1 = begin;
		flag = 1;
		while (it1 != it2)
		{
			it_next = it1;
			iterator_next(p_if, &it_next);
			if (compare(it1, it_next) > 0)
			{
				swap(it1, it_next);
				flag = 0;
			}
			it1 = it_next;
		}
		if (flag)
			return;
		iterator_prev(p_if, &it2);
	}
}
int main()
{
	dlist_node_t head01;
	dlist_int_t a, b, c, d;
	dlist_init(&head01);
	a.data = 221;
	b.data = 2;
	c.data = 3;
	d.data = 6666;
	dlist_add_tail(&head01, &a.node);
	dlist_add_tail(&head01, &b.node);
	dlist_add_tail(&head01, &c.node);
	dlist_add_tail(&head01, &d.node);

	iterator_if_t if_dlist;
	dlist_iterator_if_get(&if_dlist);

	iter_sort(&if_dlist, dlist_begin_get(&head01), dlist_tail_get(&head01), _compare, _swap);
	dlist_foreach(&head01,a.data,list_node_process);
}
