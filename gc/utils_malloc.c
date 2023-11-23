/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:54:09 by asabri            #+#    #+#             */
/*   Updated: 2023/11/23 15:09:47 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	addfront2(t_data1 **head, t_data1 *new)
{
	if (*head)
		new->next = *head;
	*head = new;
}

void	listclear2(t_data1 **head)
{
	t_data1	*tmp;
	t_data1	*ptr;

	if (!head)
		return ;
	tmp = *head;
	while (tmp)
	{
		ptr = tmp;
		tmp = tmp->next;
		free(ptr->data);
		free(ptr);
	}
	*head = NULL;
}

t_malloc	*newmalloc(void *data)
{
	t_malloc	*n;

	n = malloc(sizeof(t_malloc));
	return (n->data = data, n->next = NULL, n);
}

void	addfront(t_malloc **head, t_malloc *new)
{
	if (*head)
		new->next = *head;
	*head = new;
}

void	listclear(t_malloc **head)
{
	t_malloc	*tmp;
	t_malloc	*ptr;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		ptr = tmp;
		tmp = tmp->next;
		if (ptr->data)
			free(ptr->data);
		free(ptr);
	}
	*head = NULL;
}
