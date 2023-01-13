/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:06:28 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/11 10:06:30 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_exec_cmd	*sanitize_args(t_exec_cmd *cmd, t_exec *exec)
{
	cmd->args = malloc(sizeof(char *));
	if (!cmd->args)
	{
		free(ft_frwlist_pop_back(exec->cmds));
		return (NULL);
	}
	cmd->args[0] = NULL;
	return (cmd);
}

t_exec_cmd	*exec_add_cmd(t_exec *exec, char *cmd_path, char **cmd_args)
{
	t_exec_cmd	*cmd;

	if (!exec || !cmd_path)
		return (NULL);
	cmd = malloc(sizeof(t_exec_cmd));
	if (!cmd)
		return (NULL);
	if (!ft_frwlist_push_back(exec->cmds, cmd))
		return (free(cmd), NULL);
	cmd->name = cmd_path;
	cmd->args = cmd_args;
	if (!cmd_args)
		if (!sanitize_args(cmd, exec))
			return (NULL);
	if (exec->cmds->size > 1)
		exec->flags |= Exec_Pipe;
	cmd->redir_in = -1;
	cmd->redir_out = -1;
	cmd->redir_err = -1;
	cmd->vars = exec->vars;
	return (cmd);
}
