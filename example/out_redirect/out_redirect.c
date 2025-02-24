#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int	fd;

	if (ac < 2)
	{
		printf("writing failed.\n");
		return (0);
	}
	fd = open(av[1], O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open failed");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("%s\n", av[2]);
	return (0);
}
