/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 11:10:38 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/31 08:49:49 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void		nasm(char *file)
{
	int			fd;
	int			new;
	t_header	en;
	char		*byte_code;

	if ((fd = open(file, O_RDONLY)) == -1)
		error_exit("File doesn't exist or can't be open", EINVAL);
	if (read(fd, &en, sizeof(t_header)) != sizeof(t_header))
		error_exit("Bad file", EINVAL);
	endian(&(en.magic), sizeof(en.magic));
	endian(&(en.prog_size), sizeof(en.prog_size));
	byte_code = ft_strnew(en.prog_size);
	if (read(fd, byte_code, en.prog_size) != en.prog_size)
		error_exit("Bad file", EINVAL);
	new = open(ft_strjoin(ft_strsub(file, 0, ft_strlen(file) - 4), ".s"),
			O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	ft_putstr_fd(".name \"", new);
	ft_putstr_fd(en.prog_name, new);
	ft_putstr_fd("\"\n", new);
	ft_putstr_fd(".comment \"", new);
	ft_putstr_fd(en.comment, new);
	ft_putstr_fd("\"\n", new);
	cest_parti(byte_code, en, new);
	close(fd);
}

static void	com(char *line, t_header *ent, int *nc)
{
	if (nc[1] >= 1)
		error_exit("To much comment", EINVAL);
	if (((ft_strrchr(line, '"') - line) + 1) != (long)ft_strlen(line)
		|| (ft_strlen(ft_strsub(line, ft_strchr(line, '"') - line + 1,
				((ft_strrchr(line, '"') - line) - (ft_strchr(line, '"')
					- line) - 1))) > COMMENT_LENGTH))
		error_exit("Champion comment too long", EINVAL);
	nc[1]++;
	ft_strcpy(ent->comment,
			ft_strsub(line, ft_strchr(line, '"') - line + 1,
				((ft_strrchr(line, '"') - line)
				- (ft_strchr(line, '"') - line) - 1)));
}

void		name_comment(char *line, t_header *ent)
{
	static int	nc[2] = {0, 0};

	if (ft_strstr(line, ".name"))
	{
		if (((ft_strrchr(line, '"') - line) + 1) != (long)ft_strlen(line)
			|| (ft_strlen(ft_strsub(line, ft_strchr(line, '"') - line + 1,
					((ft_strrchr(line, '"') - line) - (ft_strchr(line, '"')
						- line) - 1))) > PROG_NAME_LENGTH))
			error_exit("Champion name too long", EINVAL);
		if (nc[0] >= 1)
			error_exit("To much name", EINVAL);
		nc[0]++;
		ft_strcpy(ent->prog_name,
				ft_strsub(line, ft_strchr(line, '"') - line + 1,
					((ft_strrchr(line, '"') - line)
					- (ft_strchr(line, '"') - line) - 1)));
	}
	else if (ft_strstr(line, ".comment"))
		com(line, ent, nc);
}

int			header(int fd, t_header *ent)
{
	char	*line;

	ent->magic = COREWAR_EXEC_MAGIC;
	endian(&(ent->magic), sizeof(unsigned int));
	line = NULL;
	while (void_str(line))
		if (get_next_line(fd, &line) <= 0 && lin(1))
			error_exit("Bad file", EINVAL);
	line = ft_strtrim(line);
	if (!ft_strncmp(line, ".name", 5) && !ft_strncmp(line, ".comment", 8))
		error_exit("Bad name/comment", EINVAL);
	name_comment(line, ent);
	get_next_line(fd, &line);
	lin(1);
	while (void_str(line))
	{
		get_next_line(fd, &line);
		lin(1);
	}
	line = ft_strtrim(line);
	if (!ft_strstr(line, ".name") && !ft_strstr(line, ".comment"))
		error_exit("Bad name/comment", EINVAL);
	name_comment(line, ent);
	return (1);
}

int			main(int argc, char **argv)
{
	int			fd;
	t_header	entete;
	t_instruct	*ins;

	if (argc <= 1 || argc >= 4)
		ft_putstr("usage : asm [file.s]\n        asm [[-n] file.cor]\n");
	else if (argc == 3 && verif_nasm(argv))
		nasm((!ft_strcmp(argv[1], "-n")) ? argv[2] : argv[1]);
	else
	{
		fd = -1;
		if (argc != 2 || argv[1][ft_strlen(argv[1]) - 2] != '.'
				|| argv[1][ft_strlen(argv[1]) - 1] != 's'
				|| (fd = open(argv[1], O_RDONLY)) == -1)
			error_exit("Wrong file", EINVAL);
		ft_bzero(entete.prog_name, PROG_NAME_LENGTH + 4);
		ft_bzero(entete.comment, COMMENT_LENGTH + 4);
		header(fd, &entete);
		ins = read_instruct(fd);
		entete.prog_size = convert(ins);
		endian(&(entete.prog_size), sizeof(entete.prog_size));
		close(fd);
		write_all(ins, entete, argv[1]);
	}
	return (1);
}
