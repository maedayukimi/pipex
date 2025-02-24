#include <unistd.h>
#include <stdio.h>

char	*find_path(void)
{
	int	fd;
	char	*buffer;
	ssize_t	bytes_read;
	char	*path_start;

	fd = open("/proc/self/environ", O_RDONLY);
	if (fd < 0)
		return (NULL);
	buffer = malloc(8192);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, 8192 - 1);
	close(fd);
	if (bites_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	path_start = strstr(buffer, "PATH=");
	if (!path_start)
	{
		free(buffer);
		return (NULL);
	}
	path_start += 5;
	return (strdup(path_start));
}

char	*get_path(char *cmd)
{
	char	*path;
	char	*token;
	char	full_path[1024];

	path = find_path();
	if (!path)
		return (NULL);

int	main(int ac, char **av)
{
	int	n;

	n = 1;
	if (ac < 2)
	{
		printf("Enter commands.\n");
		return (1);
	}
	while (n < ac)
	{
		if (access(av[n], X_OK) == 0)
			printf("%s is exist command.\n", av[n]);
		else
			printf("%s is not exist command.\n", av[n]);
		n++;
	}
	printf("test finished\n");
	return (0);
}
