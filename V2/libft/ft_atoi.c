/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:22:40 by aharder           #+#    #+#             */
/*   Updated: 2024/10/29 14:18:23 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	output;
	int	posneg;

	output = 0;
	posneg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		posneg = posneg * -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		output = output * 10 + *str - '0';
		str++;
	}
	return (output * posneg);
}
/*
#include <stdio.h>
#include <stdlib.h>


int main( int argc, char * argv[] ) {

    if ( argc == 1 ) {
        printf( "Usage: %s intValue ...\n", argv[0] );
        exit( EXIT_SUCCESS );
    }
    argc--;   argv++;

    int sum = 0;

    while ( argc != 0 ) {

        sum += ft_atoi( *argv++ );
        argc--;

    }
    printf( "La somme des valeurs saisies est de %d.\n", sum );

    return EXIT_SUCCESS;
}
*/
