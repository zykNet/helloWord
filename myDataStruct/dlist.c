#include <stdio.h>
#include "dlist.h"
dlist_node_t *dlist_prev_get(dlist_head_t *p_head, dlist_node_t *p_pos)
{
	if (p_head == NULL)
	{
		return NULL;
	}
	return p_pos->p_prev;
}
dlist_node_t *dlist_next_get(dlist_head_t *p_head, dlist_node_t *p_pos)
{
	if (p_head == NULL)
	{
		return NULL;
	}
	return p_pos->p_next;
}
dlist_node_t *dlist_tail_get(dlist_head_t *p_head)
{
	if (p_head == NULL)
	{
		return NULL;
	}
	return p_head->p_prev;
}
dlist_node_t *dlist_begin_get(dlist_head_t *p_head)
{
	if (p_head == NULL)
	{
		return NULL;
	}
	return p_head->p_next;
}
dlist_node_t *dlist_end_get(dlist_head_t *p_head)
{
	if (p_head == NULL)
	{
		return NULL;
	}
	return p_head->p_prev;
}
int dlist_init(dlist_head_t *p_head)
{
	if (p_head == NULL)
	{
		return -1;
	}
	p_head->p_next = p_head;
	p_head->p_prev = p_head;
	return 0;
}
int dlist_add(dlist_head_t *p_head, dlist_node_t *p_pos, dlist_node_t *p_node)
{
	if (p_head == NULL || p_pos == NULL)
	{
		return -1;
	}
	p_node->p_prev = p_pos->p_prev;
	p_node->p_next = p_pos;
	p_node->p_prev->p_next = p_node;
	p_node->p_next->p_prev = p_node;
	return 0;
}
int dlist_add_tail(dlist_head_t *p_head, dlist_node_t *p_node)
{
	if (p_head == NULL)
	{
		return -1;
	}
	p_node->p_prev = p_head->p_prev;
	p_node->p_next = p_head;
	p_head->p_prev->p_next = p_node;
	p_head->p_prev = p_node;
	return 0;
}
int dlist_add_head(dlist_head_t *p_head, dlist_node_t *p_node)
{
	if (p_head == NULL)
	{
		return -1;
	}
	p_node->p_prev = p_head;
	p_node->p_next = p_head->p_next;

	// p_node->p_prev->p_next = p_node;
	// p_node->p_next->p_prev = p_node;

	p_head->p_next->p_prev = p_node;
	p_head->p_next = p_node;
	return 0;
}
int dlist_del(dlist_head_t *p_head, dlist_node_t *p_node)
{
	if (p_node == NULL)
	{
		return -1;
	}
	p_node->p_prev->p_next = p_node->p_next;
	p_node->p_next->p_prev = p_node->p_prev;
	p_node->p_prev = NULL;
	p_node->p_next = NULL;
	return 0;
}

int dlist_foreach(dlist_head_t *p_head,
					void *p_arg,
				  dlist_node_process_t pfn_node_process
				  )
{
	dlist_node_t *p_tmp, *p_end;
	int ret;
	if ((p_head == NULL) || (pfn_node_process == NULL))
	{
		return -1;
	}
	p_tmp = dlist_begin_get(p_head);
	p_end = dlist_end_get(p_head);
	while (p_tmp != p_end->p_next)
	{
		ret = pfn_node_process(p_arg, p_tmp);
		if (ret < 0)
		{
			return ret;
		}
		p_tmp = dlist_next_get(p_head, p_tmp); 
	}
	return 0;
}

//************main***

typedef struct _dlist_int
{
	dlist_node_t node;
	int data;
} dlist_int_t;

// int my_addf(void *arg, dlist_node_t *p_node)
// {
// 	((dlist_int_t *)(p_node))->data += arg;
// 	return 1;
// }
int list_node_process(void *p_arg, dlist_node_t *p_node)
{
	printf("%d .\r\n", ((dlist_int_t *)p_node)->data); // ((dlist_int_t *)p_node) -> data
	return 0;
}
int dlist_test()
{
	dlist_head_t head01;
	dlist_node_t *p_buf;
	dlist_int_t a, b, c, d;
	printf("niHao***\r\n");
	dlist_init(&head01);
	a.data = 1;
	b.data = 2;
	c.data = 3;
	d.data = 44;
	dlist_add_tail(&head01, &a.node);
	dlist_add_tail(&head01, &d.node);
	dlist_add_tail(&head01, &b.node);
	dlist_add_tail(&head01, &c.node);
	b.data=dlist_foreach(&head01,  (void*)a.data,list_node_process);
	// p_buf=(dlist_begin_get(&head01));
	// //p_buf=(dlist_node_t*)b;
	// printf("%d .\r\n", ((dlist_int_t *)p_buf)->data);

	dlist_del(&a.node, &a.node);
	b.data=dlist_foreach(&head01,  (void*)a.data,list_node_process);

}