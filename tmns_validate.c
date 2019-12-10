/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmns_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:27:37 by elindber          #+#    #+#             */
/*   Updated: 2019/12/10 17:57:34 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_fillit.h"

static int		validate_4x4_chars(char *tmns)
{
	int		i;
	int		a;
	int		start;

	i = 0;
	a = 0;
	start = 0;
	while (tmns[i])
	{
		if (tmns[i] == '\n' && tmns[i - 1] == '\n')
		{
			i++;
			start = i;
		}
		if (tmns[i] == '\n' && (tmns[i + 1] == '\n' || tmns[i + 1] == '\0')
			&& (i - a != 4 || i - start != 19))
			return (-1);
		if ((tmns[i] == '\n' && i - a != 4) || (tmns[i] != '\n' &&
			tmns[i] != '#' && tmns[i] != '.'))
			return (-1);
		if (tmns[i - 1] == '\n' && tmns[i] != '\n')
			a = i;
		i++;
	}
	printf("Lines and chars passed\n");
	return (0);
}

static int		validate_pieces(char *tmns, int i, int x, int conn)
{
	while (tmns[i])
	{
		if (tmns[i] == '#' && tmns[i + 1] == '#')
			conn++;
		if (tmns[i] == '#' && tmns[i - 1] == '#')
			conn++;
		if (tmns[i] == '#' && i - x > 4 && i - x < 15 && tmns[i + 5] == '#')
			conn++;
		if (tmns[i] == '#' && i - x > 4 && i - x < 15 && tmns[i - 5] == '#')
			conn++;
		if ((tmns[i] == '#' && i - x > 14 && tmns[i - 5] == '#') ||
			(tmns[i] == '#' && i - x < 5 && tmns[i + 5] == '#'))
			conn++;
		if (tmns[i] == '\n' && (tmns[i + 1] == '\n' || tmns[i + 1] == '\0')
			&& conn != 6 && conn != 8)
			return (-1);
		if (tmns[i] == '\n' && tmns[i - 1] == '\n')
			x = i + 1;
		if (tmns[i] == '\n' && tmns[i - 1] == '\n')
			conn = 0;
		i++;
	}
	return (0);
}

static int		validate_shape(char *tmns)
{
	char	abc;
	int		hash;
	int		i;

	abc = 'A';
	hash = 0;
	i = 0;
	if (validate_pieces(tmns, 0, 0, 0) < 0)
		return (-1);
	while (tmns[i])
	{
		if (tmns[i] == '#')
			hash++;
		if (tmns[i] == '#')
			tmns[i] = abc;
		if (tmns[i] == '\n' && (tmns[i + 1] == '\n' || tmns[i + 1] == '\0')
			&& hash != 4)
			return (-1);
		if (tmns[i] == '\n' && tmns[i - 1] == '\n')
		{
			abc++;
			hash = 0;
		}
		i++;
	}
	printf("Shape valdiation passed\n");
	return (0);
}

int				validate_file(int fd, char **av, t_tetri **list)
{
	char		*file[MAX_FD];
	char		buff[BUFF_SIZE + 1];
	int			count;
	int			i;

	count = 0;
	i = -1;
	if (read(fd, buff, BUFF_SIZE) < 0)
		return (-1);
	file[fd] = buff;
	if ((validate_4x4_chars(file[fd]) < 0) || (validate_shape(file[fd]) < 0))
		return (-1);
	while (file[fd][++i])
		if (file[fd][i] == '\n')
			count++;
	if ((count < 4 || count > 129) || (count + 1) % 5 != 0)
		return (-1);
	printf("Tetrimino count passed\n\n");
	create_list(file[fd], 0, list);
	return (0);
}
