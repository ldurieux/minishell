/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:13:26 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/13 11:27:02 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"

static void	*create_var(void *ptr)
{
	t_vars	*vars;
	char	*str;
	char	**tab;

	vars = (t_vars *)ptr;
	tab = malloc(sizeof(char *) * 3);
	tab[2] = NULL;
	tab[0] = vars->name;
	tab[1] = vars->value;
	str = ft_strjoin_r(tab, "=");
	return (str);
}

char	**ft_vars_to_envp(t_ftmap *vars)
{
	char	**envp;

	envp = ft_map_to_array(vars, create_var);
	return (envp);
}
