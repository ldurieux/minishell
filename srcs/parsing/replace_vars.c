/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:02:54 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/11 15:56:37 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	find_var(char *str, int *i, int *simple_quote)
{
	while (str[*i] && (str[*i] != '$' || *simple_quote))
	{
		if (!*simple_quote && str[*i] == '\'')
			*simple_quote = 1;
		else if (*simple_quote && str[*i] == '\'')
			*simple_quote = 0;
		(*i)++;
	}
}

char	*replace_vars(char *str, t_ftmap *vars)
{
	int		i;
	int		simple_quote;
	int		size;
	t_vars	*replacement_vars;
	char	*var_name;

	i = 0;
	simple_quote = 0;
	while (str[i])
	{
		find_var(str, &i, &simple_quote);
		if (str[i] == '$' && ft_isalnum(str[i + 1]))
		{
			var_name = get_var_name(&str[i + 1]);
			if (!var_name)
				return (NULL);
			replacement_vars = ft_map_find(vars, var_name);
			size = get_replaced_size(str, var_name, replacement_vars);
			str = create_new_str(str, size, replacement_vars, i);
			if (!str)
				return (NULL);
			i = 0;
		}
	}
	return (str);
}
