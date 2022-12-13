/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:02:45 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:02:47 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_internal.h"
#include "input.h"

#define ALLOC "Allocation error"

static int	read_here_doc(t_exec_cmd *cmd)
{
	char	*buffer;
	int		pipes[2];

	if (!cmd->here_doc)
		return (1);
	buffer = here_doc(cmd->here_doc, "> ");
	if (!buffer)
		return (0);
	if (pipe(pipes) == -1)
		return (free(buffer), 0);
	write(pipes[PIPE_IN], buffer, ft_strlen(buffer));
	free(buffer);
	if (dup2(pipes[PIPE_OUT], STDIN_FILENO) == -1)
		return (0);
	close(pipes[PIPE_OUT]);
	close(pipes[PIPE_IN]);
	return (1);
}

int	run_builltin(t_builtin builtin, t_exec_cmd *cmd, char **envp)
{
	char	**argv;
	int		argc;
	int		res;

	if (!read_here_doc(cmd))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", NAME, strerror(errno));
		exit(130);
	}
	argv = make_argv(cmd->name, cmd->args, &argc);
	if (!argv)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, ALLOC);
		return (127);
	}
	res = builtin(argc, argv, envp);
	free(argv);
	return (res);
}
