/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:05:24 by mawako            #+#    #+#             */
/*   Updated: 2025/02/24 20:17:10 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*find_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (!ft_strncmp(path[i], "PATH=", 5))
			return (path[i] + 5);
		i++;
	}
	return (NULL);
}

char	*check_path(char *cmd, char **env)
{
	char	**path;
	char	**save;
	char	*path_all;
	char	*tmp;
	char	*full_cmd;

	path_all = find_path(env);
	if (!path_all)
		exit_msg("PATH not found.");
	path = ft_split(path_all, ':');
	if (!path)
		exit_msg("Failed to split PATH.");
	save = path;
	while (*path)
	{
		tmp = ft_strjoin("/", cmd);
		full_cmd = ft_strjoin(*path, tmp);
		free(tmp);
		if (access(full_cmd, X_OK) == 0)
			return (free_split(save), full_cmd);
		free(full_cmd);
		path++;
	}
	return (free_split(save), NULL);
}

int	px_execve(char *cmd_all, char **env)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(cmd_all, ' ');
	if (!cmds)
		exit_msg("Failed to split command.");
	if (cmds[0][0] == '/' || cmds[0][0] == '.')
	{
		if (access(cmds[0], X_OK) == 0)
			path = ft_strdup(cmds[0]);
		else
			return (1);
	}
	else
		path = check_path(cmds[0], env);
	if (!path)
	{
		free_split(cmds);
		return (1);
	}
	if (execve(path, cmds, env) == -1)
		return (-1);
	return (0);
}
