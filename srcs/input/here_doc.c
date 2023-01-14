/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:04:55 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/12 16:45:35 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	here_doc_fd_res(pid_t pid, int fd)
{
	int		ret_code;

	ret_code = 0;
	waitpid(pid, &ret_code, 0);
	ret_code = WEXITSTATUS(ret_code);
	if (ret_code == 127)
		return (close(fd), -1);
	return (fd);
}

int	here_doc_fd(char *end_str, char *ps2, t_ftmap *vars)
{
	int				pipes[2];
	pid_t			pid;
	struct termios	saved;
	int				res;

	signal(SIGINT, handle_abort_line_exec);
	tcgetattr(STDIN_FILENO, &saved);
	if (pipe(pipes) == -1)
		return (ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno)), -1);
	pid = fork();
	if (pid == -1)
		return (ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno)), -1);
	if (pid == 0)
	{
		close(pipes[0]);
		here_doc_child(end_str, ps2, pipes[1], vars);
	}
	close(pipes[1]);
	res = here_doc_fd_res(pid, pipes[0]);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	signal(SIGINT, handle_abort_line_input);
	return (res);
}

char	*here_doc(char *end_str, char *ps2, t_ftmap *vars)
{
	return (here_doc_res(here_doc_fd(end_str, ps2, vars)));
}
