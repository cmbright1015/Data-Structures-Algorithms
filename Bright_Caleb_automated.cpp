#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

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

int main() {
    std::vector<int> sizes = {10, 100, 1000};
    std::ofstream execution_time("Bright_Caleb_executionTime.txt");
    execution_time << "InputSize\tExecution Time in Microseconds\n";

    for (int size : sizes) {
        for (int i = 1; i <= 25; ++i) {
            std::stringstream input_name;
            input_name << "Bright_Caleb_input_" << size << "_" << i << ".txt";
            std::stringstream output_name;
            output_name << "Bright_Caleb_output_" << size << "_" << i << ".txt";

            std::ifstream inFile(input_name.str());
            if (!inFile) {
                std::cerr << "Error opening file '" << input_name.str() << "'.\n";
                continue;
            }

            std::vector<double> data;
            double value;

            while (input_name >> value) {
                data.push_back(value);
            }
            inFile.close();

            if (!inFile.eof()) {
                std::cerr << "Failed reading file '" << input_name.str() << "'.\n";
                continue;
            }

            auto start_clock = std::chrono::high_resolution_clock::now();
            if (!data.empty()) {
                quickSort(data, 0, static_cast<int>(data.size()) - 1);
            }
            auto end_clock = std::chrono::high_resolution_clock::now();
            auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_clock - start_clock).count();
            
            std::ofstream outFile(output_name.str());
            if (!outFile) {
                std::cerr << "Error opening file '" << output_name.str() << "'.\n";
                continue;
            }

            outFile << std::fixed << std::setprecision(6);
            for (std::size_t j = 0; j < data.size(); ++j) {
                outFile << data[j];
                if (j + 1 < data.size()) outFile << ' ';
            }
            outFile << '\n';
            outFile.close();

            execution_time << size << "\t" << microseconds << "\n";
        }
    }

    execution_time.close();

    std::ifstream exTimeFile("Bright_Caleb_executionTime.txt");
    std::ofstream averageTime("Bright_Caleb_averageExecutionTime.txt");

    averageTime << "Input Size\t Average Execution Time in Microseconds\n";
    std::string header;
    std::getline(exTimeFile, header);

    for (int size : sizes) {
        exTimeFile.clear();
        exTimeFile.seekg(0);
        std::getline(exTimeFile, header);

        double sum = 0;
        int count = 0;
        int s;
        long long t;
        while (exTimeFile >> s >> t) {
            if (s == size) {
                sum += t;
                count++;
            }
        }

        if (count > 0) {
            averageTime << size << "\t" << (sum / count) << "\n";
        }
    }

    averageTime.close();

    std::cout << "Files generated and sorted\n";

    return 0;
}