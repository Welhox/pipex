/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:38:18 by clundber          #+#    #+#             */
/*   Updated: 2023/11/06 10:51:46 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)

{
	int	i;
	int	j;

	i = 0;
	if (!haystack && len == 0)
		return (0);
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && (len - j) > 0)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
		i++;
		len--;
	}
	return (0);
}
