/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:35:38 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/13 11:01:41 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"

static void	ft_free_var(void *var)
{
	free(((t_vars *)var)->name);
	free(var);
}

void	ft_free_map(t_ftmap *vars)
{
	ft_map_iter(vars, ft_free_var);
	ft_map_delete(vars);
}

static t_vars	*ft_fill_map_val(char *envp)
{
	t_vars	*map_val;

	map_val = malloc(sizeof(t_vars));
	if (!map_val)
		return (NULL);
	map_val->name = ft_strtok_r((const char *)envp, "=",
			(const char **)&map_val->value);
	if (!map_val->name || !*map_val->value)
	{
		free(map_val->name);
		free(map_val);
		return (NULL);
	}
	map_val->value++;
	map_val->env = 1;
	return (map_val);
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
	{
		free(map_val->name);
		free(map_val);
		return (NULL);
	}
	map_val->value++;
	map_val->env = env;
	if (!ft_map_insert(vars, map_val->name, map_val))
		return (ft_free_map(vars), NULL);
	return (vars);
}

t_ftmap	*get_vars(char **envp)
{
	int		i;
	t_ftmap	*vars;
	t_vars	*map_val;

	i = 0;
	vars = ft_map_new(256);
	if (!vars)
		return (0);
	while (envp && envp[i])
	{
		map_val = ft_fill_map_val(envp[i]);
		if (!map_val)
			return (ft_free_map(vars), NULL);
		if (!ft_map_insert(vars, map_val->name, map_val))
			return (ft_free_map(vars), NULL);
		i++;
	}
	return (vars);
}
