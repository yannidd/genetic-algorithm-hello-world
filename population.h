#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "individual.h"

class Population {
public:
  int size = 0;
  int fitness = 0;
  int target_fitness = 0;
  int max_mutations = 0;
  std::vector<Individual> individuals = {};
  std::string goal = "";
  std::string representation = "";

  Individual doCrossover(Individual* left, Individual* right) {
    Individual child = Individual(this->goal);

    for (int i = 0; i < this->goal.length(); i++) {
      if (rand() % 2 == 0) {
        child.representation[i] = left->representation[i];
      }
      else {
        child.representation[i] = right->representation[i];
      }
    }

    child.evaluate();

    return child;
  }

  void runTournament(bool crossover = true) {
    Individual* parent0 = nullptr;
    Individual* parent1 = nullptr;
    Individual* child = nullptr;

    // Select strong parent 0.
    int rand_index_p0 = rand() % this->size;
    int rand_index_p1 = rand() % this->size;
    if (this->individuals[rand_index_p0].fitness > this->individuals[rand_index_p1].fitness) {
      parent0 = &this->individuals[rand_index_p0];
    }
    else {
      parent0 = &this->individuals[rand_index_p1];
    }

    // Select strong parent 1.
    rand_index_p0 = rand() % this->size;
    rand_index_p1 = rand() % this->size;
    if (this->individuals[rand_index_p0].fitness > this->individuals[rand_index_p1].fitness) {
      parent1 = &this->individuals[rand_index_p0];
    }
    else {
      parent1 = &this->individuals[rand_index_p1];
    }

    // Select weak child.
    rand_index_p0 = rand() % this->size;
    rand_index_p1 = rand() % this->size;
    if (this->individuals[rand_index_p0].fitness > this->individuals[rand_index_p1].fitness) {
      child = &this->individuals[rand_index_p1];
    }
    else {
      child = &this->individuals[rand_index_p0];
    }

    *child = this->doCrossover(parent0, parent1);
    child->mutate(this->max_mutations);
    child->evaluate();

    if (child->fitness > this->fitness) {
      this->fitness = child->fitness;
      this->representation = child->representation;
    }

  }

  Population(std::string goal, int size = 500, int max_mutations = 1) : size(size), goal(goal), max_mutations(max_mutations) {
    for (int i = 0; i < size; i++) {
      Individual individual = Individual(goal);
      individual.evaluate();
      if (individual.fitness > this->fitness) {
        this->fitness = individual.fitness;
        this->representation = individual.representation;
      }

      this->individuals.push_back(individual);
    }
    this->target_fitness = goal.length();
  }
};