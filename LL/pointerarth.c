/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointerarth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 02:35:13 by asyed             #+#    #+#             */
/*   Updated: 2018/02/26 02:47:39 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TO_DATA(type, list) (type *)(list + 1)
#define TO_HEAD(data) (((t_list *)data) - 1)

typedef struct	s_list {
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct 	s_data {
	char	*name;
}				t_data;

int	main(void)
{
	t_list *linkedlist;

	if (!(linkedlist = malloc(sizeof(t_list) + sizeof(t_data))))
		return (-1);
	(TO_DATA(t_data, linkedlist))->name = strdup("Hello World");
	linkedlist->next = NULL;
	linkedlist->prev = NULL;
	printf("%s\n", (TO_DATA(t_data, linkedlist))->name);
}