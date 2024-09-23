#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <random>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

#include "libs/base64.hpp"

std::string input;

std::string generateFileName(int length)
{


    const std::string CHARACTERS
        = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv"
          "wxyz0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<> distribution(
        0, CHARACTERS.size() - 1);

    std::string random_string;
    for (int i = 0; i < length; ++i) {
        random_string
            += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

void encrypt() {
    int length = 6;
    std::string input;
    
    std::cout << "Enter your desired string" << std::endl;
    std::cin >> input;

    auto encoded_str = base64::to_base64(input);

    std::string directory = "texts";
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directory(directory);
    }

    std::ofstream encryptedFile(directory + "/" + generateFileName(length) + ".txt");
    encryptedFile << encoded_str;
    encryptedFile.close();

    std::cout << "Successfully encrypted string in base64 and saved to texts directory" << std::endl;
}

std::string readFileToString(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();    
}

void decrypt() {
    std::cout << "Type the filename you want to decrypt (without extension): ";
    std::string input;
    std::cin >> input;

    std::string directory = "texts/";
    std::string filePath = directory + input + ".txt";

    try {
        if (!std::filesystem::exists(filePath)) {
            throw std::runtime_error("File does not exist.");
        }
        std::string decryptedText = readFileToString(filePath);
        auto decoded_str = base64::from_base64(decryptedText);

        std::cout << "Decrypted content: " << decoded_str << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void getUserChoice() {
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "[1] Encrypt" << std::endl;
    std::cout << "[2] Decrypt" << std::endl;

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Encrypt selected." << std::endl;
        encrypt();
    } else if (choice == 2) {
        std::cout << "Decrypt selected." << std::endl;
        decrypt();
    } else {
        std::cout << "Invalid input. Please enter 1 or 2." << std::endl;
        getUserChoice();
    }
}

int main() {
    getUserChoice();
}