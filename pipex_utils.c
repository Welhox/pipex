/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:41:54 by clundber          #+#    #+#             */
/*   Updated: 2024/01/29 17:01:47 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_splitter(char *str)

{
	char	**temp_array;
	char	*ptr;
	int		i;

	i = 0;
	while (str[i] && str[i] != 39 && str[i] != 34)
		i++;
	if (str[i] == 39 || str[i] == 34)
	{
		temp_array = ft_split(str, str[i]);
		i = 0;
		while (temp_array[0][i])
		{
			if (temp_array[0][i] == ' ')
			{
				ptr = temp_array[0];
				temp_array[0] = ft_substr(temp_array[0], 0, i);
				ft_free_str(ptr);
				return (temp_array);
			}
			i++;
		}
		return (temp_array);
	}
	return (ft_split(str, ' '));
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

char	*get_path(char *cmd, char **envp, char *ptr, int i)

{
	char	**array;
	char	*path;

	while (envp[i] && ft_strnstr(envp[i], "PATH=/", 6) == 0)
		i++;
	path = ft_substr(envp[i], 5, (ft_strlen(envp[i]) - 5));
	array = ft_split(path, ':');
	free (path);
	path = NULL;
	i = 0;
	while (array[i])
	{
		ptr = array[i];
		array[i] = ft_tri_strjoin(array[i], "/", cmd);
		i++;
		free (ptr);
	}
	i = 0;
	while (array[i] && (access (array[i], (F_OK | X_OK)) == -1))
		i++;
	if (array[i])
		path = ft_strdup(array[i]);
	ft_free(array);
	return (path);
}
