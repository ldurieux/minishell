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

int	g_process_killed = 0;

static int	run_single(t_exec *exec)
{
	t_builtin	builtin;
	t_exec_cmd	*cmd;
	pid_t		pid;
	int			res;

	cmd = exec->cmds->first->value;
	builtin = get_builtin(cmd->name);
	if (builtin)
	{
		redir_parent(cmd);
		res = run_builltin(builtin, cmd, exec->envp);
		restore_redir(cmd);
		return (res);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_dprintf(STDERR_FILENO, "%d: %d\n", NAME, "fork error");
		return (ERROR_CODE);
	}
	if (pid == 0)
		run_child(cmd, exec->paths, exec->envp);
	return (get_child_ret_code(exec, pid));
}

static pid_t	*run_pipe_init(t_exec *exec, size_t *idx, int *cur_pipes)
{
	pid_t	*res;

	*idx = (size_t)-1;
	*cur_pipes = 0;
	res = ft_calloc(sizeof(pid_t), exec->cmds->size + 1);
	if (!res)
		ft_dprintf(STDERR_FILENO, "%d: %d\n", NAME, "allocation error");
	return (res);
}

static int	run_pipe(t_exec *exec)
{
	t_func_vars	f;
	size_t		idx;
	int			cur_p;

	f.pids = run_pipe_init(exec, &idx, &cur_p);
	if (!f.pids)
		return (ERROR_CODE);
	f.node = exec->cmds->first;
	while (f.node)
	{
		f.pids[++idx] = run_pipe_internal(f.node->value, f.pipes, cur_p,
				(f.node == exec->cmds->first) + ((f.node->next == NULL) << 1));
		if (f.pids[idx] == -1)
			return (free(f.pids), ERROR_CODE);
		if (f.pids[idx] == 0)
			run_child(f.node->value, exec->paths, exec->envp);
		if (f.node != exec->cmds->first)
			close((f.pipes + (size_t)(!cur_p * 2))[PIPE_OUT]);
		if (f.node->next)
			close((f.pipes + (size_t)(cur_p * 2))[PIPE_IN]);
		cur_p = !cur_p;
		f.node = f.node->next;
	}
	close((f.pipes + (!cur_p * 2))[PIPE_OUT]);
	return (get_pipe_ret_code(exec, f.pids, exec->cmds->size));
}

static int	exec_buf(t_exec *exec)
{
	int	save_stdout;
	int	pipes[2];
	int	res;

	if (pipe(pipes) == -1)
		return (ft_dprintf(STDERR_FILENO, "%d: %d\n", NAME, strerror(errno)),
			0);
	save_stdout = dup(STDOUT_FILENO);
	if (save_stdout == -1)
		return (ft_dprintf(STDERR_FILENO, "%d: %d\n", NAME, strerror(errno)),
			close(pipes[0]), close(pipes[1]), 0);
	if (dup2(pipes[1], STDOUT_FILENO) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%d: %d\n", NAME, strerror(errno));
		return (close(pipes[0]), close(pipes[1]), close(save_stdout), 0);
	}
	exec->buffer_fd = pipes[0];
	if (exec->flags & Exec_Pipe)
		res = run_pipe(exec);
	else
		res = run_single(exec);
	if (dup2(save_stdout, STDOUT_FILENO) == -1)
		exit(ERROR_CODE);
	return (close(pipes[0]), close(pipes[1]), close(save_stdout), res);
}

int	exec_run(t_exec *exec)
{
	int	res;

	g_process_killed = 0;
	if (!exec || !exec->cmds)
		return (1);
	if (exec->cmds->size <= 0)
		return (1);
	if (exec->flags & Exec_Buffer)
		res = exec_buf(exec);
	else if (exec->flags & Exec_Pipe)
		res = run_pipe(exec);
	else
		res = run_single(exec);
	if (g_process_killed)
		res = 130;
	clean(exec);
	return (res);
}
