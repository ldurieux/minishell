/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:26:17 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/11 16:12:24 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "ft_printf.h"
# include "exec.h"
# include "vars.h"

typedef struct s_node	t_node;
typedef struct s_cmd	t_cmd;

typedef enum e_bash_operator
{
	T_cmd,
	T_and,
	T_or,
	T_pipe,
}	t_bash_operator;

typedef struct s_node
{
	char			*str;
	t_bash_operator	type;
}	t_node;

typedef struct s_cmd_info
{
	int	offset;
	int	size;
	int	cmd_number;
}	t_cmd_info;

t_node	*parse_shell(char *line);
char	*replace_vars(char *str, t_ftmap *vars);
char	*remove_quotes(char *str);
void	free_node_tab(t_node *node, int nb_cmd);
int		run_nodes(t_node *nodes, t_ftmap *vars);

void	print_node_tab(t_node *node);
void	free_cmd_tab(char **tab_cmd, int nb_cmd);
int		ft_check_line(char *line);
int		ft_check_esp(char *line);
int		is_separator(char *line, int i);
void	get_separator(int *separator, char *line, int *i, int *nb_cmd);
int		find_next_cmd(char *line, int offset, char *sp_char, int sep);
void	set_type(t_node *node);
void	fill_node_tab(char **cmd_list, t_node *node_tab);
int		ft_check_sep(char *line);
int		get_nb_cmd(char	*line);
char	**cpy_cmd(char **cmd_tab, char *line, t_cmd_info cmd);
char	**ft_split_cmd_line(char *line, int nb_cmd);
char	*get_var_name(char *str);
size_t	get_replaced_size(char *str, char *var_name, t_vars	*replacement_vars);
char	*create_new_str(char *str, int size, t_vars *replacement_vars,
			int start);
int		tokenize(t_ftfrwlist **list, char *line);
int		add_exec(t_exec *exec, char **line, t_ftmap *vars);
int		make_redirs(t_ftfrwlist *list, t_exec_cmd *cmd);
int		solo_redir(t_ftfrwlist *list);

#endif
