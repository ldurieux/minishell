/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:21:51 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/13 15:22:07 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"

static int	ft_find(t_ftmap *vars, t_vars *map_val)
{
	t_vars	*find;

	find = ft_map_find(vars, map_val->name);
	if (!find)
	{
		if (!ft_map_insert(vars, map_val->name, map_val))
			return (ft_free_map(vars), 0);
	}
	else
	{
		free(map_val->name);
		find->value = map_val->value;
		find->env = (find->env || map_val->env);
		free(map_val);
	}
	return (1);
}

t_ftmap	*ft_add_var(char *envp, uint8_t env, t_ftmap *vars)
{
	t_vars	*map_val;

	map_val = malloc(sizeof(t_vars));
	if (!map_val)
		return (NULL);
	map_val->name = ft_strtok_r((const char *)envp, "=",
			(const char **)&map_val->value);
	if (!map_val->name || !*map_val->value)
		return (free(map_val->name), free(map_val), NULL);
	map_val->value++;
	map_val->env = env;
	if (!ft_find(vars, map_val))
		return (0);
	return (vars);
}
