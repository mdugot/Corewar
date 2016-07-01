/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 10:52:18 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/31 08:47:06 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10
# define T_REG					1
# define T_DIR					4
# define T_IND					2
# define T_LAB					8
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

typedef struct					s_instruct
{
	char						*name;
	char						*label;
	int							index;
	char						**param;
	unsigned char				ocp;
	unsigned char				opc;
	char						*byte_param;
	int							byte_len;
	int							line;
	struct s_instruct			*next;
	struct s_instruct			*previous;
}								t_instruct;

int								lin(int i);
void							nasm(char *str);
void							cest_parti(char *b, t_header en, int fd);
char							*instru(char opc);
int								octet_codage(char opc);
int								dir_size(char opc);
int								nb_param(char opc);
int								*arg_val(char opc);
void							convert_param(t_instruct *ins,
									t_instruct *start);
void							convert_all(t_instruct *ins, t_instruct *start);
int								convert(t_instruct *ins);
int								search_i_lab(t_instruct *ins, char *lab);
void							write_all(t_instruct *ins, t_header entete,
									char *name);
int								is_some(char opc, int i, t_instruct *a,
									t_instruct *ins);
int								is_dir(t_instruct *ok,
									char *str, t_instruct *ins);
int								is_reg(char *str);
int								is_ind(char *str, t_instruct *ins);
int								tab_instru(char *str);
int								is_lab(char *str);
void							replace_comment(char *str);
int								check_label(char **lab, char *line);
int								check_instruction(char ***param,
									char **instru, char *line, int label);
void							clean_space(char *str);
void							error_exit(char *str, int err);
void							add_end_lst(t_instruct **lst, t_instruct *new);
int								ft_pstrlen(char **pstr);
int								verif_instru(char *str);
int								verif_label(char *label);
int								verif_nasm(char **argv);
int								void_str(char *str);
void							replace_c(char *str, char c, char r);
t_instruct						*new_instruct(int li, t_instruct **lst,
									char *all, int fd);
void							endian(void *mem, int size);
void							name_comment(char *line, t_header *ent);
int								header(int fd, t_header *ent);
t_instruct						*read_instruct(int fd);

#endif
