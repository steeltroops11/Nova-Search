# NOVA SEARCH  
### A Mini Semantic Search Engine in C++ with Neural Re-Ranking

---

## 📌 Overview

**NOVA SEARCH** is a mini semantic search engine implemented in **C++**.  
It combines classical **TF-IDF–based information retrieval** with a lightweight **neural re-ranking model** to improve document relevance.

The project is designed as an **educational prototype**, focusing on:
- Search engine internals
- Ranking algorithms
- Neural scoring logic
- Clean system-level implementation in C++

---

## 🚀 Features

- Document ingestion from text files
- Tokenization and inverted index construction
- TF-IDF scoring with cosine similarity
- Neural re-ranking using a shallow feed-forward network
- Optional neural training (demonstration mode)
- Inference-only mode for large datasets
- Top-K ranked search results
- Fully implemented from scratch in C++

---

## 🧠 System Architecture

Query
↓
Tokenizer
↓
TF-IDF Scoring (Cosine Similarity)
↓
Neural Re-Ranking (Inference)
↓
Final Ranked Results


---

## 📂 Project Structure

NOVA-SEARCH/
├── src/
│ ├── main.cpp
│ ├── document_loader.cpp
│ ├── tokenizer.cpp
│ ├── indexer.cpp
│ ├── tfidf.cpp
│ ├── search_engine.cpp
│ └── neural_ranker.cpp
│
├── include/
│ ├── document.h
│ ├── document_loader.h
│ ├── tokenizer.h
│ ├── indexer.h
│ ├── tfidf.h
│ ├── search_engine.h
│ └── neural_ranker.h
│
├── data/
│ └── docs/
│ ├── doc1.txt
│ ├── doc2.txt
│ ├── ...
│ └── doc100.txt
│
├── weights.txt
├── nova_search.exe
└── README.md


---

## 📊 Dataset

The dataset consists of **100 synthetically generated text documents**, organized into **topic-based buckets** to introduce controlled diversity and enable meaningful ranking behavior.

### Topic Buckets

The documents are evenly distributed across the following domains:

- **Machine Learning** (20 documents)  
- **Neural Networks** (20 documents)  
- **Natural Language Processing (NLP)** (20 documents)  
- **Search Engines & Information Retrieval** (20 documents)  
- **Data Science & Analytics** (20 documents)

Each document within a bucket focuses on the same domain but may differ slightly in phrasing and emphasis. This design ensures that:
- Queries activate **topic-relevant subsets** of documents
- TF-IDF correctly prioritizes domain-specific terms
- Neural re-ranking operates on meaningful relevance signals

### Design Rationale

The dataset is **synthetic and domain-focused by design**, allowing controlled evaluation of ranking behavior without noise from real-world data. This approach helps demonstrate:
- Deterministic and explainable relevance scoring
- Proper separation of topics during search
- Stability of inference-only neural re-ranking on larger datasets

This dataset design reflects how real-world search systems rely on **clean, structured corpora** during development and testing.


## ▶️ How to Build and Run

### Compile
```powershell
g++ -std=gnu++17 -Iinclude src/main.cpp src/document_loader.cpp src/tokenizer.cpp src/indexer.cpp src/tfidf.cpp src/search_engine.cpp src/neural_ranker.cpp -o nova_search.exe

 Run
.\nova_search.exe

🔍 Example Queries

Use multi-word technical queries for best results:

neural networks

machine learning algorithms

semantic search

information retrieval

natural language processing

🎯 Limitations

No deep learning frameworks (by design)

No large-scale labeled training data

Semantic understanding limited to engineered features

These constraints are intentional to emphasize core algorithmic understanding.

🏁 Conclusion

NOVA SEARCH demonstrates how classical information retrieval techniques can be combined with neural scoring to build a functional and extensible search engine in C++. The project emphasizes correctness, clarity, and system-level understanding over black-box AI.

