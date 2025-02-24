/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:46:44 by mawako            #+#    #+#             */
/*   Updated: 2025/02/21 18:46:58 by mawako           ###   ########.fr       */
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
		{
			printf("%s\n", path_out + 5);
			return (path_out + 5);
		}
		path++;
	}
	printf("PATH not found.\n");
	return (0);
}

void	check_path(char **env, char *add_cmd, char *cmd)
{
	char	**path;
	char	*path_all;
	char	**save;
	char	*full_cmd;

	path_all = find_path(env);
	if (!path_all)
	{
		printf("PATH not found. using default PATH.\n");
		path_all = "/usr/bin:/bin";
	}
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

int	main(int ac, char **av, char **env)
{
	char	buffer[4242];
	char	**split;
	char	*add_cmd;

	if (ac < 2)
		exit_msg("Enter command to check.");
	add_cmd = ft_strjoin("/", av[1]);
	check_path(env, add_cmd, av[1]);
	free(add_cmd);
	printf("test finished.\n");
	return (0);
}
