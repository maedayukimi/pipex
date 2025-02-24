#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

char	**ft_split(const char *str, char c);

int	main()
{
	int	fd;
	pid_t	pid;

	fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		printf("the cake is a lie!\n");
		execve("/bin/man", ft_split("/bin/man atoi", ' '), NULL);
	}
	else
	{
		wait(NULL);
		printf("THE CAKE IS A LIE!\n");
	}
	return (0);
}
