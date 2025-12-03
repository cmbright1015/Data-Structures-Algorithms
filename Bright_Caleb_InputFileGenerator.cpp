//Caleb Bright
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>
#include <array>

int main() {
    std::array<int, 3> sizes = {10, 100, 1000};
    const int numFiles = 25;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist (-100.0, 100.0);

    for (int n : sizes) {
        for (int i = 1; i <= numFiles; ++i) {
            std::ostringstream oss;
            oss << "Bright_Caleb_input_" << n << "_" << std::setw(2)
            << std::setfill('0') << i << ".txt";

            std::string fileName = oss.str();
            std::ofstream out(fileName);

            if (!out) {
                std::cerr << "Error opening file '" << fileName << "' .\n";
                return 1;
            }

            for (int j = 0; j < n; ++j) {
                double value = dist(gen);
                out << std::fixed << std::setprecision(6) << value;
                if (j + 1 < n) {
                    out << ' ';
                }
            }
            out << '\n';
            out.close();
        }
    }

    std::cout << "Input files generated\n";
    return 0;
}
