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

static void	delete_list(t_ftfrwlist *list)
{
	ft_frwlist_iter(list, free);
	ft_frwlist_delete(list);
}

static int	extract_redirs(t_ftfrwlist *tok_list, t_ftfrwlist **redir_list)
{
	t_ftfrwlist_node	*node;
	size_t				idx;
	char				chr;

	*redir_list = ft_frwlist_new();
	if (!*redir_list)
		return (delete_list(tok_list), 0);
	idx = (size_t)-1;
	while (++idx || 1)
	{
		node = ft_frwlist_node_at(tok_list, idx);
		if (!node)
			break ;
		chr = ((char *)node->value)[0];
		if (chr != '>' && chr != '<')
			continue ;
		if (!ft_frwlist_push_back(*redir_list, node->value))
			return (delete_list(*redir_list), delete_list(tok_list), 0);
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

static int	make_redirs(t_ftfrwlist *list, t_exec_cmd *cmd)
{
	char	*path;

	(void)list;
	(void)cmd;
	(void)path;
	return (1);
}

int	add_exec(t_exec *exec, char **line, t_ftmap *vars)
{
	t_ftfrwlist			*tok_list;
	t_ftfrwlist			*redir_list;
	t_exec_cmd			*cmd;
	char				**args;

	*line = replace_vars(*line, vars);
	if (!*line)
		return (0);
	if (!tokenize(&tok_list, *line))
		return (0);
	if (!extract_redirs(tok_list, &redir_list))
		return (0);
	cmd = NULL;
	if (tok_list->size != 0)
	{
		args = make_args(tok_list);
		if (!args)
			return (delete_list(redir_list), delete_list(tok_list), 0);
		cmd = exec_add_cmd(exec, tok_list->first->value, args);
	}
	if (!make_redirs(redir_list, cmd))
		return (delete_list(redir_list), delete_list(tok_list), 0);
	ft_frwlist_delete(tok_list);
	delete_list(redir_list);
	return (1);
}
