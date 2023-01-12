/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ret_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:58:21 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/12 14:35:52 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

int	get_child_ret_code(t_exec *exec, pid_t child_pid)
{
	int	ret_code;

	g_pids = ft_calloc(sizeof(pid_t), 2);
	g_pids[0] = child_pid;
	waitpid(child_pid, &ret_code, 0);
	ret_code = WEXITSTATUS(ret_code);
	if (exec->buffer_fd != -1)
		exec->buffer_out = read_all(exec->buffer_fd);
	free(g_pids);
	g_pids = NULL;
	return (ret_code);
}

int	get_pipe_ret_code(t_exec *exec, pid_t *pids, size_t count)
{
	int		ret_code;
	size_t	idx;

	g_pids = pids;
	ret_code = ERROR_CODE;
	idx = (size_t)-1;
	while (++idx < count)
	{
		waitpid(pids[idx], &ret_code, 0);
		ret_code = WEXITSTATUS(ret_code);
	}
	if (exec->buffer_fd != -1)
		exec->buffer_out = read_all(exec->buffer_fd);
	free(g_pids);
	g_pids = NULL;
	return (ret_code);
}
