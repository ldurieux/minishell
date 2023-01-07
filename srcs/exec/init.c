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

#define PATH_STR "PATH="
#define PATH_STR_LEN 5

static char	*get_path(char **envp)
{
	char	*path;
	size_t	idx;

	if (!envp)
		return (NULL);
	idx = (size_t)-1;
	while (envp[++idx])
		if (ft_strncmp(envp[idx], PATH_STR, PATH_STR_LEN) == 0)
			break ;
	if (!envp[idx])
		return (NULL);
	path = ft_strdup(envp[idx] + PATH_STR_LEN);
	return (path);
}

int	exec_init(t_exec *exec, char **envp, t_ftmap *vars)
{
	if (!exec)
		return (0);
	exec->cmds = ft_frwlist_new();
	if (!exec->cmds)
		return (0);
	exec->flags = Exec_None;
	exec->envp = envp;
	exec->vars = vars;
	exec->paths = get_path(envp);
	exec->buffer_out = NULL;
	exec->buffer_fd = -1;
	return (1);
}

int	exec_update(t_exec *exec, char **envp)
{
	if (!exec || !exec->cmds)
		return (0);
	exec->envp = envp;
	exec->paths = get_path(envp);
	exec->buffer_out = NULL;
	exec->buffer_fd = -1;
	return (1);
}
