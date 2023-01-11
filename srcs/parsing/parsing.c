/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:57:05 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/11 10:53:35 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_node	*parse_shell(char *line)
{
	char	**cmd_list;
	t_node	*node_tab;
	int		i;

	i = 0;
	if (ft_check_line(line) || ft_check_esp(line) || ft_check_sep(line))
		return (NULL);
	node_tab = malloc(sizeof(t_node) * (get_nb_cmd(line) + 1));
	if (!node_tab)
		return (NULL);
	cmd_list = ft_split_cmd_line(line, get_nb_cmd(line));
	node_tab = fill_node_tab(cmd_list, node_tab, &i);
	if (!node_tab)
		return (NULL);
	free(cmd_list);
	node_tab[i].str = malloc(sizeof(char *));
	if (!node_tab[i].str)
		return (free_node_tab(node_tab, i),
			free_cmd_tab(cmd_list, -1), NULL);
	node_tab[i].str = 0;
	set_type(node_tab);
	return (node_tab);
}
