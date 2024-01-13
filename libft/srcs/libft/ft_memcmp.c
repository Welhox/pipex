/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:30:33 by clundber          #+#    #+#             */
/*   Updated: 2023/11/06 11:30:21 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)

{
	unsigned char	*s1ptr;
	unsigned char	*s2ptr;
	int				i;

	s1ptr = (unsigned char *)s1;
	s2ptr = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (n > 0 && s1ptr[i] == s2ptr[i])
	{
		i++;
		n--;
	}
	if (n == 0 && s1ptr[i -1] == s2ptr[i -1])
		return (0);
	if (s1ptr[i] != s2ptr[i])
		return (s1ptr[i] - s2ptr[i]);
	return (0);
}
