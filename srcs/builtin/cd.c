/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:07 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:03:10 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#define HOME_STR "HOME="
#define HOME_STR_LEN 5

static char	*get_home(char **envp)
{
	size_t	idx;

	if (!envp)
		return (NULL);
	idx = (size_t)-1;
	while (envp[++idx])
		if (ft_strncmp(envp[idx], HOME_STR, HOME_STR_LEN) == 0)
			break ;
	if (envp[idx])
		return (envp[idx] + HOME_STR_LEN);
	return (NULL);
}

static char	*get_tilde(char **envp, char *next)
{
	char	*home;

	home = get_home(envp);
	if (!home)
		return (NULL);
	if (!next[0])
		return (ft_strdup(home));
	return (ft_strjoin(home, next));
}

static int	cd_error(char *error)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, "cd", error);
	return (1);
}

int	main_cd(int argc, char **argv, char **envp, t_ftmap *vars)
{
	char	*path;

	(void)vars;
	path = NULL;
	if (argc > 2)
		return (cd_error("too many arguments"));
	if (argc < 2)
		path = ft_strdup(get_home(envp));
	else if (argv[1][0] == '~')
		path = get_tilde(envp, argv[1] + 1);
	else
		path = ft_strdup(argv[1]);
	if (!path)
		return (cd_error("HOME not set"));
	if (chdir(path) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", "cd", strerror(errno), path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}
