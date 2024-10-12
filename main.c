/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:05:21 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/12 20:25:07 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int pipex(t_var *px_var)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	input_fd;
	int	output_fd;
	int	status;
	char	*cmd_path;
	if (pipe(fd) == -1)
		exit_on_error(px_var, "opening pipe error", 0);
	pid1 = fork();
	if (pid1 < 0 )
		exit_on_error(px_var, "fork error", 0);
	if (pid1 == 0) //first child process for 1st command
	{
		input_fd = open(px_var->infile, O_RDONLY);
		if (input_fd < 0)
			exit_on_error(px_var, px_var->infile, 1);
		dup2(input_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(input_fd);
		close(fd[0]);
		close(fd[1]);
		cmd_path = get_command_path(px_var->cmd1[0], px_var->envp);
		if (!cmd_path)
			exit_on_error(px_var, px_var->cmd1[0], 0);
		execve(cmd_path, px_var->cmd1, px_var->envp);
		free(cmd_path);
		exit_on_error(px_var, "execve cmd1 error", 0);
	}
	pid2 = fork();
	if (pid2 < 0)
		exit_on_error(px_var, "fork error", 0);
	if (pid2 == 0) // second child process for 2nd command
	{
		output_fd = open(px_var->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd < 0)
			exit_on_error(px_var, px_var->outfile, 0);
		dup2(fd[0], STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		close(output_fd);
		cmd_path = get_command_path(px_var->cmd2[0], px_var->envp);
		if (!cmd_path)
			exit_on_error(px_var, px_var->cmd2[0], 0);
		execve(cmd_path, px_var->cmd2, px_var->envp);
		free(cmd_path);
		exit_on_error(px_var, "execve cmd2 error", 0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		px_var->exitcode = WEXITSTATUS(status);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		px_var->exitcode = WEXITSTATUS(status);
	return (px_var->exitcode);
}

void	init_variables(char **argv, char **envp, t_var *px_var)
{
	px_var->cmd1 = ft_split(argv[2], ' ');
	px_var->cmd2 = ft_split(argv[3], ' ');
	px_var->infile = argv[1];
	px_var->outfile = argv[4];
	px_var->envp = envp;
	px_var->exitcode = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_var	px_var;

	if (argc != 5)
	{
		write(2, "Params should be: file1 cmd1 cmd2 file2\n", 40);
		return (1);
	}
	init_variables(argv, envp, &px_var);
	if (!px_var.cmd1 || !px_var.cmd2)
		exit_on_error(&px_var, "Command not found", 0);
	pipex(&px_var);
	free_array(px_var.cmd1);
	free_array(px_var.cmd2);
	return (px_var.exitcode);
}
