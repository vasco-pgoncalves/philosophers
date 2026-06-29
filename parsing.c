/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:19:39 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/27 15:32:10 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *str)
{
	long int	nb;
	int			sign;

	nb = 0;
	sign = 1;
	while (ft_isspace((int)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = (-1);
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

static int	valid_input(char *arg)
{
	long	number;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	number = ft_atol(arg);
	if (number <= 0 || number / __LONG_MAX__ > 1)
		return (false);
	return (true);
}

static void	assign(t_table *table, char *argv[])
{
	table->philo_nb = atol(argv[1]);
	table->time_to_die = atol(argv[2]) * 1e3;
	table->time_to_eat = atol(argv[3]) * 1e3;
	table->time_to_sleep = atol(argv[4]) * 1e3;
	if (argv[5])
		table->nb_limit_meals = atol(argv[5]);
	else
		table->nb_limit_meals = -1;
}

bool	ph_parsing(t_table	*table, char	*argv[])
{
	if (!valid_input(argv[1]))
		return (printf("invalid number of philosophers\n"), 0);
	if (!valid_input(argv[2]))
		return (printf("invalid time to die\n"), 0);
	if (!valid_input(argv[3]))
		return (printf("invalid time to eat\n"), 0);
	if (!valid_input(argv[4]))
		return (printf("invalid time to sleep\n"), 0);
	if (argv[5])
		if (!valid_input(argv[5]))
			return (printf("Invalid number of repetitions\n"), 0);
	assign(table, argv);
	return (1);
}
