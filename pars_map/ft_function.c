/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:01:36 by scolen            #+#    #+#             */
/*   Updated: 2021/02/02 19:27:07 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	len_number(int number)
{
	int len;

	len = 1;
	if (number < 0)
		number = number * (-1);
	while (number > 0)
	{
		number = number / 10;
		len++;
	}
	return (len);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)str1;
	ptr2 = (unsigned char *)str2;
	i = 0;
	while (str1[i] && str2[i])
	{
		if (ptr1[i] == ptr2[i])
			i++;
		else if (ptr1[i] > ptr2[i])
			return (ptr1[i] - ptr2[i]);
		else
			return (ptr2[i] - ptr1[i]);
	}
	return (0);
}

int		pass_space(char *substr)
{
	int start;

	start = 0;
	while (substr[start] == ' ' || substr[start] == '\t')
		start++;
	return (start);
}

int	count_comma(char *substr)
{
	int start;
	int count_comma;

	start = 0;
	count_comma = 0;
	while (substr[start])
	{
		if (substr[start] == ',')
			count_comma++;
		start++;
	}
	return (count_comma);
}
