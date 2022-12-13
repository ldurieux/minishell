#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include <errno.h>
# include <string.h>
# include "ft_printf.h"
# include "libft.h"

# define PIPE_IN 1
# define PIPE_OUT 0

typedef struct s_exec	t_exec;
typedef struct s_exec_cmd	t_exec_cmd;

void	run_child(t_exec_cmd *cmd, char *paths, char **envp);

#endif // EXEC_INTERNAL_H
