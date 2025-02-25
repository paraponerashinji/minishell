/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:31:54 by aharder           #+#    #+#             */
/*   Updated: 2024/11/14 11:12:02 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*init_file(int fd, char *file);
char	*pushingoutput(char *file);
char	*deletefile(char *file);

char	*ft_strchr2(char *str, int searchedChar);
int		ft_strlen2(const char *str);
char	*ft_strjoin2(char *dest, const char *src);
#endif
