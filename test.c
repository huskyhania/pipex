/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:05:09 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/27 14:08:15 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	int	fd[2];
	int	id;
	pipe(fd);
	if (pipe(fd) == -1)
		return (printf("error creating a pipe"));
	id = fork();
	if (id == -1)
		return (printf("error forking"));
	if (id == 0)
	{
		close(fd[0]);
		int	x;
		printf("Input a number: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
			return (printf("error writing\n"));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int	y;
		if (read(fd[0], &y, sizeof(int)) == -1)
			return (printf("error reading\n"));
		close(fd[0]);
		printf("got from child process %d\n", y);
	}
	return (0);
}
