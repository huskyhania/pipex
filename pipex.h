/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:06:12 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/17 13:07:33 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./complete_Libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex_variables
{
	int		input_fd;
	int		output_fd;
	int		exitcode;
	int		error_cmd1;
	int		error_cmd2;
	char	**envp;
	char	**cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
	char	*cmd_path;
}		t_var;

int		pipex(t_var *px, char **argv);
char	*join_paths(const char *dir, const char *cmd);
char	*find_path_in_envp(char *envp[]);
char	*get_command_path(const char *cmd, t_var *px);

void	free_array(char ***array);
void	exit_file_error(t_var *px, char *filename);
void	exit_command_error(t_var *px, char *cmd);
void	init_variables(char **argv, char **envp, t_var *px);
void	check_fd(char **argv, t_var *px);
void	check_commands(char **argv, t_var *px);

void	execute_command(t_var *px, int input_fd, int output_fd, char **cmd);
void	handle_first_child(t_var *px, int fd[2]);
void	handle_second_child(t_var *px, int fd[2]);
void	wait_for_processes(t_var *px, int pid1, int pid2);
void	clean_up(t_var *px);
int		is_empty_or_space(const char *cmd);
void	display_error(t_var *px, const char *cmd);
void	set_error_and_display(int code, t_var *px, const char *cmd);

#endif
