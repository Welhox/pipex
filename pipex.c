/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:34:07 by clundber          #+#    #+#             */
/*   Updated: 2024/01/23 15:01:09 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	arg_check(int argc, char **argv)

{
	int	fd;

	if (argc != 5)
	{
		write(2, "Usage is : ./pipex file1 cmd1 cmd2 file2\n", 41);	
		exit (1);
	}

	fd = open(argv[1], O_RDONLY);
 	if (fd < 0)
	{
		perror("infile");
		exit (0);
	} 
	close(fd);
}

void	ft_free(char **array)

{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free (array[i]);
			i++;
		}
		free (array);
		array = NULL;
	}
}

char	*get_path(char *cmd,char **envp)

{
	int	i;
	int	j; //DELETE
	char **temp;
	char **path_array;
	char *path;

	path_array = NULL;
	j = 0;
	i = 0;
	while (envp[i] &&  ft_strnstr(envp[i], "PATH=/", 10) == 0)
		i++;
	temp = ft_split(envp[i], ':');
	i = 0;
	while (temp[j])
		j++;
	path_array = malloc(sizeof(char*) * j);
	j = 0;
	while (temp[i])
	{
		path_array[i] = ft_strjoin(temp[i], "/");
		i++;
	}
	path_array[i] = NULL;
	ft_free(temp);
	i = 0;
	while (path_array[i] && (access (ft_strjoin(path_array[i], cmd), (F_OK | X_OK)) == -1))
		i++;
	path = ft_strjoin(path_array[i], cmd);
	return(path);
	
}


void	child_one(t_pipex *pipex)

{
	int	fd;
	fd = open(pipex->argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror(pipex->argv[1]);
		write(pipex->pipe_fd[1], "", 0);
		exit(1);
	}
	dup2(fd, 0);
	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], 1);
	if(execve(pipex->path, pipex->cmd_array, pipex->envp) == -1)
		//perror("could not execute command\n");
		write(2, "could not execute command\n", 26);
}

void	child_two(t_pipex *pipex)

{
	int	fd;
	fd = open(pipex->argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_free_all(pipex);
		perror("outfile");
		exit(1);
	}
	dup2(fd, 1);
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], 0);
	if(execve(pipex->path2, pipex->cmd_array2, pipex->envp) == -1)
		write(2, "could not execute command\n", 26);
		//perror("could not execute command\n");
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
	ft_free_str (pipex->path);
	ft_free_str (pipex->path2);
	ft_free(pipex->cmd_array);
	ft_free(pipex->cmd_array2);
} 

char	**ft_splitter(char *str)

{
	char **temp_array;

	temp_array = NULL;


	int	i;
	int k;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			temp_array = ft_split(str, str[i]);
			while (temp_array[0][k])
			{
				if (temp_array[0][k] == ' ')
				{	
					temp_array[0] = ft_substr(temp_array[0], 0, k);
					break; 
				}
				k++;
			}	
			break;
		}	
		i++;
	}
	if (!temp_array)
		temp_array = ft_split(str, ' ');
	return(temp_array);

}

int	main(int argc, char *argv[], char *envp[])

{
	t_pipex	pipex;
	pid_t	pid;
	pid_t	pid2;
	int		pipe_fd[2];

	pid = 0;
	pid2 = 0;
	//argc = 0;
	if (argc != 5)
	{
		write(2, "Usage is : ./pipex file1 cmd1 cmd2 file2\n", 41);	
		exit (1);
	}
	//arg_check(argc, argv);
	pipe(pipe_fd);
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.pipe_fd[0] = pipe_fd[0];
	pipex.pipe_fd[1] = pipe_fd[1];
	pipex.cmd_array = ft_splitter(argv[2]);
	pipex.cmd_array2 = ft_splitter(argv[3]);
	pipex.path = get_path(pipex.cmd_array[0], envp);
	pipex.path2 = get_path(pipex.cmd_array2[0], envp);
	pid = fork();
	if (pid != 0)
	{
		pid2 = fork();
		if (pid2 == 0)
			child_two(&pipex);
	}
	if (pid == 0)
		child_one(&pipex);
	if (pid != 0)
	{
		wait(&pid);
		wait(&pid2);
	}
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	ft_free_all(&pipex);
	return(0);
}
/*
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/