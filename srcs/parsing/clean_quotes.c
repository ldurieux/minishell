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

char	*remove_quotes(char *str)
{
	size_t	idx;
	size_t	len;
	int		last_quote;

	last_quote = 0;
	len = ft_strlen(str);
	idx = (size_t)-1;
	while (str[++idx])
	{
		if (last_quote && str[idx] != last_quote)
			continue ;
		if (str[idx] == '\'' || str[idx] == '\"')
		{
			last_quote = str[idx] * (last_quote == 0);
			ft_memmove(str + idx, str + idx + 1, len - idx);
			idx--;
		}
	}
	return (str);
}
