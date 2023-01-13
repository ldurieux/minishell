/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:48:56 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/13 17:48:58 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_internal.h"

static int	redir_one_parent(int *fd, int old_fd)
{
	int	save_fd;

	if (*fd != -1)
	{
		save_fd = dup(old_fd);
		if (save_fd == -1)
			return (0);
		if (dup2(*fd, old_fd) == -1)
			return (close(save_fd), 0);
		*fd = save_fd;
	}
	return (1);
}

/* yes, it's possible that we try to write to
 * stderr while it is closed.
 * But does bash makes sense in the first place ? */
int	redir_parent(t_exec_cmd *cmd)
{
	if (!redir_one_parent(&cmd->redir_in, STDIN_FILENO))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", NAME, strerror(errno));
		return (0);
	}
	if (!redir_one_parent(&cmd->redir_out, STDOUT_FILENO))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", NAME, strerror(errno));
		cmd->redir_out = -1;
		cmd->redir_err = -1;
		restore_redir(cmd);
		return (0);
	}
	if (!redir_one_parent(&cmd->redir_err, STDERR_FILENO))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", NAME, strerror(errno));
		cmd->redir_err = -1;
		restore_redir(cmd);
		return (0);
	}
	return (1);
}

/* wdym some errors are no well handled ?
 * if any errors occurs there the program is in
 * an irrecuperable state, so... */
int	restore_redir(t_exec_cmd *cmd)
{
	if (cmd->redir_in != -1)
	{
		if (dup2(cmd->redir_in, STDIN_FILENO) == -1)
			exit(ERROR_CODE);
		close(cmd->redir_in);
	}
	if (cmd->redir_out != -1)
	{
		if (dup2(cmd->redir_out, STDOUT_FILENO) == -1)
			exit(ERROR_CODE);
		close(cmd->redir_out);
	}
	if (cmd->redir_err != -1)
	{
		if (dup2(cmd->redir_err, STDERR_FILENO) == -1)
			exit(ERROR_CODE);
		close(cmd->redir_err);
	}
	return (1);
}

int	redir_fork(t_exec_cmd *cmd)
{
	if (cmd->redir_in != -1)
		if (dup2(cmd->redir_in, STDIN_FILENO) == -1)
			return (0);
	if (cmd->redir_out != -1)
		if (dup2(cmd->redir_out, STDOUT_FILENO) == -1)
			return (0);
	if (cmd->redir_err != -1)
		if (dup2(cmd->redir_err, STDERR_FILENO) == -1)
			return (0);
	return (1);
}
