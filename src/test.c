

/* int	check_death_status(t_mouvmt *philo)
{
	int	status;

	pthread_mutex_lock(&philo->donner->verify_if_death);
	status = philo->donner->death_statu;
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (status != 0);
}

int	check_meals_eaten(t_mouvmt *philo)
{
	int	status;

	pthread_mutex_lock(&philo->donner->food_to_eat);
	status = philo->donner->max_food_to_eat;
	pthread_mutex_unlock(&philo->donner->food_to_eat);
	return (status != 0);
}

int	check_maxmeals_eaten(t_mouvmt *philo)
{
	int	food_to_eat;
	int	eat_more;

	pthread_mutex_lock(&philo->donner->food_to_eat);
	food_to_eat = philo->eating_time;
	eat_more = (food_to_eat < philo->donner->max_food_to_eat);
	pthread_mutex_unlock(&philo->donner->food_to_eat);
	return (eat_more);
}

void	check_philo_death(t_mouvmt *philo, uint64_t current_time)
{
	if (philo->donner->death_statu == 0)
	{
		philo->donner->death_statu = 1;
		pthread_mutex_lock(&philo->donner->afficher);
		if (check_maxmeals_eaten(philo) == 0)
		{
			pthread_mutex_unlock(&philo->donner->afficher);
			pthread_mutex_unlock(&philo->donner->verify_if_death);
			return ;
		}
		printf("im here");
		printf("%llu %d %s\n", current_time, philo->num_philo, "died");
		pthread_mutex_unlock(&philo->donner->afficher);
	}
}

int	check(t_mouvmt *philo)
{
	uint16_t	cur_time;
	int			must_die;

	must_die = 0;
	pthread_mutex_lock(&philo->donner->time);
	cur_time = time_in_milis() - philo->time_to_start;
	pthread_mutex_unlock(&philo->donner->time);
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (philo->eating_time >= philo->donner->max_food_to_eat)
	{
		must_die = 1;
		philo->donner->death_statu = 0;
	}
	if (!must_die && cur_time > philo->donner->time_to_die)
	{
		must_die = 1;
		printf("im here");
		check_philo_death(philo, cur_time);
	}
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (must_die);
}


int main() {
    t_donnee donner;
    t_mouvmt philo;
    
    // Initialize donner
    donner.time_to_sleep = 1000;
    donner.time_to_die = 2000;
    donner.time_to_eat = 1000;
    donner.time_to_start = time_in_milis();
    donner.num_of_philosophers = 1;
    donner.death_statu = 0;
    donner.max_food_to_eat = 5;
    donner.finish = 0;
    pthread_mutex_init(&donner.afficher, NULL);
    pthread_mutex_init(&donner.verify_if_death, NULL);
    pthread_mutex_init(&donner.food_to_eat, NULL);
    pthread_mutex_init(&donner.eating, NULL);
    pthread_mutex_init(&donner.time, NULL);

    // Initialize philosopher
    philo.donner = &donner;
    philo.num_philo = 1;
    philo.eating_time = 0;
    philo.eating_statu = 0;
    philo.time_to_sleep = 1000;
    philo.time_to_die = 2000;
    philo.time_to_eat = 1000;
    philo.time_to_start = time_in_milis();
    pthread_mutex_init(&philo.right_fork, NULL);

    pthread_mutex_t fork_left;
    pthread_mutex_init(&fork_left, NULL);
    philo.left_fork = &fork_left;

    // Simulate a philosopher's actions
    printf("Starting test...\n");

    // Simulate the philosopher's actions
    while (1) {
        printf("Checking death status: %d\n", check_death_status(&philo));
        printf("Checking meals eaten status: %d\n", check_meals_eaten(&philo));
        printf("Checking max meals eaten: %d\n", check_maxmeals_eaten(&philo));
        printf("Checking philosopher status: %d\n", check(&philo));
        
        if (check_death_status(&philo) == 1 || check_meals_eaten(&philo) == 0) {
            break;
        }
        
        ft_usleep(500);  // Sleep for half a second between checks
    }

    printf("Test completed.\n");

    // Clean up
    pthread_mutex_destroy(&philo.right_fork);
    pthread_mutex_destroy(&fork_left);
    pthread_mutex_destroy(&donner.afficher);
    pthread_mutex_destroy(&donner.verify_if_death);
    pthread_mutex_destroy(&donner.food_to_eat);
    pthread_mutex_destroy(&donner.eating);
    pthread_mutex_destroy(&donner.time);

    return 0;
} */