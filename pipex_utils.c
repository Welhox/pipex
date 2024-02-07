/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:41:54 by clundber          #+#    #+#             */
/*   Updated: 2024/02/07 12:02:05 by clundber         ###   ########.fr       */
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

char	*get_path(char *cmd, char **envp, char *ptr, int i)

{
	char	**array;
	char	*path;

	array = NULL;
	while (envp[i] && ft_strnstr(envp[i], "PATH=/", 6) == 0)
		i++;
	if (!envp[i])
		return(NULL);
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

void	ft_argcheck(int argc, char *argv[], char *envp[])

{
	int	fd;

	fd = 0;
	if (argc != 5 || !argv[2][0] || !argv[3][0])
	{
		ft_putstr_fd("Usage is : file cmd1 cmd2 file2\n", 2);
		exit (1);
	}
	if (!envp || !envp[0])
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
}

char	*ft_tri_strjoin(char const *s1, char const *s2, char const *s3)

{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str = malloc ((ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1) * sizeof(char));
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
