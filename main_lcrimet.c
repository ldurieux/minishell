/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lcrimet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:13:18 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/11 16:15:29 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifdef LCRIMET
# include "input.h"
# include "exec.h"
# include "vars.h"
# include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	// t_exec	exec;
	t_ftmap	*vars;
	t_node	*cmd_tab;
	char	*cmd;

	(void)argc;
	(void)argv;
	vars = get_vars(envp);
	// exec_init(&exec, ft_vars_to_envp(vars), vars);
	cmd = get_input("minishell > ");
	cmd_tab = parse_shell(cmd);
	if (!cmd_tab)
		return (0);
	cmd_tab[0].str = replace_vars(cmd_tab[0].str, vars);
	cmd_tab[0].str = remove_quotes(cmd_tab[0].str);
	printf("%s\n", cmd_tab[0].str);
	// exec_add_cmd(&exec, cmd_tab[0].str, NULL);
	// exec_run(&exec);
	ft_free_map(vars);
	free_node_tab(cmd_tab, -1);
	free(cmd_tab);
	free(cmd);
	return (0);
}
#endif
