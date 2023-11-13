/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:43:51 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/14 00:32:39 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int condition(char c)
{
    if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
        return(0);
    if ( c == '0' || c == '1' || c == ' ')
        return (0);
    return (1);
}

int check_first_last_walls(t_data **data)
{
    int i;
    int last;
    t_data *crr;
    
    i = 0;
    last = 0;
    crr = *data;
    while (crr->map[0][i])
    {
        if (!is_space(crr->map[0][i]) && crr->map[0][i] != '1')
            return (1);
        i++;
    }
    i = 0;
    while (crr->map[i])
        i++;
    last = i - 1;
    i = 0;
    while (crr->map[last][i])
    {
        if (!is_space(crr->map[last][i]) && crr->map[last][i] != '1')
            return (1);
        i++;
    }
    return (0);
}

int check_walls(t_data **data)
{
    int i = 0;
    int j;

    if (check_first_last_walls(data))
        return (1);
    while ((*data)->map[i])
    {
        j = 0;
        while (is_space((*data)->map[i][j]))
            j++;
        if ((*data)->map[i][j] != '1'|| \
            ((*data)->map[i][ft_strlen((*data)->map[i]) - 1] != '1'))
            return (1);
        i++;
    }
    return (0);
}

int check_valid_chars(t_data **data)
{
    int i;
    int j;
    int count;

    if (check_walls(data))
        return (1);
    (i = 0, count = 0);
    while ((*data)->map[i])
    {
        j = 0;
        while ((*data)->map[i][j])
        {
            if (condition((*data)->map[i][j]))
                return (1);
            if ((*data)->map[i][j] == 'N' || (*data)->map[i][j] == 'E' \
                || (*data)->map[i][j] == 'W' || (*data)->map[i][j] == 'S')
			{
				(*data)->plyr = (*data)->map[i][j];
                count++;
			}
            j++;
        }
        i++;
    }  
    if (count != 1)
        return (1);
    return (0);
}

int check_wall_around_chars(t_data **data)
{
    int i;
    int j;

    i = 0;
	while ((*data)->map[i])
	{
		j = 0;
		while ((*data)->map[i][j])
		{
			if ((*data)->map[i][j] == '0' || (*data)->map[i][j] == (*data)->plyr)
			{
				if ((*data)->map[i][j] == '0')
				{
					if ((*data)->map[i][j + 1] != '1' && (*data)->map[i][j + 1] != '0' \
                        && (*data)->map[i][j + 1] != (*data)->plyr)
                        return (1);
					if ((*data)->map[i][j - 1] != '1' && (*data)->map[i][j - 1] != '0' \
                        && (*data)->map[i][j - 1] != (*data)->plyr)
                        return (1);
					if ((*data)->map[i + 1][j] != '1' && (*data)->map[i + 1][j] != '0' \
                        && (*data)->map[i + 1][j] != (*data)->plyr)
                        return (1);
					if ((*data)->map[i - 1][j] != '1' && (*data)->map[i - 1][j] != '0' \
                        && (*data)->map[i - 1][j] != (*data)->plyr)
                        return (1);
                }
				else if ((*data)->map[i][j] == (*data)->plyr)
				{
					if ((*data)->map[i][j + 1] != '1' && (*data)->map[i][j + 1] != '0')
                        return (1);
					if ((*data)->map[i][j - 1] != '1' && (*data)->map[i][j - 1] != '0')
                        return (1);
					if ((*data)->map[i + 1][j] != '1' && (*data)->map[i + 1][j] != '0')
                        return (1);
					if ((*data)->map[i - 1][j] != '1' && (*data)->map[i - 1][j] != '0')
                        return (1);
				}
			}
            j++;
		}
		i++;
	}
	return (0);
}

int check_map_valid(t_data **data)
{
    if (check_valid_chars(data))
        return (1);
    if (check_wall_around_chars(data))
    {
        return (1);
    }
    return (0);
}