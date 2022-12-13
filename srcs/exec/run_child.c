/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:58:10 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 22:58:14 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_internal.h"

#define NOT_FOUND "command not found"
#define DENIED "Permission denied"
#define ALLOC "Allocation error"

static void	find_path_check_error(t_exec_cmd *cmd, char **splitted_paths,
								char *joined_path, size_t idx)
{
	if (!splitted_paths[idx])
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, NOT_FOUND);
		exit(ERROR_CODE);
	}
	if (access(joined_path, X_OK) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, DENIED);
		exit(126);
	}
}

static char	*find_path(t_exec_cmd *cmd, char *paths)
{
	char	**splitted_paths;
	char	*joined_path;
	char	*to_join[3];
	size_t	idx;

	to_join[1] = cmd->name;
	to_join[2] = NULL;
	splitted_paths = ft_split(paths, ':');
	if (!splitted_paths)
		return (NULL);
	idx = (size_t)-1;
	while (splitted_paths[++idx])
	{
		to_join[0] = splitted_paths[idx];
		joined_path = ft_strjoin_r(to_join, "/");
		if (!joined_path)
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, ALLOC);
			exit(ERROR_CODE);
		}
		if (access(joined_path, F_OK) != -1)
			break ;
	}
	find_path_check_error(cmd, splitted_paths, joined_path, idx);
	return (joined_path);
}

void	run_child(t_exec_cmd *cmd, char *paths, char **envp)
{
	char	*path;
	char	**args;

	if (!redir_fork(cmd))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", NAME, strerror(errno));
		exit(ERROR_CODE);
	}
	path = find_path(cmd, paths);
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, ALLOC);
		exit(ERROR_CODE);
	}
	args = make_argv(cmd->name, cmd->args, NULL);
	if (!args)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, ALLOC);
		exit(ERROR_CODE);
	}
	execve(path, args, envp);
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, strerror(errno));
	exit(ERROR_CODE);
}
