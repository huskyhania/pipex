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

void	set_redirections(int input_fd, int output_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		exit (1);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		exit (1);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
}

int	fork_and_execute(t_var *px, int input_fd, int output_fd, char *cmd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		exit_file_error(px, "fork error");
	if (pid == 0)
	{
		set_redirections(input_fd, output_fd);
		px->cmd1 = get_command(cmd, px);
		if (!px->error_cmd1)
			pipex_helper(px);
		clean_up(px);
		exit(px->exitcode);
	}
	return (pid);
}

void	pipex_helper(t_var *px)
{
	if (px->cmd_path == NULL)
	{
		perror("helper path not found");
		clean_up(px);
		exit(127);
	}
	if (execve(px->cmd_path, px->cmd1, px->envp) == -1)
	{
		errno = EACCES;
		perror(px->cmd1[0]);
		free(px->cmd_path);
		free_array(&px->cmd1);
		clean_up(px);
		exit(127);
	}
}

// Function to wait for both child processes and set the exit code
void	wait_for_processes(t_var *px, int last_pid)
{
	int	status;
	int	current_exit_code;
	int	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
		{
			current_exit_code = WEXITSTATUS(status);
			if (pid == last_pid)
				px->exitcode = current_exit_code;
		}
		pid = wait(&status);
	}
}

// Function opens a pipe, and with fork creates one child processes for commands
// after handling children processes closes file descriptors, waits for children to finish
// returns with exitcode set by handling files or commands
int	pipex(t_var *px, char **argv, int argc)
{
	int	fd[2];
	int	prev_fd;
	int	i;
	int	last_pid;

	prev_fd = px->input_fd;
	i = 2;
	last_pid = -1;
	while (i < argc - 2)
	{
		if (pipe(fd) == -1)
			exit_file_error(px, "pipe creation error");
		last_pid = fork_and_execute(px, prev_fd, fd[1], argv[i]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		close(fd[1]);
		prev_fd = fd[0];
		i++;
	}
	last_pid = fork_and_execute(px, prev_fd, px->output_fd, argv[argc - 2]);
	close(prev_fd);
	wait_for_processes(px, last_pid);
	clean_up(px);
	return (px->exitcode);
}
