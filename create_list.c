/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmns_solver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:21:54 by elindber          #+#    #+#             */
/*   Updated: 2019/12/10 18:15:48 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_fillit.h"

static void	set_xy_alpha(char *tmns, int i, t_tetri **list)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (!(ft_isalpha(tmns[i])))
	{
		if (tmns[i] == '\n')
		{
			x = -1;
			y++;
		}
		x++;
		i++;
	}
	(*list)->x = x;
	(*list)->y = y;
	(*list)->alpha = tmns[i];
}

static void	set_relative_xy(t_tetri **list)
{
	int		x;
	int		y;
	int		count;
	int		r_xy;

	x = (*list)->x + 1;
	y = (*list)->y;
	count = 0;
	r_xy = 0;
	while (count < 3)
	{
		if (ft_isalpha((*list)->block[y][x]))
		{
			(*list)->rltv[count][r_xy] = y - (*list)->y;
			r_xy++;
			(*list)->rltv[count][r_xy] = x - (*list)->x;
		//	printf("%d %s", count, "Relatives are: ");
		//	printf("%d ", (*list)->rltv[count][0]);
		//	printf("%d\n", (*list)->rltv[count][1]);
			r_xy = 0;
			count++;
		}
		x++;
		if ((*list)->block[y][x] == '\0')
		{
			y++;
			x = 0;
		}
	}
}

int			create_list(char *tmns, int i, t_tetri **list)
{
	int			line;

	if (tmns[i] == '\0')
		return (0);
	*list = malloc(sizeof(t_tetri));
	(*list)->block = (char**)malloc(sizeof(char*) * 5);
	line = 0;
	while (line < 4)
	{
		(*list)->block[line] = ft_strsub(tmns, i, 4);
		i = i + 5;
	//	printf("%s\n", (*list)->block[line]);
		line++;
	}
	(*list)->block[line] = NULL;
	i++;
	set_xy_alpha(tmns, i - 21, list);
	set_relative_xy(list);
//	printf("%d%s", (*list)->x, ":");
//	printf("%d\n", (*list)->y);
//	printf("%c\n\n", (*list)->alpha);
//	printf("\n");
	create_list(tmns, i, &(*list)->next);
	return (0);
}
