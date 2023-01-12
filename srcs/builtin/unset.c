/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:25 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/12 11:01:48 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	unset(t_ftmap *vars, char *name)
{
	t_vars	*var;

	if (ft_strchr(name, '?'))
	{
		ft_dprintf(STDERR_FILENO, "%s: unset: `%s': not a valid identifier\n",
			NAME, name);
		return ;
	}
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
