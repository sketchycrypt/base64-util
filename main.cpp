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
    const std::string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv"
                                   "wxyz0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<> distribution(
        0, CHARACTERS.size() - 1);

    std::string random_string;
    for (int i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

void encode()
{
    int length = 6;
    std::string input;

    std::cout << "Enter your desired string" << std::endl;
    std::cin >> input;

    auto encoded_str = base64::to_base64(input);

    std::string directory = "texts";
    if (!std::filesystem::exists(directory))
    {
        std::filesystem::create_directory(directory);
    }

    std::ofstream encodedFile(directory + "/" + generateFileName(length) + ".txt");
    encodedFile << encoded_str;
    encodedFile.close();
    std::ofstream encodedFile(directory + "/" + generateFileName(length) + ".txt");
    encodedFile << encoded_str;
    encodedFile.close();

    std::cout << "Successfully encoded string in base64 and saved to texts directory" << std::endl;
    std::cout << "Successfully encoded string in base64 and saved to texts directory" << std::endl;
}

std::string readFileToString(const std::string &filePath)
{
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void decode()
{
    std::cout << "Type the filename you want to decode (without extension): ";
    std::string input;
    std::cin >> input;

    std::string directory = "texts/";
    std::string filePath = directory + input + ".txt";

    try
    {
        if (!std::filesystem::exists(filePath))
        {
            throw std::runtime_error("File does not exist.");
        }
        std::string decodedText = readFileToString(filePath);
        auto decoded_str = base64::from_base64(decodedText);
        std::string decodedText = readFileToString(filePath);
        auto decoded_str = base64::from_base64(decodedText);

        std::cout << "decodeed content: " << decoded_str << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void getUserChoice()
{
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "[1] Encode" << std::endl;
    std::cout << "[2] Decode" << std::endl;
    std::cout << "[1] Encode" << std::endl;
    std::cout << "[2] Decode" << std::endl;

    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        std::cout << "Encode selected." << std::endl;
        encode();
    }
    else if (choice == 2)
    {
        std::cout << "Decode selected." << std::endl;
        decode();
    }
    else
    {
        std::cout << "Invalid input. Please enter 1 or 2." << std::endl;
        getUserChoice();
    }
}

int main()
{
    getUserChoice();
}