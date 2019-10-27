#include <iostream>
#include <cstdlib>
#include <time.h>

#include "individual.h"
#include "population.h"

int runHillClimber(int max_mutations = 1) {
  Individual individual = Individual("methinks it is like a weasel");

  int n_iterations = 0;
  while (individual.fitness != individual.target_fitness) {
    Individual child = individual;
    child.mutate(max_mutations);

    individual.evaluate();
    child.evaluate();

    if (child.fitness > individual.fitness) individual = child;

    //printf("%10d %s fitness: %d\n", n_iterations, individual.representation.c_str(), individual.fitness);

    n_iterations++;
  }

  return n_iterations;
}

int runPopulation(int population_size = 500, int max_mutations = 1) {
  Population population = Population("methinks it is like a weasel", population_size, max_mutations);

  int n_iterations = 0;
  while (population.fitness != population.target_fitness) {
    population.runTournament();

    //printf("%10d %s fitness: %d\n", n_iterations, population.representation.c_str(), population.fitness);

    n_iterations++;
  }

  return n_iterations;
}

int main()
{
  srand(time(NULL));

  int stop = 500;
  std::vector<int> max_mutationss = { 1, 2, 3, 4 };
  //std::vector<int> population_sizes = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500 };
  std::vector<int> population_sizes = {};
  for (int i = 10; i <= 500; i += 10) {
    population_sizes.push_back(i);
  }

  // Hill climber.
  for (int j = 0; j < max_mutationss.size(); j++) {
    int max_mutations = max_mutationss[j];

    float hill_climber_iterations = runHillClimber(max_mutations);
    for (int i = 0; i < stop; i++) {
      float n_iterations = (float)runHillClimber(max_mutations);
      hill_climber_iterations -= hill_climber_iterations / stop;
      hill_climber_iterations += n_iterations / stop;
    }

    printf("%6d", (int)hill_climber_iterations);
  }
  printf("\n\n");

  // Population.
  for (int i = 0; i < population_sizes.size(); i++) {
    int population_size = population_sizes[i];
    
    for (int j = 0; j < max_mutationss.size(); j++) {
      int max_mutations = max_mutationss[j];

      float population_iterations = runPopulation(population_size, max_mutations);
      for (int i = 0; i < stop; i++) {
        float n_iterations = (float)runPopulation(population_size, max_mutations);
        population_iterations -= population_iterations / stop;
        population_iterations += n_iterations / stop;
      }
      
      printf("%6d", (int)population_iterations);
    }

    printf("\n");
  }
}
