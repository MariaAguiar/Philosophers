/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:51:40 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/21 20:19:48 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	value;

	sign = 1;
	value = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		value = value * 10 + (*str++ - '0');
	if ((value * sign) > 2147483647 || (value * sign) < -2147483648)
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	return (value * sign);
}

static int	get_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;

	i = get_len(n);
	s = malloc(sizeof(char) * i + 1);
	if (!s)
		return (NULL);
	s[0] = '0';
	s[i] = '\0';
	if (n == -2147483648)
	{
		s[--i] = '8';
		n = n / 10;
	}
	if (n < 0)
	{
		s[0] = '-';
		n = n * -1;
	}
	while (n > 0 && i > 0)
	{
		s[--i] = n % 10 + '0';
		n = n / 10;
	}
	return (s);
}
