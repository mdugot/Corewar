/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:09:10 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/02 19:18:29 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "vm.h"

void		wrong_format(char *file)
{
	ft_printf_fd(2, "Wrong format : %s\n", file);
	exit(1);
}

void		verify_header(int fd, char *file)
{
	char			buff[4];
	unsigned int	*n;

	if (read(fd, buff, 4) != 4)
		wrong_format(file);
	convert_endian(buff, 4);
	n = (unsigned int*)buff;
	if (*n != COREWAR_EXEC_MAGIC)
		wrong_format(file);
}

void		add_numero_in_r1(t_champion *ch)
{
	int		i;
	char	*tmp;
	int		n;

	i = 0;
	n = ch->numero;
	tmp = (char*)&n;
	while (i < REG_SIZE && i < 4)
	{
		ch->registre[0][i] = tmp[i];
		i++;
	}
}

void		read_cor_file(int fd, t_champion *champion, char *file, int o)
{
	char		buff[4];
	t_vm		*vm;
	UI			*tmp;

	vm = champion->vm;
	if (read(fd, vm->player[o].name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		wrong_format(file);
	if (read(fd, buff, 4) != 4)
		wrong_format(file);
	if (read(fd, buff, 4) != 4)
		wrong_format(file);
	convert_endian(buff, 4);
	tmp = (UI*)buff;
	vm->player[o].size = *tmp;
	if (vm->player[o].size > CHAMP_MAX_SIZE)
		wrong_format(file);
	if (read(fd, vm->player[o].comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		wrong_format(file);
	if (read(fd, buff, 4) != 4)
		wrong_format(file);
	if (read(fd, P[o].memory, P[o].size) != P[o].size)
		wrong_format(file);
}

t_champion	*read_champion(char *file, int n, t_vm *vm, int o)
{
	int			fd;
	t_champion	*champion;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "Can't open file %s\n", file);
		exit(1);
	}
	verify_header(fd, file);
	champion = ft_memalloc(sizeof(t_champion));
	champion->vm = vm;
	read_cor_file(fd, champion, file, o);
	champion->numero = n;
	vm->player[o].id = n;
	vm->player[o].dead = 0;
	add_numero_in_r1(champion);
	return (champion);
}
