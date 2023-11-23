/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:48:47 by asabri            #+#    #+#             */
/*   Updated: 2023/11/23 13:56:55 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_data1	*newmalloc2(void *data)
{
	t_data1	*n;

	n = malloc(sizeof(t_data1));
	return (n->data = data, n->next = NULL, n);
}

void	*ft_malloc2(size_t size, int mode)
{
	static t_data1	*head;
	void			*data;

	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return (exit(1), data);
		addfront2(&head, newmalloc2(data));
		return (data);
	}
	if (!mode)
		return (listclear2(&head), exit(0), NULL);
	return (NULL);
}

void	*ft_malloc(size_t size, int mode)
{
	static t_malloc	*head;
	void			*data;

	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return (exit(1), NULL);
		addfront(&head, newmalloc(data));
		return (data);
	}
	if (!mode)
		return (listclear(&head), exit(1), NULL);
	if (mode == 2)
		return (listclear(&head), exit(0), NULL);
	return (NULL);
}
