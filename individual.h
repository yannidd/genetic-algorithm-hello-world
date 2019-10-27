#include <string>

#pragma once

class Individual {
public:
  std::string goal = "";
  std::string representation = "";
  int fitness = 0;
  int target_fitness = 0;

  std::string generateRandom(int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz ";
    std::string result(length, 0);

    for (int i = 0; i < length; i++) {
      result[i] = charset[rand() % (sizeof(charset) - 1)];
    }

    return result;
  }

  void evaluate() {
    int fitness = 0;
    for (int i = 0; i < this->representation.length(); i++) {
      if (this->representation[i] == this->goal[i]) fitness++;
    }
    this->fitness = fitness;
  }

  void mutate(int max_mutations = 1) {
    int n_mutations = rand() % (max_mutations + 1);

    for (int i = 0; i < n_mutations; i++) {
      int mutation_location = rand() % this->representation.length();

      this->representation[mutation_location] = this->generateRandom(1)[0];
    }
  }

  Individual(std::string goal) : goal(goal) {
    this->representation = generateRandom(goal.length());
    this->target_fitness = goal.length();
  }
};