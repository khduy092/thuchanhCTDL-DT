#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Chia tệp thành các phần nhỏ
void splitFile(const string &inputFile, vector<string> &tempFiles, int chunkSize) {
    ifstream inFile(inputFile);
    vector<int> buffer(chunkSize);
    int num;
    int fileIndex = 0;

    while (inFile >> num) {
        buffer.clear();
        for (int i = 0; i < chunkSize && inFile >> num; i++) {
            buffer.push_back(num);
        }
        sort(buffer.begin(), buffer.end(), greater<int>());

        string tempFileName = "temp" + to_string(fileIndex++) + ".txt";
        ofstream tempFile(tempFileName);
        for (int val : buffer) {
            tempFile << val << " ";
        }
        tempFile.close();
        tempFiles.push_back(tempFileName);
    }
}

// Trộn các tệp nhỏ thành tệp đã sắp xếp
void mergeFiles(const vector<string> &tempFiles, const string &outputFile) {
    ofstream outFile(outputFile);
    vector<ifstream> streams;
    
    for (const string &file : tempFiles) {
        streams.emplace_back(file);
    }

    vector<int> values(streams.size(), INT_MIN);
    for (size_t i = 0; i < streams.size(); i++) {
        if (streams[i] >> values[i]);
    }

    while (true) {
        int maxIdx = -1, maxVal = INT_MIN;
        for (size_t i = 0; i < values.size(); i++) {
            if (values[i] > maxVal) {
                maxVal = values[i];
                maxIdx = i;
            }
        }

        if (maxIdx == -1) break;

        outFile << maxVal << " ";
        if (!(streams[maxIdx] >> values[maxIdx])) {
            values[maxIdx] = INT_MIN;
        }
    }

    outFile.close();
    for (auto &stream : streams) stream.close();
}
