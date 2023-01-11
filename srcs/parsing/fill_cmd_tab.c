/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:37:49 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/11 10:52:03 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_nb_cmd(char	*line)
{
	int	nb_cmd;
	int	i;
	int	separator;

	nb_cmd = 0;
	i = 0;
	while (line[i] && ft_is_whitespace(line[i]))
		i++;
	if (!line[i])
		nb_cmd++;
	while (line[i])
		get_separator(&separator, line, &i, &nb_cmd);
	return (nb_cmd);
}

char	**cpy_cmd(char **cmd_tab, char *line, t_cmd_info cmd)
{
	int	i;
	int	j;

	i = 0;
	j = cmd.offset;
	while (i < cmd.size)
	{
		cmd_tab[cmd.cmd_number][i] = line[j];
		i++;
		j++;
	}
	cmd_tab[cmd.cmd_number][i] = 0;
	return (cmd_tab);
}

char	**ft_split_cmd_line(char *line, int nb_cmd)
{
	char		**cmd_tab;
	int			i;
	t_cmd_info	cmd;
	char		sp_char;

	sp_char = 0;
	i = 0;
	cmd.offset = 0;
	cmd_tab = malloc(sizeof(char *) * (nb_cmd + 1));
	if (!cmd_tab)
		return (0);
	while (i < nb_cmd)
	{
		cmd.cmd_number = i;
		cmd.size = find_next_cmd(line, cmd.offset, &sp_char, 0);
		cmd_tab[i] = malloc(sizeof(char) * cmd.size + 1);
		if (!cmd_tab[i])
			return (free_cmd_tab(cmd_tab, i + 1), (char **)0);
		cmd_tab = cpy_cmd(cmd_tab, line, cmd);
		cmd.offset += cmd.size;
		i++;
	}
	cmd_tab[i] = 0;
	return (cmd_tab);
}

void	set_type(t_node *node)
{
	int	i;

	i = 0;
	while (node[i].str)
	{
		if (!ft_strcmp(node[i].str, "&&"))
			node[i].type = T_and;
		else if (!ft_strcmp(node[i].str, "||"))
			node[i].type = T_or;
		else if (!ft_strcmp(node[i].str, "|"))
			node[i].type = T_pipe;
		else
			node[i].type = T_cmd;
		i++;
	}
}

void	fill_node_tab(char **cmd_list, t_node *node_tab)
{
	size_t	i;

	i = (size_t)-1;
	while (cmd_list[++i])
		node_tab[i].str = cmd_list[i];
}
