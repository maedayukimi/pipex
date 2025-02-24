/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:17:46 by mawako            #+#    #+#             */
/*   Updated: 2024/09/11 16:15:42 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mainh;
	t_list	*temp;
	t_list	*new;
	void	*f_tmp;

	if (!lst)
		return (NULL);
	f_tmp = (*f)(lst->content);
	mainh = ft_lstnew(f_tmp);
	if (!mainh)
		return (free(f_tmp), NULL);
	temp = lst->next;
	while (temp != NULL)
	{
		f_tmp = (*f)(temp->content);
		new = ft_lstnew(f_tmp);
		if (!new)
			return (ft_lstclear(&mainh, del), free(f_tmp), NULL);
		ft_lstadd_back(&mainh, new);
		temp = temp->next;
	}
	return (mainh);
}
