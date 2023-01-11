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

static void	next_cmd_loop(char *line, int *i, char *sp_char)
{
	if (!*sp_char)
	{
		if (!*i)
		{
			if ((line[*i] == '\"') || (line[*i] == '\''))
				*sp_char = line[*i];
		}
		else if (((line[*i + 1] == '\"') || (line[*i + 1] == '\''))
			&& line[*i] != '\\')
			*sp_char = line[*i + 1];
	}
	else if (*sp_char)
	{
		if ((line[*i] != '\\') && (line[*i + 1] == *sp_char))
			*sp_char = 0;
	}
}

int	find_next_cmd(char *line, int offset, char *sp_char, int sep)
{
	int		i;

	i = offset;
	if (!line[i])
		return (1);
	if (is_separator(line, i))
	{
		sep = is_separator(line, i);
		if (sep == T_or || sep == T_and)
			return (2);
		else
			return (1);
	}
	else
	{
		while (line[i + 1])
		{
			next_cmd_loop(line, &i, sp_char);
			if (is_separator(line, i) && !*sp_char)
				return (i - offset);
			i++;
		}
	}
	i += 2;
	return (i - offset);
}
