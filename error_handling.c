/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:11:43 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/18 15:51:20 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exit_file_error(t_var *px, char *filename)
{
    // Print the error prefix
    write(2, "pipex: ", 7);
    perror(filename); // Print error message with file info

    // Set exit code based on the error
    if (errno == EACCES || errno == ENOENT)
    {
        // Permission denied or file not found -> Bash exits with 1 for file-related issues
        px->exitcode = 0;
        if (filename == px->outfile)
            px->exitcode = 1;
    }
    else
    {
        // Other file-related errors, default exit code is 1
        px->exitcode = 1;
    }
    // Exit with the appropriate exit code
    exit(px->exitcode);
}

void    display_error(t_var *px, const char *cmd)
{
    write(2, "pipex: ", 7);
    perror(cmd);
}

void    exit_command_error(t_var *px, char *cmd)
{
    //write(2, "pipex: ", 8);
    //write(2, cmd, ft_strlen(cmd));

    //char buffer[50];
    //sprintf(buffer, "errno: %d\n", errno);
    //write(2, buffer, ft_strlen(buffer));

    // Check for permission errors (EACCES)
    //if (errno == EACCES)
    //    write(2, ": Permission denied\n", 20);
    //else if (errno == ENOENT)
    //    write(2, "No such file or directory", 26);

    // Clean up allocated resources
    if (px->cmd1)
        free_array(px->cmd1);
    if (px->cmd2)
        free_array(px->cmd2);

    exit(px->exitcode);  // Exit with an error code (use 1 for errors)
}