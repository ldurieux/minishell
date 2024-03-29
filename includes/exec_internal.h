/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:07:52 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:07:53 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "ft_vector.h"
# include "ft_frwlist.h"
# include "ft_printf.h"
# include "libft.h"
# include "vars.h"
# include "builtin.h"

# define PIPE_IN 1
# define PIPE_OUT 0
# define ERROR_CODE 127

typedef struct s_func_vars
{
	int					pipes[4];
	t_ftfrwlist_node	*node;
	pid_t				*pids;
}	t_func_vars;

typedef struct s_exec		t_exec;
typedef struct s_exec_cmd	t_exec_cmd;

void	run_child(t_exec_cmd *cmd, char *paths, char **envp);
int		run_builltin(t_builtin builtin, t_exec_cmd *cmd, char **envp);
pid_t	run_pipe_internal(t_exec_cmd *cmd, int *pipes, int cur_pipes, int pos);

int		redir_parent(t_exec_cmd *cmd);
int		restore_redir(t_exec_cmd *cmd);
int		redir_fork(t_exec_cmd *cmd);

char	**make_argv(char *cmd, char **args, int *argc);
int		get_child_ret_code(t_exec *exec, pid_t child_pid);
int		get_pipe_ret_code(t_exec *exec, pid_t *pids, size_t count);

void	clean(t_exec *exec);

#endif // EXEC_INTERNAL_H
