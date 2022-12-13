/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:56:43 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/13 11:00:14 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"

void	ft_print_var_info(void *var_map)
{
	if (((t_vars *)var_map)->env)
		printf("%s=%s\n", ((t_vars *)var_map)->name, ((t_vars *)var_map)->value);
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
