/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:18:11 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/12 11:18:15 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "input.h"

static char	*get_path(char *str)
{
	while (*str == '>' || *str == '<')
		str++;
	while (ft_is_whitespace(*str))
		str++;
	return (str);
}

static void	close_if_needed(t_exec_cmd *cmd, int fd)
{
	if (fd == 0 && cmd->redir_in != -1)
		close(cmd->redir_in);
	else if (fd == 1 && cmd->redir_out != -1)
		close(cmd->redir_out);
	else if (fd == 2 && cmd->redir_err != -1)
		close(cmd->redir_out);
}

static int	was_opened(t_exec_cmd *cmd, char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (1);
	if (ft_strncmp(str, ">>", 2) == 0 && cmd->redir_out == -1)
		return (0);
	else if (ft_strncmp(str, ">", 1) == 0 && cmd->redir_out == -1)
		return (0);
	else if (ft_strncmp(str, "<", 1) == 0 && cmd->redir_in == -1)
		return (0);
	return (1);
}

static int	add_redir(t_exec_cmd *cmd, char *str, char *path)
{
	if (ft_strncmp(str, ">>", 2) == 0)
	{
		close_if_needed(cmd, STDOUT_FILENO);
		cmd->redir_out = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (ft_strncmp(str, "<<", 2) == 0)
	{
		if (cmd->here_doc)
			free(here_doc(cmd->here_doc, "> "));
		cmd->here_doc = ft_strdup(path);
	}
	else if (ft_strncmp(str, ">", 1) == 0)
	{
		close_if_needed(cmd, STDOUT_FILENO);
		cmd->redir_out = open(path, O_WRONLY | O_CREAT, 0644);
	}
	else if (ft_strncmp(str, "<", 1) == 0)
	{
		close_if_needed(cmd, STDIN_FILENO);
		cmd->redir_in = open(path, O_RDONLY);
	}
	else
		return (0);
	return (was_opened(cmd, str));
}

int	make_redirs(t_ftfrwlist *list, t_exec_cmd *cmd)
{
	char				*path;
	t_ftfrwlist_node	*node;

	if (!cmd)
		return (solo_redir(list));
	node = list->first;
	while (node)
	{
		path = get_path(node->value);
		if (!add_redir(cmd, node->value, path))
		{
			ft_dprintf(2, "%s: %s: %s\n", NAME, path, strerror(errno));
			close(cmd->redir_in);
			close(cmd->redir_out);
			close(cmd->redir_err);
			return (0);
		}
		node = node->next;
	}
	return (1);
}
