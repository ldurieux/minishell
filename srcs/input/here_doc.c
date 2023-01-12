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
#include "exec.h"
#include "exec_internal.h"

static char	*list_to_str(t_ftfrwlist *list)
{
	size_t				size;
	size_t				len;
	t_ftfrwlist_node	*node;
	char				*res;

	size = 0;
	node = list->first;
	while (node)
	{
		size += ft_strlen(node->value);
		node = node->next;
	}
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	node = list->first;
	size = 0;
	while (node)
	{
		len = ft_strlen(node->value);
		ft_memcpy(res + size, node->value, len);
		size += len;
		node = node->next;
	}
	return (res[size] = '\0', res);
}

#define READ_SIZE 64

static char	*read_all(int fd)
{
	t_ftfrwlist	*list;
	char		*buffer;
	ssize_t		bytes_read;

	list = ft_frwlist_new();
	while (list->size == 0 || bytes_read == READ_SIZE)
	{
		buffer = malloc(sizeof(char) * (READ_SIZE + 1));
		if (!buffer)
			return (ft_frwlist_iter(list, free), ft_frwlist_delete(list), NULL);
		bytes_read = read(fd, buffer, READ_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			break ;
		}
		buffer[bytes_read] = '\0';
		if (!ft_frwlist_push_back(list, buffer))
			return (ft_frwlist_iter(list, free), ft_frwlist_delete(list), NULL);
	}
	if (list->size == 0)
		return (NULL);
	buffer = list_to_str(list);
	ft_frwlist_iter(list, free);
	return (ft_frwlist_delete(list), buffer);
}

static char	*here_doc_res(pid_t pid, int fd)
{
	int		ret_code;
	char	*res;

	waitpid(pid, &ret_code, 0);
	ret_code = WEXITSTATUS(ret_code);
	if (ret_code != 0)
		return (close(fd), NULL);
	res = read_all(fd);
	close(fd);
	if (!res)
		return (ft_strdup(""));
	return (res);
}

static void	handle_abort_line(int sign)
{
	int	i;

	(void) sign;
	if (!g_pids)
		return ;
	i = 0;
	while (g_pids[i])
	{
		kill(g_pids[i], SIGINT);
		i++;
	}
	write(1, "\n", 1);
}

char	*here_doc(char *end_str, char *ps2)
{
	int				pipes[2];
	pid_t			pid;
	char			*res;
	struct termios	saved;

	signal(SIGINT, handle_abort_line);
	tcgetattr(STDIN_FILENO, &saved);
	if (pipe(pipes) == -1)
		return (ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno)), NULL);
	pid = fork();
	if (pid == -1)
		return (ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno)), NULL);
	if (pid == 0)
	{
		close(pipes[0]);
		here_doc_child(end_str, ps2, pipes[1]);
	}
	close(pipes[1]);
	res = here_doc_res(pid, pipes[0]);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	return (res);
}
