/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:45:25 by mawako            #+#    #+#             */
/*   Updated: 2025/02/10 14:34:17 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int	fd;
	char	buffer[100];
	ssize_t	bytes_read;

	if (ac < 3 || (strcmp(av[1], "write") == 0 && ac < 4))
	{
		printf("add read or write after ELF\n");
		return (0);
	}
	if (strcmp(av[1], "read") == 0)
	{
		fd = open(av[2], O_RDONLY);
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		buffer[bytes_read] = '\0';
		printf("This is %s:\n%s\n", av[2], buffer);
		close(fd);
	}
	else if (strcmp(av[1], "write") == 0)
	{
		fd = open(av[2], O_RDWR | O_CREAT, 0644);
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		buffer[bytes_read] = '\0';
		printf("This is %s before writing:\n%s\n", av[2], buffer);
		close(fd);
		printf("Adding text...\n");
		fd = open(av[2], O_WRONLY | O_APPEND);
		write(fd, av[3], strlen(av[3]));
		close(fd);
		fd = open(av[2], O_RDONLY);
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		buffer[bytes_read] = '\0';
		printf("This is %s after writing:\n%s\n", av[2], buffer);
		close(fd);
	}
	else if (strcmp(av[1], "delete") == 0)
	{
		fd = open(av[2], O_WRONLY | O_TRUNC);
		close(fd);
		printf("File has been cleaned.\n");
	}
	else if (strcmp(av[1], "DELETE") == 0)
	{
		unlink(av[2]);
		printf("File deleted.\n");
	}
	else
		printf("Invalid option. Use 'read' or 'write'.\n");
	printf("finished test");
	return (0);
}
