/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:04:38 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/12 15:04:40 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "input.h"

int	eat_here_doc(char *str, t_ftmap *vars)
{
	char	*old_str;

	old_str = str;
	str = here_doc(str, "> ", vars);
	free(old_str);
	if (!str)
		return (0);
	free(str);
	return (1);
}

static char	*get_path(char *str)
{
	while (*str == '>' || *str == '<')
		str++;
	while (ft_is_whitespace(*str))
		str++;
	return (str);
}

static int	add_redir(char *str, char *path, t_ftmap *vars)
{
	int		fd;
	char	*res;

	fd = -1;
	if (ft_strncmp(str, ">>", 2) == 0)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strncmp(str, "<<", 2) == 0)
	{
		res = here_doc(path, "> ", vars);
		if (!res)
			return (0);
		free(res);
		return (1);
	}
	else if (ft_strncmp(str, ">", 1) == 0)
		fd = open(path, O_WRONLY | O_CREAT, 0644);
	else if (ft_strncmp(str, "<", 1) == 0)
		fd = open(path, O_RDONLY);
	if (fd != -1)
		close(fd);
	return (fd != -1);
}

int	solo_redir(t_ftfrwlist *list, t_ftmap *vars)
{
	char				*path;
	t_ftfrwlist_node	*node;

	node = list->first;
	while (node)
	{
		path = get_path(node->value);
		if (!add_redir(node->value, path, vars))
		{
			if (errno != 0)
				ft_dprintf(2, "%s: %s: %s\n", NAME, path, strerror(errno));
			return (0);
		}
		node = node->next;
	}
	return (1);
}
