/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_return.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:29:27 by clundber          #+#    #+#             */
/*   Updated: 2023/11/15 15:05:24 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr_return(char *s)

{
	int	count;
	int	temp;

	temp = 0;
	count = 0;
	if (!s)
	{
		count += write (1, "(null)", 6);
		return (count);
	}
	while (*s)
	{
		count += write(1, s, 1);
		s++;
		if (temp > count)
			return (-1);
		temp = count;
	}
	return (count);
}
