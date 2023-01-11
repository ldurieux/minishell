/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:05:13 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/11 16:08:00 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_var_name(char *str)
{
	size_t	i;

	if (str[0] == '?')
		return (ft_strdup("?"));
	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	return (ft_strndup(str, i));
}

size_t	get_replaced_size(char *str, char *var_name, t_vars	*replacement_vars)
{
	size_t	size;

	size = ft_strlen(str);
	size -= ft_strlen(var_name);
	size--;
	if (replacement_vars)
		size += ft_strlen(replacement_vars->value);
	return (size);
}

char	*create_new_str(char *str, int size, t_vars *replacement_vars,
						int start)
{
	char	*new_str;
	size_t	skip;

	new_str = ft_calloc(sizeof(char), (size + 1));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, start);
	if (replacement_vars)
		ft_strcat(new_str, replacement_vars->value);
	skip = start + 1;
	if (str[skip] == '?')
		skip++;
	else
		while (ft_isalnum(str[skip]))
			skip++;
	ft_strcat(new_str, str + skip);
	free(str);
	return (new_str);
}
