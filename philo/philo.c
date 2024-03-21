/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:31 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/21 21:50:04 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_thread(t_thread *ph)
{
	int	i;

	i = ph[0].info.num_philo;
	pthread_mutex_destroy(ph[0].print);
	pthread_mutex_destroy(ph[0].count_mutex);
	pthread_mutex_destroy(ph[0].flag_mutex);
	free(ph[0].print);
	free(ph[0].count_mutex);
	free(ph[0].flag_mutex);
	free(ph[0].count_eat);
	free((void *)ph[0].flag);
	while (--i >= 0)
	{
		pthread_mutex_destroy(ph[i].left_fork);
		free(ph[i].left_fork);
		free(ph[i].left_f);
	}
}

void	thread_create(t_thread *ph, pthread_t **th_name)
{
	long	i;

	i = 0;
	while (i < ph[0].info.num_philo)
	{
		th_name[i] = (pthread_t *)malloc(sizeof(pthread_t));
		pthread_create(th_name[i], NULL, philo, (void *)(&ph[i]));
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < ph[0].info.num_philo)
	{
		pthread_join(*th_name[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pthread_t		**th_name;
	t_thread		*ph;

	ph = init_thread(argc, argv);
	if (ph == NULL)
		return (1);
	th_name = (pthread_t **)malloc(sizeof(pthread_t *) * ph[0].info.num_philo);
	thread_create(ph, th_name);
	free_thread(ph);
	free(ph);
	free(th_name);
	return (0);
}
