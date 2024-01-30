/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welhox <welhox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:34:07 by clundber          #+#    #+#             */
/*   Updated: 2024/01/30 21:12:18 by welhox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(t_pipex *pipex)

{
	int	fd;

	fd = open(pipex->argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror(pipex->argv[1]);
		write(pipex->pipe_fd[1], "", 0);
		ft_free_all(pipex);
		exit(1);
	}
	dup2(fd, 0);
	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], 1);
	if (execve(pipex->path, pipex->cmd_array, pipex->envp) == -1)
	{
		ft_putstr_fd(pipex->argv[2], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
		//perror("could not execute command one\n");
	
}

void	child_two(t_pipex *pipex)

{
	int	fd;

	fd = open (pipex->argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{	
		perror(pipex->argv[4]);
		ft_free_all(pipex);
		exit(1);
	}
	//ft_printf("ok here1\n");

	dup2(pipex->pipe_fd[0], 0);
	close(pipex->pipe_fd[1]);
	//ft_printf("ok here2\n");
	dup2(fd, 1);
	//ft_printf("ok here3\n");

	//ft_printf("ok here\n");
	if (execve(pipex->path2, pipex->cmd_array2, pipex->envp) == -1)
	{
		ft_putstr_fd(pipex->argv[3], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
		//perror("could not execute command two\n");
	}

	//ft_printf("ok here\n");
}

void	ft_argadd(t_pipex *pipex, char **argv, char **envp, int pipe_fd[2])

{
	char	*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->cmd_array = ft_splitter(pipex->argv[2]);
	pipex->cmd_array2 = ft_splitter(pipex->argv[3]);
	if (access(pipex->cmd_array[0], (F_OK | X_OK)) == -1)
		pipex->path = get_path(pipex->cmd_array[0], pipex->envp, ptr, i);
	else
		pipex->path = ft_strdup(pipex->cmd_array[0]);
	if (access(pipex->cmd_array2[0], (F_OK | X_OK)) == -1)	
		pipex->path2 = get_path(pipex->cmd_array2[0], pipex->envp, ptr, i);
	else
		pipex->path2 = ft_strdup(pipex->cmd_array2[0]);
	pipex->pipe_fd[0] = pipe_fd[0];
	pipex->pipe_fd[1] = pipe_fd[1];
	pipex->exit_code1 = 0;
	pipex->exit_code2 = 0;
}

void	ft_exec(pid_t pid, pid_t pid2, t_pipex *pipex)

{
	if (pid == 0 && pid2 == 0)
		child_one(pipex);
	else if (pid2 == 0 && pid != 0)
		child_two(pipex);
/* 	else
	{
		pid2 = fork();
		if (pid2 == -1)
		{
			ft_free_all(pipex);
			exit (1);
		}
		if (pid2 == 0)
			child_two(pipex);
	} */
	//if (pid != 0 && pid2 != 0)
  	else
	{
 		waitpid(pid, &pipex->exit_code1, 1);
		waitpid(pid2, &pipex->exit_code2, 1); 
		if (WIFEXITED(pipex->exit_code1))
			pipex->exit_code1 = WEXITSTATUS(pipex->exit_code1);
		//ft_printf("exit code1 = %d\n", pipex->exit_code1);
		if (WIFEXITED(pipex->exit_code2))
			pipex->exit_code2 = WEXITSTATUS(pipex->exit_code2);
		//ft_printf("exit code2 = %d\n", pipex->exit_code2); 
	}
}

int		ft_argcheck(int argc, char *argv[], char *envp[])

{
	int fd;

	fd = 0;
	if (argc != 5)
	{
		ft_putstr_fd("Usage is : file cmd1 cmd2 file2\n", 2);
		exit (1);
	}
	if (!envp)
		exit (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
 	{
 		perror(argv[1]);
		exit (0);
	} 
	close (fd);
 	fd = open (argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
 	{
 		perror(argv[4]);
		exit (1); 
	} 
	close (fd);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])

{
	t_pipex	pipex;
	pid_t	pid;
	pid_t	pid2;
	int		pipe_fd[2];
	int		exit_code;

	exit_code = 0;
	pid = 0;
	pid2 = 0;
	ft_argcheck(argc, argv, envp);
	pipe(pipe_fd);
	ft_argadd(&pipex, argv, envp, pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		ft_free_all(&pipex);
		return (1);
	}
	if (pid != 0)
		pid2 = fork();
	if (pid2 == -1)
	{
		ft_free_all(&pipex);
		return (1);
	}

	ft_exec(pid, pid2, &pipex);
	ft_free_all(&pipex);
	exit_code = pipex.exit_code1;
	//if (pipex.exit_code2 != 0)
	exit_code = pipex.exit_code2;
	return (exit_code);
}
/*
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/