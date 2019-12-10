/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_tmns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:40:24 by elindber          #+#    #+#             */
/*   Updated: 2019/12/10 18:12:15 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_fillit.h"

static void	place_piece(t_tetri *list, t_map *map, int y, int x)
{
	int		c;

	c = 0;
	map->dots[y][x] = list->alpha;
	while (c < 3)
	{
		map->dots[y + list->rltv[c][0]][x + list->rltv[c][1]] = list->alpha;
		c++;
	}
}

static void	print_map(t_map *map, int y)
{
	while (map->dots[y] != NULL)
	{
		ft_putstr(map->dots[y]);
		ft_putchar('\n');
		y++;
	}
}

static void	remove_piece(t_map *map, char abc)
{
	int		y;
	int		x;

	y = 0;
	while (map->dots[y])
	{
		x = 0;
		while (map->dots[y][x])
		{
			if (map->dots[y][x] == abc)
				map->dots[y][x] = '.';
			x++;
		}
		y++;
	}
}

static int 	check_fit(t_tetri *list, t_map *map, int y, int x)
{
	int		c;
	int		r;

	c = 0;
	r = 0;
	if (map->dots[y][x] != '.')
		return (0);
	while (c < 3)
	{
		if (list->rltv[c][0] + y >= map->size ||
			list->rltv[c][1] + x > map->size || list->rltv[c][1] + x < 0)
			break ;
		if (map->dots[list->rltv[c][0] + y][list->rltv[c][1] + x] == '.')
			r++;
		c++;
	}
	return (r == 3);
}

int		place_tmns(t_tetri *list, t_map *map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (list == NULL)
	{
		print_map(map, 0);
		return (1);
	}
	while (map->dots[y])
	{
		if (check_fit(list, map, y, x))
		{
			place_piece(list, map, y, x);
			if (place_tmns(list->next, map))
				return (1);
			remove_piece(map, list->alpha);
		}
		x++;
		if (map->dots[y][x] == '\0')
		{
			y++;
			x = 0;
		}
		if (map->dots[y] == NULL)
			return (0);
	}
	return (0);
}
