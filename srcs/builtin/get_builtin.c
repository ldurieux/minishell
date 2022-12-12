#include "builtin.h"

t_builtin get_builtin(char *name)
{
	if (ft_strcmp(name, "echo") == 0)
		return (main_echo);
	if (ft_strcmp(name, "cd") == 0)
		return (main_cd);
	if (ft_strcmp(name, "pwd") == 0)
		return (main_pwd);
	if (ft_strcmp(name, "export") == 0)
		return (main_export);
	if (ft_strcmp(name, "unset") == 0)
		return (main_unset);
	if (ft_strcmp(name, "env") == 0)
		return (main_env);
	if (ft_strcmp(name, "exit") == 0)
		return (main_exit);
	return (NULL);
}
