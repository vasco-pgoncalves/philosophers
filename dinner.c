/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:41:41 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/29 18:27:38 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*dinner_simulation(void	*data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	
	
	
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
	{
		//later
	}
	else
	{
		while (++i < table->philo_nb)
			safe_thread_handle(&table->philos[i].thread_id,
				dinner_simulation, &table->philos[i], CREATE);
	}

}
