/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:47:58 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/12 15:01:38 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <signal.h>
# include <unistd.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <stdlib.h>
# include "exec.h"
# include "exec_internal.h"
# include "libft.h"
# include "ft_vector.h"
# include "ft_frwlist.h"

char	*get_input(char *ps1);
char	*here_doc(char *end_str, char *ps2, t_ftmap *vars);
int		here_doc_fd(char *end_str, char *ps2, t_ftmap *vars);

char	*here_doc_child(char *end_str, char *ps2, int fd, t_ftmap *vars);
char	*here_doc_res(int fd);
char *here_doc_replace_vars(char *str, t_ftmap *vars);

#endif
