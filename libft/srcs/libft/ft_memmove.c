/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:04:54 by clundber          #+#    #+#             */
/*   Updated: 2023/11/01 11:57:31 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)

{
	char		*dstptr;
	const char	*srcptr;

	srcptr = src;
	dstptr = dst;
	if (!dst && !src)
		return (0);
	if (dstptr > srcptr)
	{
		while (len > 0)
		{
			dstptr[len -1] = srcptr[len -1];
			len--;
		}
	}
	while (len > 0)
	{
		*dstptr = *srcptr;
		dstptr++;
		srcptr++;
		len--;
	}
	return (dst);
}
