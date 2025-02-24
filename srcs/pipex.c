/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:04:57 by mawako            #+#    #+#             */
/*   Updated: 2025/02/24 12:49:15 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **av, char **env, int *fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		exit_msg("Failed to open infile.");
	if (dup2(infile, STDIN_FILENO) < 0)
		exit_msg("Failed dup2 (infile -> STDIN).");
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		exit_msg("Failed dup2 (pipe write -> STDOUT).");
	close(fd[0]);
	close(fd[1]);
	close(infile);
	if (px_execve(av[2], env) == 1)
		exit_msg("Child process:\tCommand not found.");
	if (px_execve(av[2], env) == -1)
		exit_msg("Child process:\tFailed to execve.");
}

void	parent_process(char **av, char **env, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		exit_msg("Failed to open outfile.");
	if (dup2(outfile, STDOUT_FILENO) < 0)
		exit_msg("Failed dup2 (outfile -> STDOUT).");
	if (dup2(fd[0], STDIN_FILENO) < 0)
		exit_msg("Failed dup2 (pipe read -> STDIN).");
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	if (px_execve(av[3], env) == 1)
		exit_msg("Parent process:\tCommand not found.");
	if (px_execve(av[3], env) == -1)
		exit_msg("Parent process:\tFailed to execve.");
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			exit_msg("Failed to create pipe.");
		pid = fork();
		if (pid < 0)
			exit_msg("Failed to fork.");
		if (pid == 0)
			child_process(av, env, fd);
		waitpid(pid, NULL, 0);
		parent_process(av, env, fd);
	}
	else
		help_msg();
	return (0);
}
