/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:06:15 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/11 10:06:18 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_init(t_exec *exec, char *paths)
{
	if (!exec)
		return (0);
	exec->cmds = ft_frwlist_new();
	if (!exec->cmds)
		return (0);
	exec->flags = Exec_None;
	exec->paths = paths;
	exec->buffer_in = NULL;
	exec->buffer_out = NULL;
	return (1);
}

static void	free_exec_cmd(void *ptr)
{
	size_t		idx;
	t_exec_cmd	*cmd;

	cmd = ptr;
	if (!cmd)
		return ;
	free(cmd->name);
	if (cmd->args)
	{
		idx = (size_t) - 1;
		while (cmd->args[++idx])
			free(cmd->args[idx]);
		free(cmd->args);
	}
	free(cmd);
}

void	exec_destroy(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->cmds)
	{
		ft_frwlist_iter(exec->cmds, free_exec_cmd);
		ft_frwlist_delete(exec->cmds);
	}
	free(exec->paths);
	free(exec->buffer_in);
	free(exec->buffer_out);
}
