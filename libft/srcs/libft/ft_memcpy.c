/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:57:59 by clundber          #+#    #+#             */
/*   Updated: 2023/11/01 11:48:46 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dstptr;
	const char	*srcptr;

	dstptr = dst;
	srcptr = src;
	if (dst == NULL && src == NULL)
		return (0);
	while (n > 0)
	{
		*dstptr = *srcptr;
		dstptr++;
		srcptr++;
		n--;
	}
	return (dst);
}
