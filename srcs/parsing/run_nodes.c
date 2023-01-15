/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:36:23 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/12 09:36:26 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	update_ret_code(int ret_code, t_ftmap *vars)
{
	t_vars	*var;

	var = ft_map_find(vars, "?");
	if (!var)
		return (0);
	free(var->value);
	var->value = ft_itoa(ret_code);
	return (var->value != NULL);
}

static int	init_exec(t_exec *exec, t_ftmap *vars, int first)
{
	char	**envp;

	if (g_process_killed == 2)
		update_ret_code(1, vars);
	g_process_killed = 0;
	if (!first)
		exec_destroy(exec);
	envp = ft_vars_to_envp(vars);
	if (!envp)
		return (0);
	return (exec_init(exec, envp, vars));
}

int	run_nodes(t_node *nodes, t_ftmap *vars)
{
	t_exec	exec;
	size_t	idx;
	int		ret_code;

	ret_code = 0;
	idx = (size_t)-1;
	if (!init_exec(&exec, vars, 1))
		return (0);
	while (nodes[++idx].str != NULL)
	{
		if (nodes[idx].type == T_cmd)
		{
			if (!add_exec(&exec, &(nodes + idx)->str, vars))
			{
				if (!g_process_killed)
					continue ;
				exec_destroy(&exec);
				return (update_ret_code(1, vars));
			}
		}
	}
	if (nodes[idx].str == NULL)
		ret_code = exec_run(&exec);
	exec_destroy(&exec);
	return (update_ret_code(ret_code, vars));
}
