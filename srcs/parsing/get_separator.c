/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_separator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:34:56 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/10 13:49:17 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_separator(char *line, int i)
{
	if (line[i] == '|')
	{
		if (line[i + 1] == '|')
			return (T_or);
		return (T_pipe);
	}
	if (line[i] == '&')
	{
		if (line[i + 1] == '&')
			return (T_and);
	}
	return (0);
}

static void	separator_loop(int *separator, char *line, int *i, int *skip)
{
	(*i)++;
	if (!*skip)
	{
		if (line[*i] == '\'' || line[*i] == '\"' || line[*i] == '`')
			*skip = line[*i];
	}
	else if (line[*i] == *skip)
		*skip = 0;
	*separator = is_separator(line, *i);
}

void	get_separator(int *separator, char *line, int *i, int *nb_cmd)
{
	int	skip;

	skip = 0;
	(*nb_cmd)++;
	*separator = is_separator(line, *i);
	if (line[*i] == '\'' || line[*i] == '\"' || line[*i] == '`')
		skip = line[*i];
	while (line[*i] && (skip || !*separator))
		separator_loop(separator, line, i, &skip);
	if (*separator == T_or || *separator == T_and)
		*i += 2;
	else if (*separator)
		(*i)++;
	else
		return ;
	(*nb_cmd)++;
}
