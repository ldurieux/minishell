/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:56:43 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/12 12:12:39 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"

void	ft_print_var_info(void *var_map)
{
	t_vars	*var;

	var = (t_vars *)var_map;
	if (var->env)
		if (var->value)
			printf("%s=%s\n", var->name, var->value);
}

void	ft_print_env_map(t_ftmap *vars)
{
	ft_map_iter(vars, ft_print_var_info);
}

void	ft_print_shell_info(void *var_map)
{
	printf("%s=%s\n", ((t_vars *)var_map)->name, ((t_vars *)var_map)->value);
}

void	ft_print_shell_map(t_ftmap *vars)
{
	ft_map_iter(vars, ft_print_shell_info);
}
