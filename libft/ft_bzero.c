/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:07:22 by aharder           #+#    #+#             */
/*   Updated: 2024/10/29 13:30:57 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_bzero(void *ptr, int size)
{
	unsigned char	*ptr2;
	int				i;

	i = 0;
	ptr2 = (unsigned char *) ptr;
	while (i < size)
	{
		ptr2[i] = 0;
		i++;
	}
	return (ptr);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int array [] = { 54, 85, 20, 63, 21 };
    size_t size = sizeof( int ) * 4;
    int length;

    for( length=0; length<5; length++) {
        printf( "%d ", array[ length ] );
    }
    printf( "\n" );

    ft_bzero( array, size );

    for( length=0; length<5; length++) {
        printf( "%d ", array[ length ] );
    }
    printf( "\n" );
    
    return 0;
}

int main() {

    char array [] = { "reifeuier" };
    int length;

    for( length=0; length<9; length++) {
        printf( "%c ", array[ length ] );
    }
    printf( "\n" );
//	printf("size : %zu", size);
	ft_bzero( array, 4 );

    for( length=0; length<9; length++) {
        printf( "%c ", array[ length ] );
    }
    printf( "\n" );
    
    return 0;
}*/
