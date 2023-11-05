/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 00:46:56 by abberkac          #+#    #+#             */
/*   Updated: 2023/10/24 01:54:12 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_map	*ft_new_lst(char *line, t_type type)
{
	t_map	*node;

	node = (t_map *)malloc(sizeof(t_map));
	if (node)
	{
        node->line = line;
        node->type = type;
		node->next = NULL;
	}
	return (node);
}

void	ft_add_data(t_map **head, char *line, t_type type)
{
	t_map	*new;
	t_map	*current;

	new = ft_new_lst(line, type);
	if (*head == NULL)
		*head = new;
    else
	{
		current = *head;
		while (current && current->next)
			current = current->next;
		current->next = new;
	}
	return ;
}

void	ft_delone(t_map *lst)
{
	if (lst)
		free(lst);
	else
		return ;
}

void	ft_clear_lst(t_map **lst)
{
	t_map	*tmp;

	if (!lst || !(*lst))
		return ;
	while (lst && (*lst))
	{
		tmp = (*lst)->next;
		ft_delone((*lst));
		(*lst) = tmp;
	}
	free(*lst);
	lst = NULL;
}