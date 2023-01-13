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
#include "input.h"

#define NOT_FOUND "command not found"
#define DENIED "Permission denied"
#define ALLOC "Allocation error"

static char	*find_path_check_error(t_exec_cmd *cmd, char **splitted_paths,
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
	return (joined_path);
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
	joined_path = NULL;
	while (splitted_paths[++idx])
	{
		to_join[0] = splitted_paths[idx];
		joined_path = ft_strjoin_r(to_join, "/");
		if (!joined_path)
			ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, ALLOC);
		if (!joined_path)
			exit(ERROR_CODE);
		if (access(joined_path, F_OK) != -1)
			break ;
		free(joined_path);
	}
	return (find_path_check_error(cmd, splitted_paths, joined_path, idx));
}

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
	if (dup2(pipes[PIPE_OUT], STDIN_FILENO) == -1)
		return (free(buffer), 0);
	close(pipes[PIPE_OUT]);
	close(pipes[PIPE_IN]);
	free(buffer);
	return (1);
}

static int	run_child_error(t_exec_cmd *cmd, char *error, int ret)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, error);
	return (ret);
}

void	run_child(t_exec_cmd *cmd, char *paths, char **envp)
{
	char		*path;
	char		**args;
	t_builtin	builtin;

	if (!redir_fork(cmd))
		exit(run_child_error(cmd, strerror(errno), ERROR_CODE));
	builtin = get_builtin(cmd->name);
	if (builtin)
		exit(run_builltin(builtin, cmd, envp));
	else if (ft_strchr(cmd->name, '/') != NULL)
		path = cmd->name;
	else
		path = find_path(cmd, paths);
	if (!path)
		exit(run_child_error(cmd, NOT_FOUND, ERROR_CODE));
	args = make_argv(cmd->name, cmd->args, NULL);
	if (!args)
		exit(run_child_error(cmd, ALLOC, ERROR_CODE));
	if (!read_here_doc(cmd))
		exit(run_child_error(cmd, strerror(errno), 130));
	execve(path, args, envp);
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, strerror(errno));
	exit(ERROR_CODE);
}
