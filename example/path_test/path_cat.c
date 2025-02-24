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

void	*find_path(char **split)
{
	char	**path;
	char	*path_out;

	path = split;
	while (*path)
	{
		path_out = ft_strnstr(*path, "PATH=", ft_strlen(*path));
		if (path_out)
			printf("%s\n", path_out + 5);
		path++;
	}
	//return (path_out + 5);
}

int	main(int ac, char **av)
{
	int	fd;
	char	buffer[4242];
	ssize_t	bytes_read;
	char	**split;

	if (ac < 2)
		exit_msg("Enter command to check.");
	fd = open("/proc/self/environ", O_RDONLY);
	bytes_read = read(fd, buffer, 4242 - 1);
	close(fd);
	if (bytes_read < 0)
		exit_msg("Failed read file descriptor.");
	buffer[bytes_read] = '\0';
	split = null_split(buffer, bytes_read);
	find_path(split);
	free_split(split);
	return (0);
}
