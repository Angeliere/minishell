/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:06:28 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/05 19:22:18 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *src, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
