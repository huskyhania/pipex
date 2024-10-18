/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:03:04 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/17 13:11:55 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void execute_command(t_var *px_var, int input_fd, int output_fd, char **cmd)
{
    char *cmd_path;

    dup2(input_fd, STDIN_FILENO);   // Redirect input
    dup2(output_fd, STDOUT_FILENO); // Redirect output
    close(input_fd);
    close(output_fd);

    cmd_path = get_command_path(cmd[0], px_var->envp);
    if (!cmd_path)
    {
	    clean_up(px_var);
        perror("command path fail");
//        if (px_var->cmd1)
//          free_array(px_var->cmd1);
//       if (px_var->cmd2)
//            free_array(px_var->cmd2);
	    exit_on_error(px_var, cmd[0], 0); // Handle error
    }
    execve(cmd_path, cmd, px_var->envp);
    perror("execve fail");  // Execute the command
    free(cmd_path);
    clean_up(px_var);
    exit_on_error(px_var, "execve error", 0); // If execve fails
}

// Function to execute command for the first child
void handle_first_child(t_var *px_var, int fd[2])
{
    close(fd[0]); // Close unused read end of the pipe
    execute_command(px_var, px_var->input_fd, fd[1], px_var->cmd1); // Pass input, output, and command
}

// Function to execute command for the second child
void handle_second_child(t_var *px_var, int fd[2])
{
    close(fd[1]); // Close unused write end of the pipe
    execute_command(px_var, fd[0], px_var->output_fd, px_var->cmd2); // Pass input, output, and command
}

// Function to wait for both child processes and set the exit code
void wait_for_processes(t_var *px_var, int pid1, int pid2)
{
    int status;

    waitpid(pid1, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        px_var->exitcode = WEXITSTATUS(status);
    
    waitpid(pid2, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        px_var->exitcode = WEXITSTATUS(status);
}

int pipex(t_var *px_var)
{
    int	fd[2];
    int	pid1;
    int	pid2;

    // Open the pipe
    if (pipe(fd) == -1)
    {
	    clean_up(px_var);
	    exit_on_error(px_var, "opening pipe error", 0);
    }
    // First child process
    pid1 = fork();
    if (pid1 < 0)
    {
	    clean_up(px_var);
	    exit_on_error(px_var, "fork error", 0);
    }
    if (pid1 == 0) // Inside the first child
	    handle_first_child(px_var, fd);
    // Second child process
    pid2 = fork();
    if (pid2 < 0)
    {
	    clean_up(px_var);
	    exit_on_error(px_var, "fork error", 0);
    }
    if (pid2 == 0) // Inside the second child
        handle_second_child(px_var, fd);

    // Parent process: Close both ends of the pipe
    close(fd[0]);
    close(fd[1]);

    // Wait for both child processes to finish
    wait_for_processes(px_var, pid1, pid2);
    return (px_var->exitcode);
}
