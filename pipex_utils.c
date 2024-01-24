/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:41:54 by clundber          #+#    #+#             */
/*   Updated: 2024/01/24 16:42:01 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_splitter(char *str)

{
	char **temp_array;
	char	*ptr;

	ptr = NULL;
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
					ptr = temp_array[0];
					temp_array[0] = ft_substr(temp_array[0], 0, k);
					ft_free_str(ptr);
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

void	ft_free(char **array)

{
	int	i;

	i = 0;
	if (array)
	{
		while(array[i])
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

char	*ft_strjoin_tres(char const *s1, char const *s2, char const *s3)

{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str = malloc ((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	j = 0;
	while (s3[j])
		str[i++] = s3[j++];	
	str[i] = '\0';
	return (str);
}

char	*get_path(char *cmd,char **envp)

{
	int	i;
	char	**temp;
	char	**array;
	char	*path;
	char	*temp_str;

	temp_str = NULL;
	array = NULL;
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=/", 6) == 0)
		i++;
	temp_str = ft_substr(envp[i], 5, (ft_strlen(envp[i]) -5));
	temp = ft_split(temp_str, ':');
	ft_free_str(temp_str);
	//temp = ft_split(envp[i], ':');
	i = 0;
	while (temp[i])
		i++;
	array = malloc (sizeof(char*) * (i +1));
	i = 0;
	while (temp[i])
	{
		array[i] = ft_strjoin_tres(temp[i], "/", cmd);
		//ft_printf("array = %s\n", array[i]);
		i++;
	}
	array[i] = NULL;
	ft_free(temp);
	i = 0;
	while (array[i] && (access (array[i], (F_OK | X_OK)) == -1))
		i++;
	path = ft_strdup(array[i]);//ft_strjoin(array[i], cmd);
	ft_free(array);
	return (path);
}
