/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:41:45 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/30 00:42:40 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


//if the time from last meal > time_to_die philo dies
static bool	philo_died(t_philo	*philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISECOND)
		- get_long(&philo->philo_mutex, &philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void	*data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_nb, table->philo_nb))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nb && !simulation_finished(table))
		{
			if (philo_died(table->philos + i)) //TODO
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				print_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
