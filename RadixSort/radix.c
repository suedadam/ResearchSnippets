#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct	s_radix
{
	void	*ptr;
	int		num;
}				t_radix;

typedef struct	s_node
{
	void			*content;
	struct s_node	*next;
}				t_node;

typedef struct	s_queue
{
	t_node	*first;
	t_node	*last;
}				t_queue;

t_queue	*init_queue(void)
{
	t_queue	*ret;

	if (!(ret = calloc(1, sizeof(t_queue))))
		return (NULL);
	return (ret);
}

void	add_queue(t_queue *queue, void *ptr)
{
	t_node *node;

	if (!(node = calloc(1, sizeof(t_node))))
		return ;
	node->content = ptr;
	if (!queue->first)
	{
		queue->first = node;
		return ;
	}
	if (!queue->last)
	{
		queue->first->next = node;
		queue->last = node;
		return ;
	}
	queue->last->next = node;
	queue->last = node;
}

void	*pop_queue(t_queue *queue)
{
	void	*content;
	void	*tmp;

	if (!queue || !queue->first)
		return (NULL);
	content = queue->first->content;
	tmp = queue->first;
	queue->first = queue->first->next;
	if (queue->first == queue->last)
		queue->last = NULL;
	free(tmp);
	return (content);
}

void	init_radix(int *notsorted, size_t len, t_queue **numbers)
{
	size_t	i;
	t_radix	*radix;

	if (!(*numbers = init_queue()))
		return ;
	i = 0;
	while (i < len)
	{
		if (!(radix = calloc(1, sizeof(t_radix))))
		{
			printf("Failed to allocate %zd (%s)\n", i, strerror(errno));
			return ;
		}
		radix->ptr = &(notsorted[i]);
		radix->num = notsorted[i];
		add_queue(*numbers, radix);
		i++;
	}
}

void	pop_all(t_queue **buckets, t_queue *numbers)
{
	int		i;
	t_radix	*val;

	i = 0;
	while (i < 10)
	{
		while ((val = pop_queue(buckets[i])))
			add_queue(numbers, val);
		i++;
	}
}

void	*copy_queue(t_queue *numbers, size_t len)
{
	size_t	i;
	t_radix	*num;
	int		*ret;

	i = 0;
	if (!(ret = calloc(len, sizeof(int))))
		return (NULL);
	while (i < len)
	{
		if (!(num = pop_queue(numbers)))
			return (NULL);
		memcpy(&(ret[i]), &(*(int *)num->ptr), sizeof(int));
		free(num);
		i++;
	}
	return (ret);
}

int 	*radix_sort(int *notsorted, size_t len)
{
	int		i;
	uint8_t	done;
	t_queue	**buckets;
	t_queue *numbers;
	t_radix	*num;
	int		*ret;

	init_radix(notsorted, len, &numbers);
	if (!(buckets = calloc(11, sizeof(void *))))
		return (NULL);
	i = 0;
	while (i < 10)
	{
		if (!(buckets[i] = init_queue()))
		{
			printf("Failed to init %d\n", i);
			continue ;
		}
		i++;
	}
	done = 1;
	while (done)
	{
		done = 0;
		while ((num = pop_queue(numbers)))
		{
			if (num->num)
				done = 1;
			add_queue(buckets[num->num % 10], num);
			num->num /= 10;
		}
		pop_all(buckets, numbers);
	}
	if (!(ret = copy_queue(numbers, len)))
		return (NULL);
	free(notsorted);
	return (ret);
}

int		main(int argc, char *argv[])
{
	int	i;
	int	*notsorted = calloc(argc + 1, sizeof(int));

	i = 1;
	while (i < (argc - 1))
	{
		notsorted[i - 1] = atoi(argv[i]);
		i++;
	}
	i = 0;
	while (i < (argc - 1))
	{
		printf("[%d] = %d\n", i, notsorted[i]);
		i++;
	}
	if (!(notsorted = radix_sort(notsorted, argc - 1)))
	{
		printf("Failed!\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < (argc - 1))
	{
		printf("{Sorted} [%d] = %d\n", i, notsorted[i]);
		i++;
	}
}