/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:15:43 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 15:26:17 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*read_line(int fd, char *temp);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	*ft_memset(void	*src, int c, size_t len);

#endif
