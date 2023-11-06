// ---------------------------------------------------------------------------
// This is a program that encodes and decodes a string using the Base64 algorithm.
// Author: Russel Yasol
// Last modified: 06/10/2023
// ---------------------------------------------------------------------------

// Includes and namespace
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>

// This function clears the input buffer since it causes some issues when using getline()
void clearUserInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// A simple function to clear the screen
// It uses ANSI escape codes to clear the screen
// Credit: https://stackoverflow.com/questions/17335816/clear-screen-using-c
void clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

// A simple function to pause the terminal
void terminalPause()
{
    std::cout << "Press enter to continue...";
    std::cin.get();
}

// This function encodes a string using the Base64 algorithm
/**
 *  This is the explanation of the encoding algorithm from Wikipedia:
 * The encoding process encodes 24-bit groups of input bits into output strings of 4 encoded characters.
 * 1. The 24-bit input is treated as 4 concatenated 6-bit groups, each of which is translated into a single digit in the base64 alphabet.
 * 2. Each 6-bit group is used as an index into an array of 64 printable characters.
 * 3. The character referenced by the index is placed in the output string.
 * 4. These four characters are concatenated to form the output string.
 * 5. If the number of input bytes is not a multiple of three, then the last group of 6-bit units is padded with one or two '=' signs to make the output length a multiple of 4 characters.
 * 6. If the number of input bytes is a multiple of three, then no padding is required.
 * 
*/

/**
 * Heres the breakdown of the encode function:
 * 1. We create a string called encoded to store the encoded string
 * 2. We create a string called base64_chars that contains the base64 alphabet
 * 3. We get the length of the input string
 * 4. We create a loop that will iterate through the input string
 * 5. We create a variable called chunk that will store the 24-bit group of input bits
 * 6. We create a variable called chunkSize that will store the size of the chunk
 * 7. We create a loop that will iterate through the input string and store the 24-bit group of input bits in the chunk variable
 * 8. We create a loop that will iterate through the 4 6-bit groups
 * 9. We create a variable called index that will store the index of the base64_chars string
 * 10. We create a variable called encodedChar that will store the encoded character
 * 11. We create a loop that will iterate through the 4 6-bit groups
 * 12. We create a variable called index that will store the index of the base64_chars string
 * 13. We create a variable called encodedChar that will store the encoded character
 * 14. We append the encodedChar to the encoded string
 * 15. We return the encoded string
*/
std::string encode(std::string const &input)
{
    std::string encoded;
    const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int inputLength = input.length();

    int i = 0;
    while (i < inputLength)
    {
        int chunk = 0;
        int chunkSize = 0;

        for (int j = 0; j < 3 && i < inputLength; j++)
        {
            chunkSize++;
            chunk = (chunk << 8) | static_cast<unsigned char>(input[i]);
            i++;
        }

        for (int j = 0; j < 4; j++)
        {
            if (j <= chunkSize)
            {
                int index = (chunk >> (6 * (3 - j))) & 0x3F;
                encoded += base64_chars[index];
            }
            else
            {
                encoded += '=';
            }
        }
    }
    return encoded;
}

// This function decodes a string using the Base64 algorithm
/**
 * This is the explanation of the decoding algorithm from Wikipedia:
 * The decoding process decodes 4 encoded characters into 3 bytes.
 * 1. Each encoded character in the input string is mapped to a 6-bit value.
 * 2. Each 6-bit value is used as an index into an array of 64 printable characters.
 * 3. The character referenced by the index is placed in the output string.
 * 4. These four characters are concatenated to form the output string.
 * 5. If the number of characters in the input string is not a multiple of 4, then '=' characters are appended to the end of the input string until the number of characters is a multiple of 4.
 * 6. If the last group of characters is '==' then the last two bytes of the last group are set to zero.
 * 7. If the last group of characters is '=' then the last byte of the last group is set to zero.
*/

/**
 * Heres the breakdown of the decode function:
 * 1. We create a string called decoded to store the decoded string
 * 2. We create a string called base64_chars that contains the base64 alphabet
 * 3. We get the length of the input string
 * 4. We create a loop that will iterate through the input string
 * 5. We create a variable called chunk that will store the 24-bit group of input bits
 * 6. We create a variable called chunkSize that will store the size of the chunk
 * 7. We create a loop that will iterate through the input string and store the 24-bit group of input bits in the chunk variable
 * 8. We create a loop that will iterate through the 4 6-bit groups
 * 9. We create a variable called index that will store the index of the base64_chars string
 * 10. We create a variable called decodedChar that will store the decoded character
 * 11. We append the decodedChar to the decoded string
 * 12. We return the decoded string
*/
std::string decode(std::string const &input)
{
    std::string decoded;
    const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int inputLength = input.length();
    int i = 0;

    while (i < inputLength)
    {
        int chunk = 0;
        int chunkSize = 0;

        for (int j = 0; j < 4 && i < inputLength; j++)
        {
            char c = input[i++];
            if (c == '=')
            {
                break;
            }
            chunkSize++;
            int index = base64_chars.find(c);
            chunk = (chunk << 6) | index;
        }

        for (int j = 0; j < chunkSize - 1; j++)
        {
            char decodedChar = (chunk >> (8 * (2 - j))) & 0xFF;
            decoded += decodedChar;
        }
    }

    return decoded;
}

