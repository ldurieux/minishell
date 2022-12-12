/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:06:26 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/11 10:06:28 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_internal.h"

static int	run_single(t_exec *exec)
{
	t_builtin	builtin;
	t_exec_cmd	*cmd;
	pid_t		pid;

	cmd = exec->cmds->first->value;
	builtin = get_builtin(cmd->name);
	if (builtin)
		return (run_builltin(builtin, cmd, exec->envp));
	pid = fork();
	if (pid == 0)
		run_child(cmd, exec->paths, exec->envp);
	return (get_child_ret_code(pid));
}

static int	run_pipe(t_exec *exec)
{
	(void)exec;
	(void)WIP;
	return (1);
}

int	exec_run(t_exec *exec)
{
	if (exec->cmds->size <= 0)
		return (ERROR_CODE);
	if (exec->flags & Exec_Pipe)
		return (run_pipe(exec));
	return (run_single(exec));
}
