/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 10:07:24 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/27 09:04:27 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		lin(int i)
{
	static	int	line = 0;

	line += i;
	return (line);
}

void	error_exit(char *str, int err)
{
	int	errno;

	errno = err;
	perror(str);
	exit(0);
}
