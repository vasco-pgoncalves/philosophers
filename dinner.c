/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:41:41 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/30 00:53:19 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//fake to lock the fork
//sleep until the monitor breaks
static void	*alone(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex,
		&philo->last_meal_time, get_time(MILLISECOND));
	add_to_long(&philo->table->table_mutex, &philo->table->threads_nb);
	print_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(300);
	return (NULL); 
}

static void	philo_eat(t_philo	*philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	print_status(TAKE_FIRST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	print_status(TAKE_SECOND_FORK, philo);

	set_long(&philo->philo_mutex,
		&philo->last_meal_time, get_time(MILLISECOND));
	philo->nb_meals_had++;
	print_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nb_limit_meals > 0
		&& philo->nb_meals_had == philo->table->nb_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);

	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
}
//TODO
static void	thinking(t_philo	*philo)
{
	print_status(THINKING, philo);
}

void	*dinner_simulation(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	add_to_long(&philo->table->table_mutex, &philo->table->threads_nb);

	// set to the last meal time

	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		philo_eat(philo);
		print_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

/* 
		./philo 5 200 100 100 [0]
		
	0)	if no meals [0] (return NULL;) back to main()
	0.1) if only 1 philo create an adoc function (hardcode)
	1) create all threads, all philos
	2) create a monitor thread -> search for dead philos
	3) syncronize the beginning of the simulation
		pthread_create -> philo starts to run!
		every philo starts  simultaniously
	4) join everyone
*/

void	diner_start(t_table	*table)
{
	int	i;

	i = -1;
	if (table->nb_limit_meals == 0)
		return ;
	else if (table->philo_nb == 1)
		safe_thread_handle(&table->philos[0].thread_id,
			alone, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nb)
			safe_thread_handle(&table->philos[i].thread_id,
				dinner_simulation, &table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nb)
		safe_thread_handle(&table->philos[i].thread_id,
			NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
