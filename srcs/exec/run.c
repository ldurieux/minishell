/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:06:26 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/11 10:06:28 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_internal.h"

int	exec_run(t_exec *exec)
{
	int	res;

	res = 0;
	if (exec->cmds->size < 2)
		exec->flags &= ~Exec_Pipe;

	return (res);
}
