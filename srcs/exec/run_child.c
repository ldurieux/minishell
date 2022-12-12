#include "exec.h"
#include "exec_internal.h"

#define ERROR_CODE 127

#define NOT_FOUND "command not found"
#define DENIED "Permission denied"
#define ALLOC "Allocation error"

static char	*find_path_check_error(t_exec_cmd *cmd, char **splitted_paths,
								char *joined_path, size_t idx)
{
	if (!splitted_paths[idx])
	{
		ft_dprintf(STDEER_FILENO, "%s: %s: %s\n", NAME, cmd->name, NOT_FOUND);
		exit(ERROR_CODE);
	}
	if (access(joined_path, X_OK) == -1)
	{
		ft_dprintf(STDEER_FILENO, "%s: %s: %s\n", NAME, cmd->name, DENIED);
		exit(ERROR_CODE);
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
			ft_dprintf(STDEER_FILENO, "%s: %s: %s\n", NAME, cmd->name, ALLOC);
			exit(ERROR_CODE);
		}
		if (access(joined_path, F_OK) != -1)
			break ;
	}
	find_path_check_error(cmd, splitted_paths, joined_path, idx);
	return (joined_path);
}

//TODO
static char	**get_args(t_exec_cmd *cmd)
{
	char	**res;

	res = NULL;
	return (res);
}

void	run_child(t_exec_cmd *cmd, char *paths, char **envp)
{
	char	*path;
	char	**args;

	if (cmd->redir_in != -1)
		dup2(cmd->redir_in, STDIN_FILENO);
	if (cmd->redir_out != -1)
		dup2(cmd->redir_out, STDOUT_FILENO);
	if (cmd->redir_err != -1)
		dup2(cmd->redir_err, STDERR_FILENO);
	path = find_path(cmd, envp);
	if (!path)
	{
		ft_dprintf(STDEER_FILENO, "%s: %s: %s\n", NAME, cmd->name, ALLOC);
		exit(ERROR_CODE);
	}
	args = get_args(cmd);
	if (!args)
	{
		ft_dprintf(STDEER_FILENO, "%s: %s: %s\n", NAME, cmd->name, ALLOC);
		exit(ERROR_CODE);
	}
	execve(path, args, envp);
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmd->name, strerror(errno));
	exit(ERROR_CODE);
}