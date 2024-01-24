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

/**
 * Function: Atosz
 * -----------------
 * This function is used to convert a string to size_t. Here we check if the
 * string is a number, and if it is, we convert it to size_t.
 *  
 * @param: *str: The string that is going to be converted.
 * @var: *res: The result of the conversion.
 * 
 * @return: Returns the converted string.
 *
 */

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

/**
 * Function: Ft_calloc
 * -----------------
 * This function is used to allocate memory and initialize it to 0. 
 *  
 * @param: count: The number of elements.
 * @param: size: The size of each element.
 * @var: total_size: The total size of the memory that is going to be allocated.
 * 
 * @return: Returns the converted string.
 *
 */

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
