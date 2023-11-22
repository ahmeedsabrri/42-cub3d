/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:48:47 by asabri            #+#    #+#             */
/*   Updated: 2023/11/22 16:54:41 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_malloc(size_t size, int mode)
{
	static t_malloc	*head;
	void			*data;

	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return (ft_malloc(0, 0));
		addfront(&head, newmalloc(data));
		return (data);
	}
	if (!mode)
		return (listclear(&head), exit(1), NULL);
	if (mode == 2)
		return (listclear(&head), exit(0), NULL);
	return (NULL);
}
