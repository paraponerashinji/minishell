/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:54:00 by aharder           #+#    #+#             */
/*   Updated: 2024/10/23 13:06:54 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
#include "libft.h"

void	*ft_memset(void *ptr, int value, int size)
{
	unsigned char	*ptr2;
	int				i;

	i = 0;
	ptr2 = (unsigned char *) ptr;
	while (i < size)
	{
		ptr2[i] = (unsigned char) value;
		i++;
	}
	return (ptr);
}
/*
int main() {

    char array [] = { "reifeuier" };
    int size = sizeof( char ) * 4;
    int length;

    for( length=0; length<9; length++) {
        printf( "%c ", array[ length ] );
    }
    printf( "\n" );
//	printf("size : %zu", size);
	ft_memset( array, '-', size );

    for( length=0; length<9; length++) {
        printf( "%c ", array[ length ] );
    }
    printf( "\n" );
    
    return 0;
}*/
/*
int main() {

    int array [] = { 54, 85, 20, 63, 21 };
    int size = sizeof( int ) * 2;
    int length;

    for( length=0; length<5; length++) {
        printf( "%d ", array[ length ] );
    }
    printf( "\n" );

    ft_memset( array, 0, size );

    for( length=0; length<5; length++) {
        printf( "%d ", array[ length ] );
    }
    printf( "\n" );
    
    return 0;
}*/
