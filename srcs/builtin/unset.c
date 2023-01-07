/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:25 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:03:26 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	unset(t_ftmap *vars, char *name)
{
	t_vars	*var;

	var = ft_map_remove(vars, name);
	if (!var)
		return ;
	free(var->name);
}

int	main_unset(int argc, char **argv, char **envp, t_ftmap *vars)
{
	int	idx;

	(void)envp;
	idx = 0;
	while (++idx < argc)
		unset(vars, argv[idx]);
	return (0);
}
