/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:27:26 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/02 23:30:25 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define INT_MAX	2147483647
# define INT_MIN	-2147483648
# define THOUSAND	1000
# define TRUE		1
# define FALSE		0

typedef struct s_info {
	long	num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_must_eat;
} t_info;

typedef struct s_thread {
	pthread_mutex_t	*print;
	pthread_mutex_t	*count_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info	info;
	long	*left_f;
	long	*right_f;
	long	ph_name;
	long	*count_eat;

} t_thread;

int	ft_islong(const char *str);
long	ft_atol(const char *str);
long	ft_now_microsec(void);
void	*philo(void *input);

#endif
