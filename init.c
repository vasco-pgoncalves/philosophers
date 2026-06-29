/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:47:22 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/29 18:07:34 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork	*forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nb;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static void	philo_init(t_table	*table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nb)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->nb_meals_had = 0;
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

int	data_init(t_table	*table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->philos = safe_malloc_cleanup (sizeof(t_philo) * table->philo_nb,
			cleanup_table, table);
	mutex_handle(&table->table_mutex, INIT);
	table->forks = safe_malloc_cleanup (sizeof(t_fork) * table->philo_nb,
			cleanup_table, table);
	while (++i < table->philo_nb)
	{
		if (mutex_handle(&table->forks[i].fork, INIT) != 0)
		{
			// clean up and return an error
		}
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
