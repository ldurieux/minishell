/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:36:23 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/10 13:36:40 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	eat_quote(char **str)
{
	char	quote;
	char	*new_str;

	new_str = *str;
	quote = *new_str;
	if (quote != '\"' && quote != '\'')
		return ;
	new_str++;
	while (*new_str && *new_str != quote)
		new_str++;
	*str = new_str;
}

static int	next_cmd_sep(char *str)
{
	if (ft_strncmp(str, "||", 2) == 0)
		return (T_or);
	if (ft_strncmp(str, "&&", 2) == 0)
		return (T_and);
	if (str[0] == '|')
		return (T_pipe);
	return (0);
}

int	find_next_cmd(char *line, int offset)
{
	char	*save_line;
	int		sep;

	line += offset;
	save_line = line;
	if (!*line)
		return (1);
	sep = next_cmd_sep(line);
	if (sep)
		return (1 + (sep == T_or || sep == T_and));
	while (*line)
	{
		if (next_cmd_sep(line))
			return (line - save_line);
		eat_quote(&line);
		if (*line)
			line++;
	}
	return (line - save_line);
}
