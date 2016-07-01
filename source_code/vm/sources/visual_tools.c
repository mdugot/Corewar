/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 15:40:46 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/02 19:19:39 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_middle_value(WINDOW *win, char *str, int value, int *line)
{
	int		w;
	int		h;
	int		size;
	int		tmp;

	size = 0;
	tmp = ABS(value);
	while (tmp)
	{
		size++;
		tmp /= 10;
	}
	if (value < 0)
		size++;
	getmaxyx(win, h, w);
	wattron(win, A_BOLD);
	mvwprintw(win, *line, w / 2 - ft_strlen(str) / 2, str);
	wattroff(win, A_BOLD);
	mvwprintw(win, *line + 1, w / 2 - size / 2, "%d", value);
	*line += 3;
}

void	print_middle_str(WINDOW *win, char *str, char *value, int *line)
{
	int		w;
	int		h;
	int		len;

	getmaxyx(win, h, w);
	wattron(win, A_BOLD);
	mvwprintw(win, *line, w / 2 - ft_strlen(str) / 2, str);
	wattroff(win, A_BOLD);
	len = ft_strlen(value);
	len = (len > 20 ? 20 : len);
	mvwprintw(win, *line + 1, w / 2 - len / 2, "%.20s", value);
	*line += 3;
}

void	print_middle_simple(WINDOW *win, char *str, int flags, int *line)
{
	int		w;
	int		h;

	getmaxyx(win, h, w);
	wattron(win, flags);
	mvwprintw(win, *line, w / 2 - ft_strlen(str) / 2, str);
	wattroff(win, flags);
	*line += 1;
}

void	print_header(WINDOW *win, char *h1, char *h2, int *line)
{
	int		w;
	int		h;
	char	*str;

	str = ft_strjoin(h1, h2);
	getmaxyx(win, h, w);
	mvwprintw(win, *line, w / 2 - ft_strlen(str) / 2, str);
	*line += 1;
	ft_strdel(&str);
}

void	print_middle_hexa(WINDOW *win, unsigned int value, int flags, int *line)
{
	int		w;
	int		h;

	getmaxyx(win, h, w);
	wattron(win, flags);
	mvwprintw(win, *line, w / 2 - 5, "%#010x", value);
	wattroff(win, flags);
	*line += 1;
}
