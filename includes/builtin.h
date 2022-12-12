#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"

typedef int (*t_builtin)(int, char **, char **);

t_builtin	get_builtin(char *name);

int			main_echo(int argc, char **argv, char **envp);
int			main_cd(int argc, char **argv, char **envp);
int			main_pwd(int argc, char **argv, char **envp);
int			main_export(int argc, char **argv, char **envp);
int			main_unset(int argc, char **argv, char **envp);
int			main_env(int argc, char **argv, char **envp);
int			main_exit(int argc, char **argv, char **envp);

#endif // BUILTIN_H
