/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 18:48:00 by elindber          #+#    #+#             */
/*   Updated: 2019/12/10 17:56:53 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_fillit.h"

static void	free_map(t_map *map)
{
	int	y;

	y = 0;
	while (map->dots[y])
	{
		y++;
	}
	while (y != -1)
	{
		ft_strdel(&map->dots[y]);
		y--;
	}
	free(map->dots);
	map->dots = NULL;
}

int		map_size(int size)
{
	int		count;

	count = 2;
	while (count * count < size)
		count++;
	return (count);
}

int			create_map(t_tetri *list, int size)
{
	int		y;
	t_map	*map;

	y = 0;
	if (!(map = malloc(sizeof(t_map))))
		return (-1);
	if (!(map->dots = (char**)malloc(sizeof(char*) * (size + 1))))
		return (-1);
	map->size = size;
	while (y < size)
	{
		map->dots[y] = ft_memset(ft_strnew(size), '.', size);
	//	printf("%s\n", map->dots[y]);
		y++;
	}
	map->dots[y] = NULL;
//	printf("\n");
	if(!place_tmns(list, map))
	{
		free_map(map);
		create_map(list, size + 1);
	}
	return (0);
}

int	count_nodes(t_tetri *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}
