/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:05:21 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/01 20:41:55 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int pipex(char *file1, char *cmd1[], char *cmd2[], char *file2)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	input_fd;
	int	output_fd;

	if (pipe(fd) == -1)
	{
		perror("opening pipe error\n");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork error\n");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0) //first child process for 1st command
	{
		input_fd = open(file1, O_RDONLY);
		if (input_fd < 0)
		{
			perror("file1 open error\n");
			exit(EXIT_FAILURE);
		}
		dup2(input_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(input_fd);
		execve(cmd1[0], cmd1, NULL);
		perror("execve cmd1 error\n");
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("2nd fork error\n");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0) // second child process for 2nd command
	{
		output_fd = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd < 0)
		{
			perror("file2 open error\n");
			exit(EXIT_FAILURE);
		}
		dup2(fd[0], STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		close(output_fd);
		execve(cmd2[0], cmd2, NULL);
		perror("execve cmd2 error\n");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		write(2, "Params should be: file1 cmd1 cmd2 file2\n", 40);
		return (1);
	}
	char *cmd1[] = {argv[2], NULL};
	char *cmd2[] = {argv[3], NULL};
	pipex(argv[1], cmd1, cmd2, argv[4]);
	return (0);
}
