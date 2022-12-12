/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:36:38 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 10:40:53 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/wait.h>
# include <unistd.h>
# include "ft_frwlist.h"

typedef enum e_exec_flags
{
	Exec_None = 0x0,
	Exec_Pipe = 0x1,
	Exec_Buffer = 0x2,
}	t_exec_flags;

typedef struct s_exec_cmd
{
	char	*name;
	char	**args;
	int		redir_in;
	int		redir_out;
	int		redir_err;
}	t_exec_cmd;

typedef struct s_exec
{
	t_ftfrwlist		*cmds;
	t_exec_flags	flags;
	char			*paths;
	char			*buffer_in;
	char			*buffer_out;
}	t_exec;

/**
 * @brief initialize pipeline
 *		  `paths` will be freed when `destroy` is called
 * @param struct to initialize
 * @return 0 if failed, 1 otherwise
 */
int			exec_init(t_exec *exec, char *paths);

/**
 * @brief free everything in pipeline
 * @param struct to free
 */
void		exec_destroy(t_exec *exec);

/**
 * @brief add a command to the pipeline.
 *		  `cmd_path` and `cmd_args` will be freed by `exec_destroy` and
 *		  should not be freed manually unless this function failed then they
 *		  have to be freed manually
 * @param struct of the pipeline
 * @param path of the command
 * @param args of the command
 * @return NULL if failed, otherwise pointer to the added command
 */
t_exec_cmd	*exec_add_cmd(t_exec *exec, char *cmd_path, char **cmd_args);

/**
 * @brief run every command in the pipeline
 * @param struct of the pipeline
 * @return last command exit code
 */
int			exec_run(t_exec *exec);

#endif // EXEC_H