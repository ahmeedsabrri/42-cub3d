/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:49:40 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/11 06:35:07 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    free_struct_infos(t_infos **infos)
{
    if (!*infos)
        return ;
    free((*infos)->ceiling);
    free((*infos)->floor);
    free((*infos)->north);
    free((*infos)->south);
    free((*infos)->east);
    free((*infos)->west);
    free(*infos);
}

int store_valid_infos(char **str)
{
    char *tmp;

    while (*str && !is_space(**str))
        (*str)++;
    while (*str && is_space(**str))
        (*str)++;
    if (**str == '\n')
        return (1);
    tmp = strdup(*str);
    if (tmp == NULL)
        return (1);
    *str = tmp;
    return (0);
}

int extract_rgb_floor(t_floor **floor, char *color)
{
    int i = 0;
    int idx = 0;
    int c = 0;
    int count = 0;
    char *tmp;

    while (color[i])
    {
        if (ft_isdigit(color[i]))
            count++;
        else if (color[i] == ',' || color[i] == '\n')
        {
            if (count > 3 || !count || c > 2)
                return (1);
            tmp = ft_strndup(color + idx, i);
            if (c == 0)
                (*floor)->r = ft_atoi(tmp);
            else if (c == 1)
                (*floor)->g = ft_atoi(tmp);
            else if (c == 2)
                (*floor)->b = ft_atoi(tmp);
            if ((*floor)->r < 0 || (*floor)->g < 0 || (*floor)->b < 0)
                return (1);
            (free(tmp), count = 0, idx = i + 1);
            c++;
        }
        i++;
    }
    return (0);
}

int extract_rgb_ceiling(t_ceiling **ceiling, char *color)
{
    int i;
    int idx;
    int c;
    int count;
    char *tmp;

    (i = 0, idx = 0, c = 0, count = 0);
    while (color[i])
    {
        if (ft_isdigit(color[i]))
            count++;
        else if (color[i] == ',' || color[i] == '\n')
        {
            if (count > 3 || !count || c > 2)
                return (1);
            tmp = ft_strndup(color + idx, i);
            if (c == 0)
                (*ceiling)->r = ft_atoi(tmp);
            else if (c == 1)
                (*ceiling)->g = ft_atoi(tmp);
            else if (c == 2)
                (*ceiling)->b = ft_atoi(tmp);
            if ((*ceiling)->r < 0 || (*ceiling)->g < 0 || (*ceiling)->b < 0)
                return (1);
            (free(tmp), count = 0, idx = i + 1);
            c++;
        }
        i++;
    }
    return (0);
}

int check_colors_valid(char *color)
{
    int i;
    int comma;

    (i = 0, comma = 0);
    while (color[i])
    {
        if (!ft_isdigit(color[i]) && color[i] != ',' \
            && color[i] != '\n' && !is_space(color[i]))
            return (1);
        if (color[i] == ',')
            comma++;
        i++;
    }
    if (comma != 2)
        return (1);
    return (0);
}

int fill_rgb_colors(t_floor **floor, t_ceiling **ceiling, char *fl, char *cl)
{
    *floor = malloc(sizeof(t_floor));
    if (!*floor)
        return (1);
    ((*floor)->r = 0, (*floor)->g = 0, (*floor)->b = 0);
    if (extract_rgb_floor(floor, fl))
        return (1);
    *ceiling = malloc(sizeof(t_ceiling));
    if (!*ceiling)
        return (1);
    ((*ceiling)->r = 0, (*ceiling)->g = 0, (*ceiling)->b = 0);
    if (extract_rgb_ceiling(ceiling, cl))
        return (1);
    return (0);
}

int	check_infos(t_infos **infos)
{
    t_floor *floor;
    t_ceiling *ceiling;
	
    (floor = NULL, ceiling = NULL);
    if (store_valid_infos(&(*infos)->north) || store_valid_infos(&(*infos)->south) \
        || store_valid_infos(&(*infos)->east) || store_valid_infos(&(*infos)->west) \
        || store_valid_infos(&(*infos)->floor) || store_valid_infos(&(*infos)->ceiling) \
        || check_colors_valid((*infos)->floor) || check_colors_valid((*infos)->ceiling))
        return (free_struct_infos(infos), 1);
    if (fill_rgb_colors(&floor, &ceiling, (*infos)->floor, (*infos)->ceiling))
        return (1);
    return (0);
}
