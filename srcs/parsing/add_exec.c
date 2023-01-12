/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:49:31 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/11 23:49:33 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	del_list(t_ftfrwlist *list)
{
	ft_frwlist_iter(list, free);
	ft_frwlist_delete(list);
}

static int	extract_redirs(t_ftfrwlist *tok_list, t_ftfrwlist **redir_list,
							int skip_first)
{
	t_ftfrwlist_node	*node;
	size_t				idx;
	char				chr;

	*redir_list = ft_frwlist_new();
	if (!*redir_list)
		return (del_list(tok_list), 0);
	idx = (size_t)-1 + skip_first;
	while (++idx || 1)
	{
		node = ft_frwlist_node_at(tok_list, idx);
		if (!node)
			break ;
		chr = ((char *)node->value)[0];
		if (chr != '>' && chr != '<')
			continue ;
		if (!ft_frwlist_push_back(*redir_list, node->value))
			return (del_list(*redir_list), del_list(tok_list), 0);
		ft_frwlist_remove_at(tok_list, idx--);
	}
	return (1);
}

static char	**make_args(t_ftfrwlist *list)
{
	t_ftfrwlist_node	*node;
	char				**res;
	size_t				idx;

	res = malloc(sizeof(char *) * list->size);
	if (!res)
		return (NULL);
	res[list->size - 1] = NULL;
	node = list->first->next;
	idx = 0;
	while (node)
	{
		res[idx++] = node->value;
		node = node->next;
	}
	return (res);
}

static int	add_exec_init(char **line, t_ftmap *vars, t_ftfrwlist **toks,
							t_ftfrwlist **redirs)
{
	int		skip_first;
	size_t	idx;

	*line = replace_vars(*line, vars);
	if (!*line)
		return (0);
	if (!tokenize(toks, *line))
		return (0);
	idx = (size_t)-1;
	while (ft_is_whitespace((*line)[++idx]))
		;
	skip_first = (*line)[idx] == '\'' || (*line)[idx] == '\"';
	if (!extract_redirs(*toks, redirs, skip_first))
		return (0);
	return (1);
}

int	add_exec(t_exec *exec, char **line, t_ftmap *vars)
{
	t_ftfrwlist			*toks;
	t_ftfrwlist			*redirs;
	t_exec_cmd			*cmd;
	char				**args;

	if (!add_exec_init(line, vars, &toks, &redirs))
		return (0);
	cmd = NULL;
	if (toks->size != 0)
	{
		args = make_args(toks);
		if (!args)
			return (del_list(redirs), del_list(toks), 0);
		cmd = exec_add_cmd(exec, toks->first->value, args);
	}
	if (!make_redirs(redirs, cmd))
		return (exec_rm_last_cmd(exec), del_list(redirs), del_list(toks), 0);
	ft_frwlist_delete(toks);
	del_list(redirs);
	return (1);
}
