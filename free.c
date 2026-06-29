/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 17:28:12 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/29 17:31:59 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_table(void	*data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	// destroy mutexes etc...
}
