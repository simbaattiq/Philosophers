/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:52:01 by mel-atti          #+#    #+#             */
/*   Updated: 2024/12/11 06:54:20 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	input_checker(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (error_msg("Error: Invalid argument count"));
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdegit(av[i][j]) && !ft_issign(av[i][j]))
				return (error_msg("Invalid argument format"));
			if (av[i][j] == '-')
				return (error_msg("Use only positive numbers"));
		}
	}
	return (final_check(ac, av));
}

long long	ft_atol(char *nptr)
{
	long long		i;
	long long		sign;
	long long		res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r')))
		i++;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res *= 10;
		res += nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_isdegit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_issign(int c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}
