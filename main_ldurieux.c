/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:13:18 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/09 22:13:20 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifdef LDURIEUX

#include "exec.h"
#include "ft_printf.h"
#include <fcntl.h>

int	main(int argc, char **argv, char **envp)
{
	t_exec		exec;
	t_exec_cmd	*cmd;
	int			ret_code;

	(void)argc;
	(void)argv;
	exec_init(&exec, envp);
	cmd = exec_add_cmd(&exec, ft_strdup("ls"), NULL);
	cmd->redir_out = open("test.txt", O_WRONLY | O_CREAT, 0644);
	ft_printf("before\n");
	ret_code = exec_run(&exec);
	ft_printf("after\n");
	exec_destroy(&exec);
	return (ret_code);
}
#endif
