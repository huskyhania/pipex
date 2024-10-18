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

void exit_file_error(t_var *px_var, char *filename)
{
    // Print the error prefix
    write(2, "pipex: ", 7);
    perror(filename); // Print error message with file info

    // Set exit code based on the error
    if (errno == EACCES || errno == ENOENT)
    {
        // Permission denied or file not found -> Bash exits with 1 for file-related issues
        px_var->exitcode = 0;
        if (filename == px_var->outfile)
            px_var->exitcode = 1;
    }
    else
    {
        // Other file-related errors, default exit code is 1
        px_var->exitcode = 1;
    }
    // Exit with the appropriate exit code
    exit(px_var->exitcode);
}

void    exit_command_error(t_var *px_var, char *cmd)
{
    write(2, "pipex: ", 7);
    write(2, cmd, ft_strlen(cmd));
    char buffer[50];
    sprintf(buffer, "\nerrno: %d\n", errno);
    write(2, buffer, ft_strlen(buffer));
    if (errno == EACCES)
        write(2, ": Permission denied", 20);
    if (px_var->cmd1)
		    free_array(px_var->cmd1);
	if (px_var->cmd2)
		    free_array(px_var->cmd2);
    exit(0);  // Exit with 0 for now to focus on output display
}