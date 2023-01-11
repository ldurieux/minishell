/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:32:31 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/11 16:54:29 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_check_esp(char *line)
{
	int	i;

	i = 0;
	if (!line[i])
		return (0);
	if (line[i] == '&' && line[i + 1] != '&')
		return (1);
	i++;
	if (!line[i])
		return (0);
	while (line[i + 1])
	{
		if (line[i] == '&' && line[i + 1] == '&')
			i++;
		i++;
	}
	return (0);
}

static void	check_loop(char *line, int *i, char *sp_char)
{
	(*i)++;
	if (!*sp_char)
	{
		if ((line[*i] == '\"') || (line[*i] == '\''))
			*sp_char = line[*i];
	}
	else if (*sp_char == line[*i])
		*sp_char = 0;
}

int	ft_check_line(char *line)
{
	int		i;
	char	sp_char;

	i = 0;
	sp_char = 0;
	while (ft_is_whitespace(line[i]) && line[i])
		i++;
	if (!line[i])
		return (0);
	if (line[i] == '&' || line[i] == '|')
		return (1);
	if (line[i] == '\'' || line[i] == '"')
		sp_char = line[i];
	while (line[i])
		check_loop(line, &i, &sp_char);
	if ((line[i - 1] == '&') || (line[i - 1] == '|'))
		return (1);
	return (sp_char);
}
