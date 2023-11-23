/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:49:58 by asabri            #+#    #+#             */
/*   Updated: 2023/11/23 17:11:12 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>

typedef struct s_malloc
{
	void			*data;
	struct s_malloc	*next;

}t_malloc;
typedef struct s_data1
{
	void			*data;
	struct s_data1	*next;

}t_data1;

t_malloc	*newmalloc(void *data);
t_data1		*newmalloc2(void *data);
void		addfront(t_malloc **head, t_malloc *new);
void		listclear(t_malloc **head);
void		*ft_malloc(size_t size, int mode);
void		*ft_malloc2(size_t size, int mode);
void		listclear2(t_data1 **head);
void		addfront2(t_data1 **head, t_data1 *new);
#endif
