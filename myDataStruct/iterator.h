
typedef void *iterator_t;
typedef void (*iterator_next_t)(iterator_t *p_iter);
typedef void (*iterator_prev_t)(iterator_t *p_iter);

typedef struct _iterator_if
{
	iterator_next_t pfn_next;
	iterator_prev_t pfn_prev;
} iterator_if_t;


void iterator_if_init(iterator_if_t *p_if, iterator_next_t pfn_next, iterator_prev_t pfn_prev);
void iterator_next(iterator_if_t *p_if, iterator_t *p_iter);
void iterator_prev(iterator_if_t *p_if, iterator_t *p_iter);