// This function displays the results of the encoding and decoding
// It also gives the user the option to save the results to a file
void displayResults(const std::string encodedResultsArr[], const std::string decodedResultsArr[], int resultIndexEnc, int resultIndexDec)
{
    int choice;

    std::cout << "\n\nHere are your encoded results:\n";
    for (int i = 0; i < resultIndexEnc; i++)
    {
        std::cout << "Result " << (i + 1) << ": " << encodedResultsArr[i] << std::endl;
    }

    std::cout << "\nHere are your decoded results:\n";
    for (int i = 0; i < resultIndexDec; i++)
    {
        std::cout << "Result " << (i + 1) << ": " << decodedResultsArr[i] << std::endl;
    }

    std::cout << "\n\nDo you want to save these results to a file?\n";
    std::cout << "1. Yes\n";
    std::cout << "2. No\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Clear the input buffer after reading the choice
    clearUserInputBuffer();

    if (choice == 1) {
        std::string fileName;
        std::cout << "\nPlease enter a file name: ";
        std::getline(std::cin, fileName);
        fileName += ".txt";

        std::ofstream file(fileName);
        if (file.is_open())
        {
            file << "Here are your encoded results:\n";
            for (int i = 0; i < resultIndexEnc; i++)
            {
                file << "Result " << (i + 1) << ": " << encodedResultsArr[i] << std::endl;
            }
            
            file << "\n\nHere are your decoded results:\n";
            for (int i = 0; i < resultIndexDec; i++)
            {
                file << "Result " << (i + 1) << ": " << decodedResultsArr[i] << std::endl;
            }
            file.close();
            std::cout << "Results saved to file " << fileName << std::endl;
        }
        else
        {
            std::cout << "Unable to open file " << fileName << std::endl;
        }
    }

    else {
        std::cout << "\nResults not saved to file. Exiting...\n";
    }
}

// Main function
// This is where the program starts
int main()
{
    clearScreen();
    int userChoice;

    const int maxResults = 100;
    std::string encodedResultsArr[maxResults];
    std::string decodedResultsArr[maxResults];
    int resultIndexEnc = 0;
    int resultIndexDec = 0;

    do
    {
        clearScreen();
        std::cout <<"========================================================================\n";
        std::cout << "Welcome to the Base64 Encoder/Decoder!\n";
        std::cout << "This program will encode or decode a string using the Base64 algorithm.\n";
        std::cout <<"========================================================================\n\n";
        std::cout << "Please choose an option:\n";
        std::cout << "1. Encode\n";
        std::cout << "2. Decode\n";
        std::cout << "3. Display results\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> userChoice;

        // Clear the input buffer after reading the choice
        clearUserInputBuffer();

        switch (userChoice)
        {
        case 1:
        {
            std::cout << "\nYou have chosen to encode a string.\n";
            std::string input;
            std::cout << "Please enter a message: ";
            std::getline(std::cin, input);
            std::string encodedResult = encode(input);
            std::cout <<"\n========================================================================\n";
            std::cout << "This is the encoded base64 message: " << encodedResult << std::endl;
            std::cout <<"========================================================================\n";
            terminalPause();
            encodedResultsArr[resultIndexEnc] = encodedResult;
            resultIndexEnc++;
            break;
        }
        case 2:
        {
            std::cout << "\nYou have chosen to decode a string.\n";
            std::string input;
            std::cout << "Please enter a base64 string: ";
            std::getline(std::cin, input);
            std::string decodedResult = decode(input);
            std::cout <<"\n========================================================================\n";
            std::cout << "This is the decoded message from base64 string: " << decodedResult << std::endl;
            std::cout <<"========================================================================\n";
            terminalPause();
            decodedResultsArr[resultIndexDec] = decodedResult;
            resultIndexDec++;
            break;
        }
        case 3:
            clearScreen();
            displayResults(encodedResultsArr, decodedResultsArr, resultIndexEnc, resultIndexDec);
            terminalPause();
            break;
        case 4:
            clearScreen();
            std::cout << "You have chosen to exit the program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            terminalPause();
            break;
        }

    } while (userChoice != 3);

    return 0;
}
