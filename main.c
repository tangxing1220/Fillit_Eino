/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:00:32 by elindber          #+#    #+#             */
/*   Updated: 2019/12/10 17:57:21 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_fillit.h"

int		main(int ac, char **av)
{
	int		fd;
	int		ret;
	t_tetri	*list;

	if (ac <= 1 || ac > 2)
	{
		if (ac <= 1)
			ft_putstr("Too few parameters. Usage-thing here.\n");
		if (ac > 2)
			ft_putstr("Too many parameters. Usage-thing here.\n");
		return (-1);
	}
	if (!(fd = open(av[1], O_RDONLY)))
	{
		ft_putstr_fd("open error", 2);
		return (-1);
	}

	if ((ret = validate_file(fd, &av[1], &list)) < 0)
	{
		ft_putstr("error\n");
		return (-1);
	}
	create_map(list, map_size(count_nodes(list) * 4));
	printf("\nMain function completed\n");
//	while (1);
	return (0);
}
