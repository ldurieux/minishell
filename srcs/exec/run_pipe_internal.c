/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_internal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:58:19 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/13 22:58:20 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_internal.h"

pid_t	run_pipe_internal(t_exec_cmd *cmd, int *pipes, int cur_pipes, int pos)
{
	pid_t	pid;

	if (!(pos & 2))
	{
		pipe(pipes + (size_t)(cur_pipes * 2));
		if (cmd->redir_out == -1)
			cmd->redir_out = (pipes + (size_t)(cur_pipes * 2))[PIPE_IN];
		else
			close((pipes + (size_t)(cur_pipes * 2))[PIPE_IN]);
	}
	if (!(pos & 1))
	{
		if (cmd->redir_in == -1 && !cmd->here_doc)
			cmd->redir_in = (pipes + (size_t)(!cur_pipes * 2))[PIPE_OUT];
		else
			close((pipes + (size_t)(!cur_pipes * 2))[PIPE_OUT]);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_dprintf(STDERR_FILENO, "%d: %d\n", NAME, "fork error");
		return (-1);
	}
	return (pid);
}
