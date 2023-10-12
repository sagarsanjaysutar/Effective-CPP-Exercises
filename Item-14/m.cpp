#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Create an fstream object and open a file in read and write mode
    std::fstream file("random.txt", std::ios::in | std::ios::out);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    // Write data to the file
    file << "Hello, World!" << std::endl;

    // Seek to the beginning of the file
    file.seekg(0);

    // Read data from the file
    std::string line;
    std::getline(file, line);

    // Print the read data
    std::cout << "Read from file: " << line << std::endl;

    // Close the file
    file.close();

    return 0;
}
