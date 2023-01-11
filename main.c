/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:13:18 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 16:31:51 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"
#include "exec.h"
#include "input.h"
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

static int	run_nodes(t_node *nodes, t_ftmap *vars)
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

static int	init_vars(t_ftmap *vars)
{
	t_vars	*var;

	var = ft_map_remove(vars, "?");
	if (var)
	{
		free(var->name);
		free(var);
	}
	var = malloc(sizeof(t_vars));
	if (!var)
		return (0);
	var->name = ft_strdup("?");
	var->value = ft_strdup("0");
	var->env = SHELL;
	if (!var->name || !var->value)
		return (free(var->name), free(var->value), free(var), 0);
	if (!ft_map_insert(vars, var->name, var))
		return (free(var->name), free(var->value), free(var), 0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_ftmap	*vars;
	char	*input;
	t_node	*parse_nodes;

	(void)argc;
	(void)argv;
	vars = get_vars(envp);
	if (!vars || !init_vars(vars))
		return (ft_free_map(vars), 1);
	while (1)
	{
		input = get_input("minishell > ");
		if (!input || !input[0])
			continue ;
		parse_nodes = parse_shell(input);
		if (!parse_nodes || !parse_nodes[0].str)
			free_node_tab(parse_nodes, -1);
		if (!parse_nodes || !parse_nodes[0].str)
			continue ;
		if (!run_nodes(parse_nodes, vars))
			break ;
		free(input);
		free_node_tab(parse_nodes, -1);
	}
	return (ft_free_map(vars), free_node_tab(parse_nodes, -1), 0);
}
