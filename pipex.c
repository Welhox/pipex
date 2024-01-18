/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:34:07 by clundber          #+#    #+#             */
/*   Updated: 2024/01/17 15:37:12 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	arg_check(int argc, char **argv)

{
	int	fd;

	if (argc != 5 || !argv[2] || !argv[3])
	{
		write(2, "Error\n", 6);	
		exit (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		//ft_printf("unable to open read file\n");
		exit (0);
	}
	close(fd);
	fd = open (argv[4], O_WRONLY);
	if (fd < 0)
	{
		perror("Error");
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
/* 	while(path_array[j]) //DELETE
	{
		ft_printf("path_array = %s\n", path_array[j]);
		j++;

	} */
	i = 0;
	while (path_array[i] && (access (ft_strjoin(path_array[i], cmd), (F_OK | X_OK)) == -1))
		i++;
	path = ft_strjoin(path_array[i], cmd);
	return(path);
	
}

 char **get_cmd(char **argv)

{
	char **array;

	array = NULL;
	array = malloc(sizeof(char*) * 3);
	int	i;

	i = 1;
	array[0] = ft_strdup(argv[0]);
	//array[1] = ft_strdup(argv[2]);
	array[1] = NULL;
 
	return(array);

} 

int	main(int argc, char *argv[], char *envp[])

{
	t_pipex	**pipex;
	pipex = malloc(sizeof(t_pipex));
	pid_t	pid;
	int		fd;
	char	*path;
	char	**cmd_arr;
	int		pipe_fd[2];

	arg_check(argc, argv);
	pipe(pipe_fd);
	pid = fork();
	cmd_arr = get_cmd(argv);
	if (pid != 0) //parent
	{
		fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		path = get_path(argv[2], envp);
		if(execve(path, cmd_arr, envp) == -1)
		{
		perror("could not execute command\n");
		}

	}
	else // child
	{
		fd = open(argv[4], O_WRONLY);
		dup2(fd, 1);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		path = get_path(argv[3], envp);
		if(execve(path, cmd_arr, envp) == -1)
		{
		perror("could not execute command\n");
		}
	}

// 	path = get_path(argv[2], envp);
	//argc = 0; // for silencing the warning, DELETE when argcheck returned
/*	//arg_check(argc, argv);



	fd1 = open (argv[3], O_WRONLY);
	dup2(fd1, 1);


  	if(execve(path, cmd_arr, envp) == -1)
	{
		perror("could not execute command\n");

	}
		// fork traini */

/* 	int i = 0;
	while(envp[i])
	{
	ft_printf("the envp = %s\n\n", envp[i]);
	i++;
	} */

	//char cmd[] = "bin/wc";
//	char *argv[] = {"/bin/ls", "-l", NULL};
//	char *envp[] = {NULL};

/* 	int package;
	package = 0;
	int	pipe1[2];
	int	pipe2[2];
	pipe(pipe1);
	pipe(pipe2); */
	//pid = fork();
/*
	if (pid == 0) // this is the child process
	{
		read(pipe1[0], &package, sizeof(int));
		fd = open (argv[4], O_WRONLY);
		dup2(fd, 1);
		//ft_printf("Hello, this is child\n");
		ft_printf("the package number is %d\n", package);
		close(fd);
	}
	else // this is the parent process
	{
		package = 10;
		write(pipe1[1], &package, sizeof(int));
		//wait(&pid);
		ft_printf("and I am parent\n");
	} */

	// fork training
	return(0);
}


/*
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/