/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:19 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:03:20 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	export(t_ftmap *vars, char *name)
{
	t_vars	*var;

	var = ft_map_find(vars, name);
	if (var)
		var->env = ENV;
	else
	{
		var = malloc(sizeof(t_vars));
		if (!var)
			return ;
		var->name = name;
		var->env = ENV;
		var->value = NULL;
		if (!ft_map_insert(vars, name, var))
			free(var);
	}
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
