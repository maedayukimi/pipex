/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:04:57 by mawako            #+#    #+#             */
/*   Updated: 2025/02/24 19:01:37 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	wait_children(int fd[2], pid_t pid1, pid_t pid2)
{
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

static void	command1(char **av, char **env, int fd[2])
{
	int	infile;
	int	err;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		exit_msg("Failed to open infile.");
	if (dup2(infile, STDIN_FILENO) < 0)
		exit_msg("Failed dup2 (infile -> STDIN).");
	close(infile);
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		exit_msg("Failed dup2 (pipe write -> STDOUT).");
	close(fd[1]);
	err = px_execve(av[2], env);
	if (err == 1)
		exit_msg("Command1:\tCommand not found.");
	else if (err == -1)
		exit_msg("Command1:\tFailed to execve.");
	exit(EXIT_FAILURE);
}

static void	command2(char **av, char **env, int fd[2])
{
	int	outfile;
	int	err;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		exit_msg("Failed to open outfile.");
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		exit_msg("Failed dup2 (pipe read -> STDIN).");
	close(fd[0]);
	if (dup2(outfile, STDOUT_FILENO) < 0)
		exit_msg("Failed dup2 (outfile -> STDOUT).");
	close(outfile);
	err = px_execve(av[3], env);
	if (err == 1)
		exit_msg("Command2:\tCommand not found.");
	else if (err == -1)
		exit_msg("Command2:\tFailed to execve.");
	exit(EXIT_FAILURE);
}

static void	check_arguments(char **av)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (!av[i] || !*av[i])
		{
			exit_msg("Invalid arguments.");
		}
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		help_msg();
	check_arguments(av);
	if (pipe(fd) == -1)
		exit_msg("Failed to create pipe.");
	pid1 = fork();
	if (pid1 < 0)
		exit_msg("Command1:\tFailed to fork.");
	if (pid1 == 0)
		command1(av, env, fd);
	pid2 = fork();
	if (pid2 < 0)
		exit_msg("Command2:\tFailed to fork.");
	if (pid2 == 0)
		command2(av, env, fd);
	wait_children(fd, pid1, pid2);
	return (0);
}
