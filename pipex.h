/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:32:09 by clundber          #+#    #+#             */
/*   Updated: 2024/01/24 12:15:11 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/includes/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	char	*path;
	char	*path2;
	char	**cmd_array;
	char	**cmd_array2;
	int		pipe_fd[2];
}	t_pipex;

void	arg_check(int argc);//, char **argv);
void	ft_free(char **array);
char	*get_path(char *cmd,char **envp);
void	child_one(t_pipex *pipex);
void	child_two(t_pipex *pipex);
void	ft_free_str(char *str);
void	ft_free_all(t_pipex *pipex);
char	**ft_splitter(char *str);
char	*get_path(char *cmd,char **envp);
void	ft_exec(pid_t pid, pid_t pid2, t_pipex *pipex);

# endif