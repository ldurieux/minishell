/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:57:05 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/11 16:45:57 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_check_redirect(char *str)
{
	int	i;
	int	redirect;

	i = 0;
	redirect = 0;
	while (str[i])
	{
		if (redirect && (str[i] == '&' || str[i] == '|'))
			return (1);
		if (!ft_is_whitespace(str[i]) && !is_redirect(str[i]))
			redirect = 0;
		if (is_redirect(str[i]))
		{
			redirect++;
			if (str[i] == str[i + 1])
				i++;
		}
		if (redirect > 1)
			return (1);
		i++;
	}
	return (redirect);
}

t_node	*parse_shell(char *line)
{
	char	**cmd_list;
	t_node	*node_tab;

	if (ft_check_line(line) || ft_check_esp(line) || ft_check_sep(line)
		|| ft_check_redirect(line))
		return (ft_dprintf(STDERR_FILENO, "parsing error\n"), NULL);
	node_tab = ft_calloc(sizeof(t_node), get_nb_cmd(line) + 1);
	if (!node_tab)
		return (NULL);
	cmd_list = ft_split_cmd_line(line, get_nb_cmd(line));
	fill_node_tab(cmd_list, node_tab);
	free(cmd_list);
	set_type(node_tab);
	return (node_tab);
}
