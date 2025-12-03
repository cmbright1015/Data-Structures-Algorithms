//Caleb Bright
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>
#include <array>
#include<cstdlib>
#include<ctime>

int main() {
    std::array<int, 3> sizes = {10, 100, 1000};
    const int numFiles = 25;

    srand(static_cast<unsigned>(time(nullptr)));

    for (int n : sizes) {
        for (int i = 1; i <= numFiles; ++i) {
            // builds the file names with the correct prefix
            std::ostringstream oss;
            oss << "Bright_Caleb_input_" << n << "_" << std::setw(2)
            << std::setfill('0') << i << ".txt";

            // convert to string and open the file
            std::string fileName = oss.str();
            std::ofstream out(fileName);

            if (!out) {
                std::cerr << "Error opening file '" << fileName << "' .\n";
                return 1;
            }

            for (int j = 0; j < n; ++j) {
                // convert to float in [-100,100] range
                double value = ((double)rand() / RAND_MAX) * 200.0 - 100.0;
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
