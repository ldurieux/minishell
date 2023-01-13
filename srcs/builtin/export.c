/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:19 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/13 10:11:42 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_name(char *name)
{
	if (ft_strchr(name, '?'))
	{
		ft_dprintf(STDERR_FILENO, "%s: export: `%s': not a valid identifier\n",
			NAME, name);
		return (1);
	}
	return (0);
}

static void	export(t_ftmap *vars, char *name)
{
	t_vars		*var;
	const char	*value;

	name = ft_strtok_r(name, "=", &value);
	if (!name || check_name(name))
		return ;
	var = ft_map_find(vars, name);
	if (!var)
	{
		var = malloc(sizeof(t_vars));
		if (!var)
			return ;
		var->name = name;
		var->value = NULL;
		if (value[0])
			var->value = ft_strdup(value + 1);
		if (!ft_map_insert(vars, var->name, var))
			free(var);
	}
	else if (value[0])
	{
		free(var->value);
		var->value = ft_strdup(value + 1);
	}
	var->env = ENV;
}

int	main_export(int argc, char **argv, char **envp, t_ftmap *vars)
{
	int	idx;

	(void)envp;
	idx = 0;
	while (++idx < argc)
		export(vars, argv[idx]);
	return (0);
}
