/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:03:04 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/22 19:08:25 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>// DELETE MEEEE

// Function redirect input to stdin and output to stdout
//closes fds, calls get cmd path and executes a command, cleans up if exec fails
void	execute_command(t_var *px, int input_fd, int output_fd, char **cmd)
{
	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(input_fd);
	close(output_fd);
	px->cmd_path = get_command_path(cmd[0], px);
	if (px->cmd_path)
		execve(px->cmd_path, cmd, px->envp);
	free(px->cmd_path);
	clean_up(px);
}

// Function to execute command for the first child, 
// closes unused read end of the pipe, passes input, 
// output and command to execute command
void	handle_first_child(t_var *px, int fd[2])
{
	if (px->input_fd < 0)
	{
		close(fd[1]);
		close(fd[0]);
		free_array(&px->cmd1);
		exit(0);
	}
	close(fd[0]);
	execute_command(px, px->input_fd, fd[1], px->cmd1);
	if (px->cmd1)
		free_array(&px->cmd1);
	exit(px->exitcode);
}

// Function to execute command for the second child, 
// closes unused write end of the pipe
// passes input, output and command to execute command
void	handle_second_child(t_var *px, int fd[2])
{
	close(fd[1]);
	if (px->output_fd < 0)
	{
		close(fd[0]);
		if (px->cmd_path)
		{
			free(px->cmd_path);
			px->cmd_path = NULL;
		}
		if (px->cmd2)
		{
			free_array(&px->cmd2);
			px->cmd2 = NULL;
		}
		px->exitcode = 1;
		exit (1);
	}
	execute_command(px, fd[0], px->output_fd, px->cmd2);
	if (px->cmd2)
		free_array(&px->cmd2);
	exit(px->exitcode);
}

// Function to wait for both child processes and set the exit code
void	wait_for_processes(t_var *px_var, int pid1, int pid2)
{
	int	status;

	if (pid1 > 0)
	{
		waitpid(pid1, &status, 0);
		if (WIFEXITED(status))
			px_var->exitcode = WEXITSTATUS(status);
	}
	if (pid2 > 0)
	{
		waitpid(pid2, &status, 0);
		if (WIFEXITED(status))
			px_var->exitcode = WEXITSTATUS(status);
	}
}

// Function opens a pipe, and with fork creates one child processes for commands
// after handling children processes closes file descriptors, waits for children to finish
// returns with exitcode set by handling files or commands
int	pipex(t_var *px, char **argv)
{
	int	pid1;
	int	pid2;
	int	fd[2];

	pid1 = -1;
	pid2 = -1;
	if (pipe(fd) == -1)
	{
		clean_up(px);
		exit_file_error(px, "pipe creation error");
	}
	if (!px->error_cmd1)
	{
		pid1 = fork();
		if (pid1 < 0)
		{
			clean_up(px);
			exit_file_error(px, "fork error");
		}
		if (pid1 == 0)
			handle_first_child(px, fd);
	}
	if (px->cmd1)
		free_array(&px->cmd1);
	px->cmd2 = ft_split(argv[3], ' ');
	if (!px->cmd2)
	{
		clean_up(px);
		free_array(&px->cmd1);
		exit_command_error(px, argv[3]);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		clean_up(px);
		exit_file_error(px, "fork error");
	}
	if (pid2 == 0)
		handle_second_child(px, fd);
	close(fd[0]);
	close(fd[1]);
	wait_for_processes(px, pid1, pid2);
	clean_up(px);
	return (px->exitcode);
}
