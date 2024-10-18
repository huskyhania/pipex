/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:05:21 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/16 21:07:32 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	t_var	px_var;

	if (argc != 5)
	{
		write(2, "Params should be: file1 cmd1 cmd2 file2\n", 40);
		return (1);
	}
	init_variables(argv, envp, &px_var);
	//if (!px_var.cmd1 || !px_var.cmd2)
	//{
	//	printf("i'm exiting from main\n");
	//	exit_on_error(&px_var, "Command not found", 0);
	//}
	pipex(&px_var);
	free_array(px_var.cmd1);
	free_array(px_var.cmd2);
	return (px_var.exitcode);
}
