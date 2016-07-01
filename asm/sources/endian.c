/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 10:15:55 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/17 15:45:35 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	endian(void *mem, int size)
{
	char	c;
	char	*str;
	int		compt;

	str = mem;
	compt = size;
	while (--compt >= (size / 2))
	{
		c = str[(size - 1) - compt];
		str[(size - 1) - compt] = str[compt];
		str[compt] = c;
	}
}
