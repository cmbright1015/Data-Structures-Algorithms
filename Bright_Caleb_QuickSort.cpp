//Caleb Bright
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>


int medianThree(std::vector<double> &a, int left, int right) {
    // middle index
    int middle = left + (right - left) / 2;

    // left <= middle <= right
    if (a[left] > a[middle]) {
        std ::swap(a[left], a[middle]);
    }
    if (a[left] > a[right]) {
        std::swap(a[left], a[right]);
    }
    if (a[middle] > a[right]) {
        std::swap(a[middle], a[right]);
    }

    // middle is moved to the left so we can use it as the pivot
    std::swap(a[left], a[middle]);
    return left;
}

int part(std::vector<double> &a, int left, int right) {
    // if <2 just sort them
    if (right - left + 1 <= 2) {
        if (a[left] > a[right]) {
            std::swap(a[left], a[right]);
        }
        return (left + right) / 2;
    }

    int pivotI = medianThree(a, left, right);
    double pivot = a[pivotI];

    // move i to the right and move j to the left
    int i = left + 1;
    int j = right;

    // move i forward if a[i] <= pivot and j has not been crossed
    // then move j backwards if a[j] >= pivot and i has not been crossed
    while(true) {
        while (i <= j && a[i] <= pivot)
            ++i;
        while (j >= i && a[j] > pivot)
            --j;
        if (i >= j) {
            break;
        }
        std::swap(a[i], a[j]);
    }
    std::swap(a[left], a[j]);
    return j;
}

void quickSort(std::vector<double> &a, int left, int right) {
    if (left >= right) {
        return;
    }
    // partition the array and find the pivot's final position
    // sort the left and right parts using recursion
    int pivot_position = part(a, left, right);
    quickSort(a, left, pivot_position - 1);
    quickSort(a, pivot_position + 1, right);
}

int main(int argc, char *argv[]) {
    // program, input file, output file
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input.txt output.txt\n";
        return 1;
    }

    // get input and output from the arugments
    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];

    std::ifstream inFile(inputFileName);
    if(!inFile) {
        std::cerr << "Error opening input file '" << inputFileName << "' .\n";
        return 1;
    }

    std::vector<double> data;
    double value;

    // reading the file until it fails
    while (inFile >> value) {
        data.push_back(value);
    }
    inFile.close();

    // if the reading didn't end because of EOF there was a different error
    if (!inFile.eof()) {
        std::cerr << "Failed reading input file\n";
        return 1;
    }

    // record time before and after
    // sort if there is at least one item
    auto start = std::chrono::high_resolution_clock::now();
    if (!data.empty()) {
        quickSort(data, 0, static_cast<int>(data.size()) - 1);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // output file open fail
    std::ofstream outFile(outputFileName);
    if (!outFile) {
        std::cerr << "Error opening output file '" << outputFileName << "'.\n";
        return 1;
    }

    // 6 digits after the decimal point
    // the sorted values are put into the output file
    outFile << std::fixed << std::setprecision(6);
    for (std::size_t i = 0; i < data.size(); ++i) {
        outFile << data[i];
        if (i + 1 < data.size()) outFile << ' ';
    }
    outFile << '\n';
    outFile.close();

    std::cout << microseconds << std::endl;

    return 0;
}