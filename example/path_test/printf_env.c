#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void	exit_msg(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	char	**save;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
