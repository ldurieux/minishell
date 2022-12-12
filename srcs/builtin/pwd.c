/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:23 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:03:24 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#define BUF_SIZE 2048

int	main_pwd(int argc, char **argv, char **envp)
{
	char	buf[BUF_SIZE];

	(void)argc;
	(void)argv;
	(void)envp;
	ft_printf("%s\n", getcwd(buf, BUF_SIZE - 1));
	return (0);
}
