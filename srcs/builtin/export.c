/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:19 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/12 12:08:28 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	export_free_var_tab(char **tab, char *is_equal)
{
	free(tab[0]);
	free(tab[1]);
	if (is_equal)
		free(tab[2]);
	free(tab);
}

static void	export(t_ftmap *vars, char *name)
{
	t_vars	*var;
	char	**tab;
	char	*is_equal;

	is_equal = ft_strchr(name, '=');
	tab = ft_split(name, '=');
	if (!tab)
		return ;
	var = ft_map_find(vars, tab[0]);
	if (!var)
	{
		var = malloc(sizeof(t_vars));
		if (!var)
			return ;
		var->name = ft_strdup(tab[0]);
		if (is_equal)
			var->value = ft_strdup(tab[1]);
		else
			var->value = NULL;
		export_free_var_tab(tab, is_equal);
		if (!ft_map_insert(vars, var->name, var))
			free(var);
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
