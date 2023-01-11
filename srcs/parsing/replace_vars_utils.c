/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:05:13 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/11 13:07:32 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_var_name(char *str)
{
	char	*var_name;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i] && ft_isalnum(str[i]))
	{
		i++;
		size++;
	}
	var_name = malloc(sizeof(char) * (size + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (str[i] && ft_isalnum(str[i]))
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = 0;
	return (var_name);
}

int	get_replaced_size(char *str, char *var_name, t_vars	*replacement_vars)
{
	int		size;

	size = ft_strlen(str);
	size -= ft_strlen(var_name);
	size--;
	if (replacement_vars)
		size += ft_strlen(replacement_vars->value);
	return (size);
}

static void	add_replaced_var(t_vars *replacement_vars, int *i, char *new_str)
{
	int	j;

	j = 0;
	if (replacement_vars)
	{
		while (replacement_vars->value[j])
		{
			new_str[*i] = replacement_vars->value[j];
			(*i)++;
			j++;
		}
	}
}

char	*create_new_str(char *str, int size, t_vars *replacement_vars,
						int start)
{
	char	*new_str;
	int		i;
	int		skip;

	i = -1;
	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	while (++i < start)
		new_str[i] = str[i];
	skip = i + 1;
	add_replaced_var(replacement_vars, &i, new_str);
	while (ft_isalnum(str[skip]))
		skip++;
	while (str[skip])
	{
		new_str[i] = str[skip];
		i++;
		skip++;
	}
	new_str[i] = 0;
	free(str);
	return (new_str);
}
