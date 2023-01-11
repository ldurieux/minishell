/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:29:43 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/11 11:01:06 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_node_tab(t_node *node, int nb_cmd)
{
	int	i;

	i = -1;
	if (nb_cmd >= 0)
		while (++i < nb_cmd)
			free(node[i].str);
	else
		while (node[++i].str)
			free(node[i].str);
	free(node);
}

void	free_cmd_tab(char **tab_cmd, int nb_cmd)
{
	int	i;

	i = 0;
	if (nb_cmd < 0)
	{
		while (tab_cmd[i])
		{
			free(tab_cmd[i]);
			i++;
		}
		free(tab_cmd[i]);
	}
	else
	{
		while (i < nb_cmd)
		{
			free(tab_cmd[i]);
			i++;
		}
	}
}

void	print_node_tab(t_node *node)
{
	int	i;

	i = 0;
	while (node[i].str)
	{
		printf("%d : %s type(%d)\n", i, node[i].str, node[i].type);
		i++;
	}
}
