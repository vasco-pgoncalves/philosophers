/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 17:28:12 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/30 01:03:25 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_table(void	*data)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	i = -1;
	table = (t_table *)data;
	while (++i < table->philo_nb)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo ->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->table_mutex, DESTROY);
	safe_mutex_handle(&table->print_mutex, DESTROY);
	free(table->philos);
	free(table->forks);
}
