# A base64 encoder and decoder program using pybase64 library in Python
# Author: Russel Yasol
# Date: 2023-06-10
# Version: 1.0.0
# Usage: python3 base64.py

# Import libraries
import os
import base64
import pybase64

# Function definitions

# This function clears the terminal screen
def clear_screen():
    try:
        os.system('clear')  # For Linux/macOS
    except:
        os.system('cls')  # For Windows

# This function pauses the terminal screen
def terminal_pause():
    input("Press enter to continue...")

# These 2 functions encodes and decodes a string using the base64 algorithm
# I used the pybase64 library for this function.
# The pybase64 library is a wrapper for the base64 library.
# The pybase64 library will handle the encoding and decoding for us.
def encode(input_str):
    encoded_bytes = pybase64.b64encode(input_str.encode('utf-8'))
    encoded_str = encoded_bytes.decode('utf-8')
    return encoded_str

def decode(input_str):
    decoded_bytes = pybase64.b64decode(input_str.encode('utf-8'))
    decoded_str = decoded_bytes.decode('utf-8')
    return decoded_str

# This function displays the results of the encoded and decoded strings
# It also gives the user the option to save the results to a file
# The results are saved to a file in the same directory as the program
# The results are saved to a text file with the extension .txt
def display_results(encoded_results_arr, decoded_results_arr):
    
    print("\nHere are your results:\n")
    print("Encoded Results:")
    for i, result in enumerate(encoded_results_arr):
        if result is not None:
            print(f"Result {i + 1}: {result}")
    
    print("\nDecoded Results:")
    for i, result in enumerate(decoded_results_arr):
        if result is not None:
            print(f"Result {i + 1}: {result}")
            
    choice = input("\n\nDo you want to save these results to a file?\n1. Yes\n2. No\nEnter your choice: ")

    if choice == "1":
        file_name = input("Please enter a file name: ") + ".txt"

        with open(file_name, "w") as file:
            file.write("Here are your encoded results:\n")
            for i, result in enumerate(encoded_results_arr):
                if result is not None:
                    file.write(f"Result {i + 1}: {result}\n")

            file.write("\nHere are your decoded results:\n")
            for i, result in enumerate(decoded_results_arr):
                if result is not None:
                    file.write(f"Result {i + 1}: {result}\n")

        print(f"Results saved to file {file_name}")
    else:
        print("Results not saved to file. Exiting...")

# Main program
# This is the main program loop
# The user will be presented with a menu
# The user will choose an option from the menu
# The user can encode or decode a string
# I used array variables to store the results of the encoded and decoded strings
if __name__ == "__main__":
    clear_screen()
    user_choice = 0

    max_results = 100
    encoded_results_arr = [None] * max_results
    decoded_results_arr = [None] * max_results
    result_index_enc = 0
    result_index_dec = 0

    while user_choice != "4":
        try:
            os.system('clear')  # For Linux/macOS
        except:
            os.system('cls')  # For Windows

        print("========================================================================")
        print("Welcome to the Base64 Encoder/Decoder!")
        print("This program will encode or decode a string using the Base64 algorithm.")
        print("========================================================================\n")

        print("Please choose an option:")
        print("1. Encode")
        print("2. Decode")
        print("3. Display results")
        print("4. Exit")
        user_choice = input("Enter your choice: ")

        if user_choice == "1":
            print("\nYou have chosen to encode a string.")
            input_str = input("Please enter a message: ")
            encoded_result = encode(input_str)
            print("========================================================================")
            print("This is the encoded base64 message:", encoded_result)
            print("========================================================================")
            terminal_pause()
            encoded_results_arr[result_index_enc] = encoded_result
            result_index_enc += 1
        elif user_choice == "2":
            print("\nYou have chosen to decode a string.")
            input_str = input("Please enter a base64 string: ")
            decoded_result = decode(input_str)
            print("========================================================================")
            print("This is the decoded message from base64 string:", decoded_result)
            print("========================================================================")
            terminal_pause()
            decoded_results_arr[result_index_dec] = decoded_result
            result_index_dec += 1
        elif user_choice == "3":
            clear_screen()
            display_results(encoded_results_arr, decoded_results_arr)
            terminal_pause()
        elif user_choice == "4":
            clear_screen()
            print("You have chosen to exit the program.")
        else:
            print("Invalid choice. Please try again.")
            terminal_pause()
