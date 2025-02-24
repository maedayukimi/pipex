/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:07:55 by mawako            #+#    #+#             */
/*   Updated: 2025/02/24 01:07:58 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	help_msg(void)
{
	ft_putendl_fd("This is Pipex", 1);
	ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 1);
	ft_putendl_fd("The outfile will be created/truncated if needed.", 1);
	ft_putendl_fd("Example:", 1);
	ft_putendl_fd("  ./pipex infile \"cat\" \"wc -l\" outfile", 1);
	exit(EXIT_FAILURE);
}

void	exit_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}
