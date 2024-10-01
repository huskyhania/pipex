/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:05:21 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/01 19:12:18 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int pipex(int argc, char **argv)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0) //first child process for 1st command
	{
		dup2(fd[1], fileNUMBER);
		close(fd[0]);
		close(fd[1]);
		execve (first command);
		int err0 = errno;
		printf("%d\n", err0);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0) // second child process for 2nd command
	{
		dup2(fd[0], filleNUMBER2);
		close(fd[0]);
		close(fd[1]);
		execve (second command);
		int err = errno;
		printf("%d\n", err);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 5)
		pipex(argc, argv);
	else
		ft_printf("wrong argument count\n");
	return (0);
}
