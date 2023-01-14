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
#include "input.h"
#include "parsing.h"

static int	init_ret_code(t_ftmap *vars)
{
	t_vars	*var;

	var = ft_map_remove(vars, "?");
	if (var)
	{
		free(var->name);
		free(var->value);
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

static int	init_shell_lvl(t_ftmap *vars)
{
	t_vars	*var;
	int		shlvl;

	var = ft_map_find(vars, "SHLVL");
	if (!var)
	{
		var = malloc(sizeof(t_vars));
		if (!var)
			return (0);
		var->name = ft_strdup("SHLVL");
		var->value = ft_strdup("1");
		var->env = ENV;
		if (!var->name || !var->value || !ft_map_insert(vars, var->name, var))
			return (free(var->name), free(var->value), free(var), 0);
		return (1);
	}
	shlvl = ft_atoi(var->value);
	if (shlvl < 0)
		shlvl = -1;
	if (shlvl >= 999)
		shlvl = 0;
	free(var->value);
	var->value = ft_itoa(shlvl + 1);
	return (var->value != NULL);
}

static int	init_vars(t_ftmap *vars)
{
	if (!init_ret_code(vars))
		return (0);
	if (!init_shell_lvl(vars))
		return (0);
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
