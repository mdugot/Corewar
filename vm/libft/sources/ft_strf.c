/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:43:56 by mdugot            #+#    #+#             */
/*   Updated: 2016/04/01 17:43:27 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

char	*do_strf(int fd)
{
	char	*result;
	char	*tmp;
	char	buff[1001];
	int		r;

	result = ft_strdup("");
	while ((r = read(fd, buff, 1000)) > 0)
	{
		buff[r] = 0;
		tmp = ft_strjoin(result, buff);
		ft_strdel(&result);
		result = tmp;
	}
	return (result);
}

char	*ft_strf(const char *restrict format, ...)
{
	va_list ap;
	int		pip[2];
	int		child;
	char	*result;

	va_start(ap, format);
	pipe(pip);
	child = fork();
	if (child == 0)
	{
		close(pip[0]);
		do_printf_fd(pip[1], (char *)format, &ap);
		close(pip[1]);
		exit(0);
		return (NULL);
	}
	else
	{
		close(pip[1]);
		result = do_strf(pip[0]);
		close(pip[0]);
		return (result);
	}
}
