/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:59:02 by jmorneau          #+#    #+#             */
/*   Updated: 2022/11/23 00:05:39 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	execute_final(t_pipe *pipex)
{
	close(pipex->fd[1]);
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->file_close, STDOUT_FILENO);
	close(pipex->file_close);
	if (execve(pipex->path_to_command, pipex->argv, pipex->env) == -1)
	{
		print_ncmd(pipex->path_to_command);
		exit (1);
	}
	exit (0);
}

static int	execute_first(t_pipe *pipex)
{
	int	fd;

	fd = pipex->file_open;
	close(pipex->fd[0]);
	dup2(pipex->file_open, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->file_open);
	if (fd)
	{
		if (execve(pipex->path_to_command, pipex->argv, pipex->env) == -1)
		{
			print_ncmd(pipex->path_to_command);
			exit (1);
		}
	}
	exit (0);
}

void	*exec_cmd(t_pipe *pipex, int nb_cmd, int argc)
{
	pid_t	id;

	if (!pipex->path_to_command && pipex->argv[0])
		pipex->path_to_command = ft_strdup(pipex->argv[0]);
	id = fork();
	if (id == -1)
		return (print_error());
	if (id == 0)
	{
		if (nb_cmd == 2)
			execute_first(pipex);
		else if (nb_cmd == 3)
			execute_final(pipex);
	}
	if (nb_cmd == 2)
		close(pipex->file_open);
	else if (nb_cmd == argc - 2)
	{
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		close(pipex->file_close);
	}
	waitpid(id, NULL, 0);
	return (0);
}
