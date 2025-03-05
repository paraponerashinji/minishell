/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:38:35 by aharder           #+#    #+#             */
/*   Updated: 2024/10/29 14:53:52 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *ptr1, void *ptr2, int size)
{
	unsigned char	*ptr3;
	unsigned char	*ptr4;
	int				i;

	i = 0;
	ptr3 = (unsigned char *) ptr1;
	ptr4 = (unsigned char *) ptr2;
	while (i < size)
	{
		if (ptr3[i] != ptr4[i])
			return (ptr3[i] - ptr4[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main() {
   char str1[] = "12345678901400345678";
   char str2[] = "1234567";

   int result = ft_memcmp(str2, str1, 10);

   if (result < 0) {
       printf("First is less than second.\n");
   } else if (result == 0) {
       printf("First is equal to second.\n");
   } else {
       printf("First is greater than second.\n");
   }
    return 0;
}*/
