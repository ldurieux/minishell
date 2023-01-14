/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:51:32 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/14 12:51:33 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	*make_entry(void *ptr)
{
	t_vars	*vars;
	char	*str;
	char	*tab[5];

	vars = (t_vars *)ptr;
	if (!vars->value)
		return (ft_strdup(vars->name));
	tab[0] = ft_strjoin(vars->name, "=");
	tab[1] = "\"";
	tab[2] = vars->value;
	tab[3] = "\"";
	tab[4] = NULL;
	str = ft_strjoin_r(tab, "");
	return (str);
}

static void	sort_array(char **tab, size_t size)
{
	int		again;
	size_t	i;
	char	*tmp;

	again = 1;
	while (again)
	{
		again = 0;
		i = (size_t) - 1;
		while (++i < size - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				again = 1;
			}
		}
	}
}

void	export_no_args(t_ftmap *vars)
{
	char	**array;
	size_t	idx;

	array = ft_map_to_array(vars, make_entry);
	if (!array)
		return ;
	sort_array(array, vars->size);
	idx = (size_t)-1;
	while (array[++idx])
		ft_printf("declare -x %s\n", array[idx]);
}
