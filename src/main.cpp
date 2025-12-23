#include <iostream>
#include <vector>
#include <algorithm>

#include "document_loader.h"
#include "search_engine.h"
#include "neural_ranker.h"

int main() {
    // ==============================
    // CONFIGURATION
    // ==============================
    const bool ENABLE_TRAINING = false;   // KEEP FALSE for 100-doc dataset

    // ==============================
    // LOAD DOCUMENTS
    // ==============================
    std::vector<Document> documents =
        DocumentLoader::loadDocuments("data/docs");

    if (documents.empty()) {
        std::cerr << "No documents loaded. Check data/docs folder.\n";
        return 1;
    }

    // ==============================
    // INITIALIZE SEARCH ENGINE
    // ==============================
    SearchEngine engine(documents);

    // ==============================
    // INITIALIZE NEURAL RANKER
    // ==============================
    NeuralRanker neural;
    neural.initialize();
    neural.loadWeights("weights.txt");

    std::cout << "NOVA SEARCH (TF-IDF + Neural Re-Ranking)\n";
    std::cout << "--------------------------------------\n";

    // ==============================
    // OPTIONAL TRAINING PHASE
    // ==============================
    if (ENABLE_TRAINING) {
        std::cout << "\nStarting neural training...\n";

        struct TrainSample {
            std::string query;
            int docId;
            double target; // 1.0 = relevant, 0.0 = not relevant
        };

        std::vector<TrainSample> trainingData = {
            {"neural networks", 0, 1.0},
            {"neural networks", 1, 0.0},
            {"semantic search", 2, 1.0},
            {"semantic search", 1, 0.0}
        };

        const int epochs = 100;
        const double learningRate = 0.01;

        for (int epoch = 1; epoch <= epochs; ++epoch) {
            double totalLoss = 0.0;

            for (const auto& sample : trainingData) {
                auto tfidfResults = engine.search(sample.query);

                double tfidfScore = 0.0;
                for (const auto& r : tfidfResults) {
                    if (r.first == sample.docId) {
                        tfidfScore = r.second;
                        break;
                    }
                }

                totalLoss += neural.train(
                    sample.query,
                    documents[sample.docId],
                    tfidfScore,
                    sample.target,
                    learningRate
                );
            }

            if (epoch == 1 || epoch % 10 == 0) {
                std::cout << "Epoch " << epoch
                          << " | Avg Loss: "
                          << (totalLoss / trainingData.size())
                          << "\n";
            }
        }

        std::cout << "Neural training completed.\n";
    } else {
        std::cout << "\nNeural training disabled (inference-only mode).\n";
    }

    // ==============================
    // SEARCH LOOP
    // ==============================
    while (true) {
        std::string query;
        std::cout << "\nEnter query (or type 'exit'): ";
        std::getline(std::cin, query);

        if (query == "exit")
            break;

        auto tfidfResults = engine.search(query);
        std::vector<std::pair<int, double>> finalResults;

        for (const auto& r : tfidfResults) {
            double neuralScore =
                neural.score(query, documents[r.first], r.second);

            double finalScore = 0.7 * r.second + 0.3 * neuralScore;
            finalResults.push_back({r.first, finalScore});
        }

        std::sort(finalResults.begin(), finalResults.end(),
                  [](const auto& a, const auto& b) {
                      return a.second > b.second;
                  });

        std::cout << "\nSearch Results:\n";
        const int TOP_K = 10;

        for (int i = 0; i < std::min(TOP_K, (int)finalResults.size()); ++i) {
            std::cout << "Doc " << finalResults[i].first
                      << " | Score: " << finalResults[i].second << "\n";
        }        
    }

    // ==============================
    // SAVE WEIGHTS
    // ==============================
    neural.saveWeights("weights.txt");
    std::cout << "Weights saved. Exiting.\n";

    return 0;
}
