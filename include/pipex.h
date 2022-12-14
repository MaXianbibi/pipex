/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:40:03 by jmorneau          #+#    #+#             */
/*   Updated: 2022/11/22 21:08:04 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_pipe
{
	int		fd[2];
	char	**env;
	char	**argv;
	char	*path_to_command;
	int		file_open;
	int		file_close;
}	t_pipe;

char	*find(char **envp, char *cmd);
char	**final_cmd(char **arg, char *read_file);
void	*exec_cmd(t_pipe *pipex, int nb_cmd, int argc);
void	*print_error(void);
int		print_error_int(void);
int		print_arg(int n);
void	*print_ncmd(char *cmd);
char	*find_path_line(char **envp);

#endif