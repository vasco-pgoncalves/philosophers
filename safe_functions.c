/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:56:02 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/29 17:27:31 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
*	init
*	destroy
*	lock
*	unlock
*/

int	mutex_handle(t_mtx	*mutex, t_opcode	opcode)
{
	if (LOCK == opcode)
		pthread_mutex_lock(mutex);
	else if (UNLOCK == opcode)
		pthread_mutex_unlock(mutex);
	else if (INIT == opcode)
		pthread_mutex_init(mutex, NULL);
	else if (DESTROY == opcode)
		pthread_mutex_destroy(mutex);
	else
	{
		printf("wrong opcode for mutex handle");
		return (-1);
	}
	return (0);
}

void	*safe_malloc_cleanup(size_t size,
			void (*cleanup)(void *), void *data)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		if (cleanup)
			cleanup(data);
		return (NULL);
	}
	return (ptr);
}
