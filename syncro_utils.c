/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:49:26 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/30 02:10:08 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_threads_running(t_mtx	*mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

// loop until all philos are in sync
void	wait_all_threads(t_table	*table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

// increase the nb of threads that are running to sync with the monitor

void	add_to_long(t_mtx	*mutex, long	*value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

// Make the system fair when running odd philo_nb

void	de_sync_philos(t_philo	*philo)
{
	if (philo->table->philo_nb % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->table->philo_nb % 2)
			thinking(philo, true);
	}
}
