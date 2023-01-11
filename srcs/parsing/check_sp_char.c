/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sp_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:38:42 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/10 13:39:19 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_sp_char(char *line, int *i, int *j)
{
	if (line[*i] == '&')
	{
		if (*i == 0)
		{
			if (line[*i + 1] != '&')
				return (1);
		}
		else if (line[*i + 1] != '&' && line[*i - 1] != '&')
			return (1);
	}
	if (line[*i] == '|' || line[*i] == '&')
	{
		if (line[*i + 1] == line[*i])
			*j = *i + 2;
		else
			*j = *i + 1;
	}
	while (ft_is_whitespace(line[*j]))
		(*j)++;
	if (line[*j] == '&' || line[*j] == '|' || !line[*j])
		return (1);
	return (0);
}

int	ft_check_sep(char *line)
{
	int		i;
	int		j;
	char	sp_char;

	i = 0;
	sp_char = 0;
	while (line[i])
	{
		j = 0;
		if (!sp_char)
		{
			if (line[i] == '"' || line[i] == '\'')
				sp_char = line[i];
		}
		else if (sp_char)
		{
			if (sp_char == line[i])
				sp_char = 0;
		}
		if (!sp_char)
			if (check_sp_char(line, &i, &j))
				return (1);
		i++;
	}
	return (0);
}
