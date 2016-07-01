/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:52:31 by cdrouet           #+#    #+#             */
/*   Updated: 2016/06/06 10:30:17 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	direct(char *b, int fd, int *i, int *inc)
{
	int		k;
	short	de;
	int		katr;

	k = dir_size(b[(*i)]);
	ft_memcpy(((k == 2) ? (int*)&de : &katr),
			&b[(*i) + (*inc) + 2], k);
	endian(((k == 2) ? (void*)&de : (void*)&katr), k);
	ft_putchar_fd(DIRECT_CHAR, fd);
	ft_putstr_fd(ft_itoa((k == 2) ? (int)de : katr), fd);
	(*inc) += k;
}

static void	indirect(char *b, int fd, int *i, int *inc)
{
	short	de;

	ft_memcpy(&de, &b[(*i) + (*inc) + 2], 2);
	endian(&de, 2);
	ft_putstr_fd(ft_itoa((int)de), fd);
	(*inc) += 2;
}

static void	registre(char *b, int fd, int *i, int *inc)
{
	ft_putchar_fd('r', fd);
	ft_putstr_fd(ft_itoa((int)b[(*i) + (*inc) + 2]), fd);
	(*inc)++;
}

static void	ocp_ok(char *b, int fd, int *i)
{
	int		j;
	int		inc;

	j = 6;
	inc = 0;
	while (j >= 0)
	{
		if (j != 6 && ((b[(*i) + 1] >> j) & 0b00000011) != 0)
			ft_putchar_fd(SEPARATOR_CHAR, fd);
		if (((b[(*i) + 1] >> j) & 0b00000011) == DIR_CODE)
			direct(b, fd, i, &inc);
		else if (((b[(*i) + 1] >> j) & 0b00000011) == IND_CODE)
			indirect(b, fd, i, &inc);
		else if (((b[(*i) + 1] >> j) & 0b00000011) == REG_CODE)
			registre(b, fd, i, &inc);
		else
		{
			(*i) += inc;
			(*i) += 2;
			ft_putchar_fd('\n', fd);
			break ;
		}
		j -= 2;
	}
}

void		cest_parti(char *b, t_header en, int fd)
{
	int		i;
	int		k;
	short	de;
	int		katr;

	i = 0;
	while ((unsigned int)i < en.prog_size)
	{
		ft_putstr_fd(instru(b[i]), fd);
		ft_putchar_fd(' ', fd);
		if (octet_codage(b[i]))
			ocp_ok(b, fd, &i);
		else
		{
			k = dir_size(b[i]);
			ft_memcpy(((k == 2) ? (int*)&de : &katr),
					&b[i + 1], k);
			endian(((k == 2) ? (void*)&de : (void*)&katr), k);
			ft_putchar_fd(DIRECT_CHAR, fd);
			ft_putstr_fd(ft_itoa((k == 2) ? (int)de : katr), fd);
			ft_putchar_fd('\n', fd);
			i += k;
			i++;
		}
	}
}
