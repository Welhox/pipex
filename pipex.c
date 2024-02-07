/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:34:07 by clundber          #+#    #+#             */
/*   Updated: 2024/02/07 19:06:33 by clundber         ###   ########.fr       */
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
	close(fd);
	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], 1);
	close(pipex->pipe_fd[1]);
	if (execve(pipex->path, pipex->cmd_array, pipex->envp) == -1)
	{
		ft_free_all(pipex);
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(pipex->argv[2], 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
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
	dup2(pipex->pipe_fd[0], 0);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	dup2(fd, 1);
	close(fd);
	if (execve(pipex->path2, pipex->cmd_array2, pipex->envp) == -1)
	{
		ft_free_all(pipex);
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(pipex->argv[3], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

void	ft_argadd(t_pipex *pipex, char **argv, char **envp, int pipe_fd[2])

{
	int		i;

	i = 0;
	pipex->argv = argv;
	pipex->envp = envp;
	if (!pipex->cmd_array)
		pipex->cmd_array = ft_splitter(pipex->argv[2]);
	if (!pipex->cmd_array2)
		pipex->cmd_array2 = ft_splitter(pipex->argv[3]);
	if (access(pipex->cmd_array[0], (F_OK | X_OK)) == -1)
		pipex->path = get_path(pipex->cmd_array[0], pipex->envp, i);
	else
		pipex->path = ft_strdup(pipex->cmd_array[0]);
	if (access(pipex->cmd_array2[0], (F_OK | X_OK)) == -1)
		pipex->path2 = get_path(pipex->cmd_array2[0], pipex->envp, i);
	else
		pipex->path2 = ft_strdup(pipex->cmd_array2[0]);
	pipex->pipe_fd[0] = pipe_fd[0];
	pipex->pipe_fd[1] = pipe_fd[1];
	pipex->exit_code2 = 0;
}

void	ft_exec(pid_t pid, pid_t pid2, t_pipex *pipex)

{
	int	status;

	if (pid == 0 && pid2 == 0)
		child_one(pipex);
	else if (pid2 == 0 && pid != 0)
		child_two(pipex);
	ft_free_all(pipex);
	if (pid != 0 && pid2 != 0)
	{
		waitpid(pid, NULL, 0);
		waitpid(pid2, &status, 0);
		if (WIFEXITED(status))
			pipex->exit_code2 = WEXITSTATUS(status);
	}
}

int	main(int argc, char *argv[], char *envp[])

{
	t_pipex	pipex;
	pid_t	pid;
	pid_t	pid2;
	int		pipe_fd[2];

	pid = 0;
	pid2 = 0;
	ft_argcheck(argc, argv, envp, &pipex);
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
	return (pipex.exit_code2);
}
