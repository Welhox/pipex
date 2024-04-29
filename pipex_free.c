/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:06:19 by clundber          #+#    #+#             */
/*   Updated: 2024/02/22 13:35:36 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **array)

{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
		while (i >= 0)
		{
			free (array[i]);
			i--;
		}
		free (array);
		array = NULL;
	}
}

void	ft_free_str(char *str)

{
	if (str)
	{
		free (str);
		str = NULL;
	}
}

void	ft_free_all(t_pipex *pipex)

{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	ft_free_str (pipex->path);
	ft_free_str (pipex->path2);
	ft_free(pipex->cmd_array);
	ft_free(pipex->cmd_array2);
}

void	ft_exit(char *str, int code)

{
	ft_putstr_fd(str, 2);
	exit(code);
}

void	ft_argcheck(int argc, char *argv[], char *envp[], t_pipex *pipex)

{
	if (argc != 5)
		ft_exit("usage is : file cmd1 cmd2 file2\n", 1);
	if (!argv[2][0])
		pipex->cmd_array = ft_split("invalid", 'z');
	else
		pipex->cmd_array = NULL;
	if (!argv[3][0])
		pipex->cmd_array2 = ft_split("invalid", 'z');
	else
		pipex->cmd_array2 = NULL;
	if (!envp || !envp[0])
		ft_exit("envp missing\n", 1);
}
