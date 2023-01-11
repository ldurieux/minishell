/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:23:32 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/11 15:24:10 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	switch_quote(int *quote, int *rm_count)
{
	if (!*quote)
		*quote = 1;
	else
		*quote = 0;
	(*rm_count)++;
}

static int	get_rm_count(char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;
	int	rm_count;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	rm_count = 0;
	while (str[i])
	{
		if (str[i] == '"' && !s_quote)
			switch_quote(&d_quote, &rm_count);
		if (str[i] == '\'' && !d_quote)
			switch_quote(&s_quote, &rm_count);
		i++;
	}
	return (rm_count);
}

static void	skip_quote(char *str, int *i, int *d_quote, int *s_quote)
{
	if (str[*i] == '"' && !*s_quote)
	{
		if (!*d_quote)
			*d_quote = 1;
		else
			*d_quote = 0;
		(*i)++;
	}
	if (str[*i] == '\'' && !*d_quote)
	{
		if (!*s_quote)
			*s_quote = 1;
		else
			*s_quote = 0;
		(*i)++;
	}
}

static char	*rm_quotes(char *str, char *new_str)
{
	int	i;
	int	j;
	int	s_quote;
	int	d_quote;

	i = 0;
	j = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		skip_quote(str, &i, &d_quote, &s_quote);
		if (str[i])
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	new_str[j] = 0;
	return (new_str);
}

char	*remove_quotes(char *str)
{
	int		rm_count;
	int		size;
	char	*new_str;

	rm_count = get_rm_count(str);
	size = ft_strlen(str) - rm_count;
	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	new_str = rm_quotes(str, new_str);
	free(str);
	return (new_str);
}
