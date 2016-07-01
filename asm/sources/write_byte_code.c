/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_byte_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 10:05:19 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/24 10:23:03 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		void_str(char *str)
{
	int		i;

	if (!str)
		return (1);
	replace_comment(str);
	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '	' && str[i] != '\n')
			return (0);
	return (1);
}

void	write_all(t_instruct *ins, t_header entete, char *name)
{
	int	fd;

	name[ft_strlen(name) - 1] = '\0';
	name = ft_strjoin(name, "cor");
	fd = open(name, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	write(fd, &entete, sizeof(entete));
	while (ins)
	{
		if (ins->name)
		{
			write(fd, &(ins->opc), 1);
			if (ins->ocp)
				write(fd, &(ins->ocp), 1);
			write(fd, ins->byte_param, ins->byte_len);
		}
		ins = ins->next;
	}
	close(fd);
}
