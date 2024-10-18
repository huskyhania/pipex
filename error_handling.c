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
	    px_var->exitcode = errno;
	    if (errno == ENOENT || errno == EACCES || errno == EISDIR)
		    perror(info);
	    else
	    {
		    ft_putstr_fd(info, 2);
		    ft_putendl_fd(": command not found", 2);
	    }
	    if (px_var->cmd1)
		    free_array(px_var->cmd1);
	    if (px_var->cmd2)
		    free_array(px_var->cmd2);
	    if (px_var->exitcode == EACCES || px_var->exitcode == EISDIR)
		    px_var->exitcode = 126;
	    else
		    px_var->exitcode = 127;
	    exit(px_var->exitcode);
    }
}
