#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int	fd;
	char	buffer[100];

	if (ac == 1)
	{
		perror("text")
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open failed");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	buffer[99] = '\0';
	printf("Read from input.txt: %s\n", buffer);
	return (0);
}
