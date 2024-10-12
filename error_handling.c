/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:11:43 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/12 20:21:10 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exit_on_error(t_var *px_var, char *info, int is_file_error)
{
    write(2, "pipex: ", 7); // Print the prefix

    if (is_file_error)
    {
        // Check for file-related errors
        if (errno == EACCES)
        {
            // Permission denied for input or output files
            px_var->exitcode = 0; // Change exit code to 0 for permission denied on infile
            perror(info); // Print the error message
        }
        else if (errno == ENOENT)
        {
            // File not found
            px_var->exitcode = 0; // Exit code 0 for missing infile
            perror(info); // Print the error message
        }
        else
        {
            // General file error
            px_var->exitcode = 1; // Default exit code for other file errors
            perror(info);
        }
    }
    else
    {
        // Handle command execution errors
        if (errno == EACCES)
        {
            // Permission denied for command execution
            px_var->exitcode = 1; // Exit code 1 for permission denied on command
            perror(info);
        }
        else if (errno == ENOENT)
        {
            // Command not found
            px_var->exitcode = 127; // Exit code 127 for command not found
            perror(info);
        }
        else
        {
            // General command execution error
            px_var->exitcode = 1; // Default exit code for other command errors
            perror(info);
        }
    }

    exit(px_var->exitcode); // Exit with the determined exit code
}
