/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:47:48 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/22 18:47:49 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	atosz(const char *str)
{
	size_t	res;

	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == '+' || *str == '-')
		str++;
	while (*str && *str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = count * size;
	if (total_size != 0 && total_size / count != size)
		return (NULL);
	ptr = (void *)malloc(total_size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, total_size);
	return (ptr);
}
