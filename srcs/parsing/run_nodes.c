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

static int	init_exec(t_exec *exec, t_ftmap *vars, int first)
{
	char	**envp;

	if (!first)
		exec_destroy(exec);
	envp = ft_vars_to_envp(vars);
	if (!envp)
		return (0);
	return (exec_init(exec, envp, vars));
}

static int	update_ret_code(int ret_code, t_ftmap *vars)
{
	t_vars	*var;

	var = ft_map_find(vars, "?");
	free(var->value);
	var->value = ft_itoa(ret_code);
	return (var->value != NULL);
}

int	run_nodes(t_node *nodes, t_ftmap *vars)
{
	t_exec	exec;
	size_t	idx;
	int		ret_code;

	idx = (size_t)-1;
	if (!init_exec(&exec, vars, 1))
		return (0);
	while (nodes[++idx].str != NULL)
	{
		if (nodes[idx].type != T_cmd && nodes[idx].type != T_pipe)
		{
			ret_code = exec_run(&exec);
			if ((ret_code && nodes[idx].type == T_and)
				|| (!ret_code && nodes[idx].type == T_or))
				break ;
			if (!init_exec(&exec, vars, 0))
				return (0);
		}
		else if (nodes[idx].type != T_pipe)
			add_exec(&exec, &(nodes + idx)->str, vars);
	}
	if (nodes[idx].str == NULL)
		ret_code = exec_run(&exec);
	exec_destroy(&exec);
	return (update_ret_code(ret_code, vars));
}
