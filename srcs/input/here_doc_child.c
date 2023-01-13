/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:09:17 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/12 15:09:19 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	handle_abort_line(int sign)
{
	(void) sign;
	write(1, "\n", 1);
	exit(127);
}

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
		return (ft_frwlist_delete(list), NULL);
	buffer = list_to_str(list);
	ft_frwlist_iter(list, free);
	return (ft_frwlist_delete(list), buffer);
}

char	*here_doc_res(int fd)
{
	char	*res;

	if (fd == -1)
		return (NULL);
	res = read_all(fd);
	close(fd);
	if (!res)
		return (ft_strdup(""));
	return (res);
}

char	*here_doc_child(char *end_str, char *ps2, int fd)
{
	char			*buffer;
	t_ftvector		*str;
	struct termios	attributes;
	int				i;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	signal(SIGINT, handle_abort_line);
	str = ft_vector_new(sizeof(char), 32);
	buffer = readline(ps2);
	while (ft_strcmp(buffer, end_str) && buffer)
	{
		i = -1;
		while (buffer[++i])
			ft_vector_push_back(str, &buffer[i]);
		ft_vector_push_back(str, "\n");
		free(buffer);
		buffer = readline(ps2);
	}
	ft_vector_push_back(str, "\0");
	write(fd, str->data, ft_strlen(str->data));
	free(buffer);
	exit(0);
}
