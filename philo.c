/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:15:10 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/27 16:08:56 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		printf("incorect number of arguments\n");
		return (0);
	}
	// error handling
	ph_parsing(&table, argv);
	// creating and inicializing everything
	data_init(&table);
	// the actual simulation
	diner_start(&table);
	// free memory --> when all philos are full || when 1 philo dies
	clean(&table);
}
