#ifndef NEURAL_RANKER_H
#define NEURAL_RANKER_H

#include <vector>
#include <string>
#include "document.h"

class NeuralRanker {
public:
    void initialize();
    void loadWeights(const std::string& file);
    void saveWeights(const std::string& file);

    double score(const std::string& query,
                 const Document& doc,
                 double tfidfScore);

    // UPDATED: returns loss
    double train(const std::string& query,
                 const Document& doc,
                 double tfidfScore,
                 double target,
                 double learningRate);

private:
    std::vector<std::vector<double>> W1; // 4 x 8
    std::vector<double> B1;               // 8
    std::vector<double> W2;               // 8
    double B2;

    static double relu(double x);
    static double sigmoid(double x);
};

#endif
