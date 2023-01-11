/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:49:39 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/11 23:49:40 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	eat_whitespace(char *line, size_t *idx)
{
	while (ft_is_whitespace(line[*idx]))
		(*idx)++;
}

static int	add_token(t_ftfrwlist *list, char *line, size_t *idx)
{
	size_t	end_idx;
	char	save_chr;
	char	*token;

	eat_whitespace(line, idx);
	end_idx = *idx;
	while (line[end_idx] == '>' || line[end_idx] == '<')
		end_idx++;
	eat_whitespace(line, &end_idx);
	while (line[end_idx] && !ft_is_whitespace(line[end_idx]))
	{
		save_chr = line[end_idx];
		if (save_chr == '>' || save_chr == '<')
			break ;
		if (save_chr == '\'' || save_chr == '\"')
			while (line[++end_idx] != save_chr)
				if (!line[end_idx])
					break ;
		end_idx++;
	}
	token = ft_strndup(line + *idx, end_idx - *idx);
	if (!token || !ft_frwlist_push_back(list, token))
		return (free(token), 0);
	*idx = end_idx - (save_chr == '>' || save_chr == '<');
	return (1);
}

static void	delete_list(t_ftfrwlist *list)
{
	ft_frwlist_iter(list, free);
	ft_frwlist_delete(list);
}

int	tokenize(t_ftfrwlist **list, char *line)
{
	size_t				idx;
	t_ftfrwlist_node	*node;
	char				*tmp;

	*list = ft_frwlist_new();
	if (!*list)
		return (0);
	idx = (size_t)-1;
	while (line[++idx])
	{
		if (!add_token(*list, line, &idx))
			return (delete_list(*list), 0);
		if (!line[idx])
			break ;
	}
	node = (*list)->first;
	while (node)
	{
		tmp = remove_quotes(node->value);
		if (!tmp)
			return (delete_list(*list), 0);
		node->value = tmp;
		node = node->next;
	}
	return (1);
}
