/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:46:44 by mawako            #+#    #+#             */
/*   Updated: 2025/02/21 03:08:05 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	**null_split(const char *b, size_t l);
void	free_array(char **arr, size_t used);

void	exit_msg(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*find_path(char **env)
{
	char	**path;
	char	*path_out;

	path = env;
	while (*path)
	{
		path_out = ft_strnstr(*path, "PATH=", ft_strlen(*path));
		if (path_out)
			return (path_out + 5);
		path++;
	}
	return (0);
}

void	check_path(char **split, char *add_cmd, char *cmd)
{
	char	**path;
	char	*path_all;
	char	**save;
	char	*full_cmd;

	path_all = find_path(split);
	if (!path_all)
		exit_msg("PATH not found.");
	path = ft_split(path_all, ':');
	if (!path)
		exit_msg("Failed to split PATH.");
	save = path;
	while (*path)
	{
		full_cmd = ft_strjoin(*path, add_cmd);
		if (access(full_cmd, X_OK) == 0)
		{
			printf("%s is available!\n", cmd);
			free(full_cmd);
			return ;
		}
		free(full_cmd);
		path++;
	}
	printf("%s is unavailable.\n", cmd);
	free_split(save);
}

int	main(int ac, char **av)
{
	int		fd;
	char	buffer[4242];
	ssize_t	bytes_read;
	char	**split;
	char	*add_cmd;

	if (ac < 2)
		exit_msg("Enter command to check.");
	fd = open("/proc/self/environ", O_RDONLY);
	bytes_read = read(fd, buffer, 4242 - 1);
	close(fd);
	if (bytes_read < 0)
		exit_msg("Failed read file descriptor.");
	buffer[bytes_read] = '\0';
	split = null_split(buffer, bytes_read);
	if (!split)
		exit_msg("Failed to split environ.");
	add_cmd = ft_strjoin("/", av[1]);
	check_path(split, add_cmd, av[1]);
	free_split(split);
	free(add_cmd);
	printf("test finished.\n");
	return (0);
}
