/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_return.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:33:47 by clundber          #+#    #+#             */
/*   Updated: 2023/11/15 14:55:38 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnbr_u_return(unsigned int nbr)

{
	char	output;
	int		count;
	int		temp;

	temp = 0;
	count = 0;
	output = nbr % 10 + 48;
	if (nbr / 10 != 0)
		count += ft_putnbr_u_return(nbr / 10);
	if (temp > count)
		return (-1);
	temp = count;
	count += write(1, &output, 1);
	return (count);
}
