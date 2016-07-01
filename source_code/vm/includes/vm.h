/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 13:30:16 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/05 17:46:10 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdlib.h>
# include <ncurses.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# define UI unsigned int

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
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
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define PLAYER	struct s_player
# define P vm->player
# define CTD vm->cycle_to_die
# define NDV vm->next_die_verification
# define NLIVE vm->nbr_live
# define NCHECK vm->nbr_check
# define PMV print_middle_value
# define PMS print_middle_simple
# define PSTR print_middle_str
# define FCO find_champion_order
# define OIP ch->op_in_progress
# define CH t_champion

typedef struct	s_champion
{
	int			n;
	int			numero;
	int			order;
	int			born_in;
	char		registre[REG_NUMBER][REG_SIZE];
	int			pc;
	int			carry;
	int			in_live;
	int			last_opcode;
	int			last_position;
	int			in_progress;
	int			op_in_progress;
	struct s_vm	*vm;
	PLAYER		*p;
}				t_champion;

typedef struct	s_viewer
{
	int			champion_color[MAX_PLAYERS];
	int			actual_process[MAX_PLAYERS];
	char		opname[16][5];
	t_champion	*process_position[MEM_SIZE];
	int			namemode;
	int			pause;
	int			speed;
	int			width_memory;
	int			memory_line;
	int			memory_w;
	int			memory_h;
	int			header_w;
	int			header_h;
	int			info_w;
	int			info_h;
	int			ch_w;
	int			ch_h;
	int			w;
	int			h;
	WINDOW		*header;
	WINDOW		*memory;
	WINDOW		*info;
	WINDOW		*champion[MAX_PLAYERS];
}				t_viewer;

typedef	struct	s_player
{
	int			id;
	int			dead;
	int			pc_number;
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	UI			size;
	char		memory[CHAMP_MAX_SIZE + 1];
	t_champion	*first_process;
}				t_player;

typedef struct	s_vm
{
	t_player	player[MAX_PLAYERS];
	int			last_in_live;
	t_list		*list_champions;
	int			visual;
	int			show_live;
	int			number_champions;
	int			next_die_verification;
	int			cycle_to_die;
	int			nbr_live;
	int			nbr_check;
	int			actual_turn;
	int			nbr_turn;
	char		memory[MEM_SIZE];
	void		(*tab_function[16])(CH *c, struct s_vm *v, char **a, char *t);
	int			duration[16];
	int			direct_size[16];
	int			argc[16];
	t_viewer	*viewer;
}				t_vm;

void			f_sti(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_fork(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_lfork(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_lld(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_ld(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_add(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_zjmp(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_sub(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_ldi(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_or(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_st(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_aff(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_live(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_xor(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_lldi(t_champion *champion, t_vm *vm, char **arg, char *type);
void			f_and(t_champion *champion, t_vm *vm, char **arg, char *type);

t_champion		*read_champion(char *file, int n, t_vm *vm, int o);
void			convert_endian(char *mem, int len);
int				available_number(t_list *list, t_list *elem, int n);
int				cmp_champion(void *a1, void *a2);
void			dispatch_champions(t_vm *vm);
void			print_vm(t_vm *vm);
int				one_turn(t_vm *vm);
void			execute_instruction(t_champion *ch, t_vm *vm);
void			move_pc(t_champion *ch, int move);
void			verify_live(t_vm *vm);
void			victory(t_champion *ch);
int				champion_here(t_list *elem, int position);
t_champion		*find_champion(t_list *elem, int actual, int n);
t_champion		*find_champion_id(t_list *elem, int id);
t_champion		*find_champion_order(t_list *elem, int id, int actual, int n);
void			initialise_function(t_vm *vm);
void			end_game(t_vm *vm);
void			change_position(t_champion *ch, int new);
void			init_duration(int duration[16]);
void			init_argc(int argc[16]);
void			init_direct_size(int direct_size[16]);
t_vm			*init_vm();
void			add_process(t_vm *vm, t_champion *ch);

int				check_reg(char *reg);
void			stock_reg(t_champion *ch, int reg, char *val, int o);
void			cpy_reg(t_champion *ch, int reg, int src);
int				cast_int(char *tab);
int				cast_int_rev(char *tab);
int				cast_int_frone(char tab);
short int		cast_sh_int(char *tab);
int				convert(t_champion *ch, t_vm *vm, char *arg, char type);
int				convert_nomod(t_champion *ch, t_vm *vm, char *arg, char type);
int				convert_sh(t_champion *ch, t_vm *vm, char *arg, char type);
int				index_memory(int index);

void			init_visual(t_vm *vm);
int				update_visual(t_vm *vm);
WINDOW			*new_window(int x, int y, int w, int h);
void			refresh_window(WINDOW *window);
void			draw_memory(t_vm *vm, t_viewer *v, WINDOW *w);
void			draw_all(t_vm *vm, t_viewer *v);
void			print_middle_value(WINDOW *w, char *str, int value, int *line);
void			print_middle_str(WINDOW *win, char *str, char *value, int *l);
void			print_middle_simple(WINDOW *win, char *s, int f, int *line);
void			print_middle_hexa(WINDOW *w, unsigned int v, int f, int *l);
int				find_champion_color(t_vm *vm, t_viewer *v, int position);
int				find_mem_color(t_vm *vm, t_viewer *v, int i, int y);
int				find_color_of(t_champion *c, t_viewer *v);
void			draw_register(WINDOW *w, t_champion *c, int line);
void			init_opname(char opname[16][5]);
void			init_color_champion(int color[MAX_PLAYERS]);
void			init_color_pair(void);
void			first_screen(t_viewer *v);
t_viewer		*new_viewer(void);
void			print_header(WINDOW *win, char *h1, char *h2, int *line);

#endif
