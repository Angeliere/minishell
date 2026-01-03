/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:06:38 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/09 12:52:24 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*pointer;

	if (size != 0 && n > ((size_t)-1) / size)
		return (NULL);
	if (n == 0 || size == 0)
		return (malloc(0));
	pointer = malloc(size * n);
	if (pointer == NULL)
		return (NULL);
	ft_memset (pointer, 0, n * size);
	return (pointer);
}
