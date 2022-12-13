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

#define ALLOC "Allocation error"

int	run_builltin(t_builtin builtin, t_exec_cmd *cmd, char **envp)
{
	char	**argv;
	int		argc;
	int		res;

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
