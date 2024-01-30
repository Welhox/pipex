/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:32:09 by clundber          #+#    #+#             */
/*   Updated: 2024/01/30 14:25:56 by clundber         ###   ########.fr       */
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
	int		exit_code1;
	int		exit_code2;

}	t_pipex;

char	*ft_tri_strjoin(char const *s1, char const *s2, char const *s3);
void	ft_free(char **array);
char	*get_path(char *cmd,char **envp, char *ptr, int i);
void	child_one(t_pipex *pipex);
void	child_two(t_pipex *pipex);
void	ft_free_str(char *str);
void	ft_free_all(t_pipex *pipex);
char	**ft_splitter(char *str);
void	ft_exec(pid_t pid, pid_t pid2, t_pipex *pipex);
//void	ft_argcheck(int argc, char *argv[], char *envp[]);

# endif