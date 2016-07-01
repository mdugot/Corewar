/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_instru.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 13:38:36 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/31 08:40:58 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int			verif_instru(char *str)
{
	static const char	in[16][6] = {"lfork", "sti", "fork", "lld", "ld", "add",
		"zjmp", "sub", "ldi", "or", "st", "aff", "live", "xor", "lldi", "and"};
	int					i;
	int					ok;

	i = -1;
	ok = 0;
	while (++i < 16)
		if (!ft_strcmp(in[i], str))
			ok = 1;
	return (ok);
}

static void	clean_space2(char *str, int *y)
{
	int	i;

	i = *y;
	while (str[++i] && (str[i] == ' '
		|| str[i] == '	' || str[i] == SEPARATOR_CHAR))
		if (str[i] == SEPARATOR_CHAR)
			error_exit(ft_strjoin("Syntax Error, Bad separator on line:"
				, ft_itoa(lin(1))), EINVAL);
		else
			str[i] = SEPARATOR_CHAR;
	*y = i;
}

void		clean_space(char *str)
{
	int	i;
	int	y;

	y = -1;
	while (str[++y])
		if (str[y] == SEPARATOR_CHAR)
		{
			i = y;
			while (--i >= 0 && (str[i] == ' '
				|| str[i] == '	' || str[i] == SEPARATOR_CHAR))
				if (str[i] == SEPARATOR_CHAR)
					error_exit(ft_strjoin("Syntax Error, Bad separator on line:"
						, ft_itoa(lin(1))), EINVAL);
				else
					str[i] = SEPARATOR_CHAR;
			clean_space2(str, &y);
			if (!str[i])
				error_exit(ft_strjoin("Syntax Error, Bad separator on line:"
					, ft_itoa(lin(1))), EINVAL);
		}
}
