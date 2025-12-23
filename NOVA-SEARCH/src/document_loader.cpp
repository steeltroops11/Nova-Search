#include "document_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>

std::vector<Document> DocumentLoader::loadDocuments(const std::string& directoryPath) {
    std::vector<Document> documents;
    int docId = 0;

    std::string searchPath = directoryPath + "\\*.txt";
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open directory: " << directoryPath << std::endl;
        return documents;
    }

    do {
        std::string filePath = directoryPath + "\\" + findData.cFileName;
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            continue;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        Document doc;
        doc.id = docId++;
        doc.content = buffer.str();
        documents.push_back(doc);

    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
    return documents;
}
