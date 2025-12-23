#include "neural_ranker.h"
#include "tokenizer.h"
#include <cmath>
#include <algorithm>
#include <fstream>
void NeuralRanker::initialize() {
    W1 = {
        {0.3, 0.1, -0.2, 0.05, 0.4, -0.3, 0.2, 0.1},
        {0.2, -0.1, 0.3, 0.4, -0.2, 0.1, 0.05, -0.05},
        {0.1, 0.2, 0.1, -0.3, 0.3, 0.2, -0.1, 0.4},
        {0.4, -0.2, 0.2, 0.1, 0.1, -0.1, 0.3, 0.2}
    };

    B1 = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
    W2 = {0.2,-0.1,0.3,0.4,-0.2,0.1,0.2,0.3};
    B2 = 0.1;
}

double NeuralRanker::relu(double x) {
    return x > 0 ? x : 0;
}

double NeuralRanker::sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

static double sigmoidDerivative(double y) {
    return y * (1.0 - y);
}

double NeuralRanker::score(const std::string& query,
                           const Document& doc,
                           double tfidfScore) {

    auto qTokens = Tokenizer::tokenize(query);
    auto dTokens = Tokenizer::tokenize(doc.content);

    int overlap = 0;
    for (const auto& q : qTokens)
        if (std::find(dTokens.begin(), dTokens.end(), q) != dTokens.end())
            overlap++;

    std::vector<double> input = {
        tfidfScore,
        (double)qTokens.size(),
        (double)dTokens.size(),
        (double)overlap
    };

    std::vector<double> hidden(8,0), hiddenRaw(8,0);

    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 4; i++)
            hiddenRaw[j] += input[i] * W1[i][j];
        hiddenRaw[j] += B1[j];
        hidden[j] = relu(hiddenRaw[j]);
    }

    double outRaw = B2;
    for (int j = 0; j < 8; j++)
        outRaw += hidden[j] * W2[j];

    return sigmoid(outRaw);
}

double NeuralRanker::train(const std::string& query,
                           const Document& doc,
                           double tfidfScore,
                           double target,
                           double lr) {

    auto qTokens = Tokenizer::tokenize(query);
    auto dTokens = Tokenizer::tokenize(doc.content);

    int overlap = 0;
    for (const auto& q : qTokens)
        if (std::find(dTokens.begin(), dTokens.end(), q) != dTokens.end())
            overlap++;

    std::vector<double> input = {
        tfidfScore,
        (double)qTokens.size(),
        (double)dTokens.size(),
        (double)overlap
    };

    std::vector<double> hidden(8,0), hiddenRaw(8,0);

    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 4; i++)
            hiddenRaw[j] += input[i] * W1[i][j];
        hiddenRaw[j] += B1[j];
        hidden[j] = relu(hiddenRaw[j]);
    }

    double outRaw = B2;
    for (int j = 0; j < 8; j++)
        outRaw += hidden[j] * W2[j];

    double out = sigmoid(outRaw);

    // ---- LOSS ----
    double error = target - out;
    double loss = error * error;

    // ---- BACKPROP ----
    double deltaOut = error * sigmoidDerivative(out);

    for (int j = 0; j < 8; j++)
        W2[j] += lr * deltaOut * hidden[j];
    B2 += lr * deltaOut;

    for (int j = 0; j < 8; j++) {
        if (hiddenRaw[j] > 0) {
            double deltaH = deltaOut * W2[j];
            for (int i = 0; i < 4; i++)
                W1[i][j] += lr * deltaH * input[i];
            B1[j] += lr * deltaH;
        }
    }

    return loss;
}

void NeuralRanker::saveWeights(const std::string& file) {
    std::ofstream out(file);
    if (!out) return;

    for (auto& r : W1)
        for (double v : r) out << v << " ";
    out << "\n";

    for (double v : B1) out << v << " ";
    out << "\n";

    for (double v : W2) out << v << " ";
    out << "\n";

    out << B2;
}

void NeuralRanker::loadWeights(const std::string& file) {
    std::ifstream in(file);
    if (!in) return;

    for (auto& r : W1)
        for (double& v : r) in >> v;
    for (double& v : B1) in >> v;
    for (double& v : W2) in >> v;
    in >> B2;
}
