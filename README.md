# Genetic Algorithms
This is an implementation of the "hello world" to genetic algorithms (GA). The GA has to evolve a string into `methinks it is like a weasel`. The fitness of an individual is equal to the number of matching characters between it and the final goal.

Two algorithms are implemented in this repository:
- Hill climber - Mutate a single individual until the goal is reached.
- Population - Do crossover and mutation on a population. The individuals are selected with tournament selection.

Below are shown the number of iterations (average of 500 runs) it took for both algorithms to reach the goal for different hyperparameters.

![alt text](eval.png "")
