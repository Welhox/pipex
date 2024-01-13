/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welhox <welhox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:56:37 by clundber          #+#    #+#             */
/*   Updated: 2023/11/08 22:13:46 by welhox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)

{
	int		counter;
	t_list	*ptr;

	ptr = NULL;
	counter = 0;
	if (!lst)
		return (0);
	ptr = lst;
	while (ptr)
	{
		counter++;
		ptr = ptr->next;
	}
	return (counter);
}
