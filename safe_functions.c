/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:56:02 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/29 22:30:33 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (printf("pthread_mutex_lock failed\n"), -1);
	}
	else if (opcode == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (printf("pthread_mutex_unlock failed\n"), -1);
	}
	else if (opcode == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (printf("pthread_mutex_init failed\n"), -1);
	}
	else if (opcode == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (printf("pthread_mutex_destroy failed\n"), -1);
	}
	else
		return (printf("wrong opcode for mutex handle\n"), -1);
	return (0);
}

int	safe_thread_handle(pthread_t *thread, void *(*wildcard)(void *),
					void *arg, t_opcode opcode)
{
	if (opcode == CREATE)
	{
		if (pthread_create(thread, NULL, wildcard, arg) != 0)
			return (printf("pthread_create failed\n"), -1);
	}
	else if (opcode == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			return (printf("pthread_join failed\n"), -1);
	}
	else if (opcode == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			return (printf("pthread_detach failed\n"), -1);
	}
	else
		return (printf("wrong opcode for thread handle\n"), -1);
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
