// Header files
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <limits>
#include <stdexcept>
#include <string>
#include "liboai.h"
using namespace liboai;

// Function prototypes
int brainrotTranslator(Conversation &convo, std::string database);
int professionalBrainrotTranslator(Conversation &convo, std::string database);
int brainrotProfessor(Conversation &convo, std::string database);
void getTranslation(OpenAI &oai, Conversation &convo);
int getMenuChoice();

// Main function
int main() {
    // Instantiating a new object to access OpenAI
    OpenAI oai;
    // Set API key from environment variable, and checking to ensure the operation worked
    if (!oai.auth.SetKeyEnv("OPENAI_API_KEY")) {
        std::cerr << "API key not set!" << std::endl;
        return 1;
    }

    // Creating a new conversation
    Conversation convo;

    // Loading in a CSV database of brainrot terms for reference
    std::unordered_map<std::string, std::string> slang_db;
    std::ifstream file("Brainrot-terms-and-translations-database.csv");
    if (!file.is_open()) {
        throw std::runtime_error("Error: File could not open.");
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string phrase, translation;
        std::getline(ss, phrase, ',');
        std::getline(ss, translation, ',');
        slang_db[phrase] = translation;
    }

    // Building a prompt with the database entries for context
    std::string database = "Here is a database of Gen Z slang terms and their meanings:\n";
    int count = 0;
    for (const auto& [term, meaning] : slang_db) {
        if (count++ > 100) break; 
        database += term + ": " + meaning + "\n";
    }
    // Updating the conversation with the message, and checking to ensure it worked
    bool didOperationWork = convo.SetSystemData(database);
    if (!didOperationWork) {
        std::cerr << "ERROR: Failed to add database to system data!" << std::endl;
    }

    // Welcoming users to the program
    std::cout << "\nWelcome to the Brainrot Translator!\n\n";


    // Creating a variable to save the user's menu choice
    int botChoice;
    // A do-while loop which continuously takes user input until 4 is entered
    do {
        // Calling a function to display the menu and ensure the user only entered a single number
        botChoice = getMenuChoice();
        switch (botChoice) {
            case 1: 
                // Case 1: selecting the casual Brainrot Translator: calling the associated function
                brainrotTranslator(convo, database); 
                break;
            case 2: 
                // Case 1: selecting the Professional Brainrot Translator: calling the associated function
                professionalBrainrotTranslator(convo, database); 
                break;
            case 3: 
                // Case 1: selecting the Brainrot Professor: calling the associated function
                brainrotProfessor(convo, database); 
                break;
            case 4: 
                // Printing the user a farewell message before exiting the program
                std::cout << "\nThanks for using the Brainrot Translator, have a skibidi day!\n"; 
                break;
        }
        if (botChoice != 4) getTranslation(oai, convo);
    } while (botChoice != 4);


    return 0;
}


// Function declarations

// A function to carry out a translation for casual Brainrot Translator
int brainrotTranslator(Conversation &convo, std::string database){
    // Updating the context of the conversation based on the selection of bot
    std::string context = database + "You are a helpful bot that translates Gen Z slang, aka 'Brainrot,' to casual, converational terms.\n";    
    // Updating system data with new context, and making sure it worked
    bool didOperationWork = convo.ChangeFirstSystemMessage(context);
    if (!didOperationWork) {
        // Outputting an error if operation failed
        std::cerr << "\nERROR: Failed to set system data! \n\n";
    }
    else{ // If operation succeeded, continuing with the conversation
        // Clearing the buffer, and taking in the user's brainrot message
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string brainrotMessage;
        std::cout << "\nPlease enter a message with brainrot, and I'll translate it into casual language: \n";
        std::getline(std::cin, brainrotMessage);
        std::cout << std::endl;
        // Updating the conversation with the message, and checking to ensure it worked
        bool didOperationWork = convo.AddUserData(brainrotMessage);
        if (!didOperationWork) {
            std::cerr << "ERROR: Failed to update response data!" << std::endl;
        }
        // Returning the user's input to the while loop in main
        return 1;
    }
    // If the info update failed, ending the conversation
    return 4;
}

// A function to carry out a translation for Professional Brainrot Translator
int professionalBrainrotTranslator(Conversation &convo, std::string database){
    // Updating the context of the conversation based on the selection of bot
    std::string context = database + "You are a helpful bot that translates Gen Z slang, aka 'Brainrot', into professional language (for older generations in an working envirionment).\n";    
    // Updating system data with new context, and making sure it worked
    bool didOperationWork = convo.ChangeFirstSystemMessage(context);
    if (!didOperationWork) {
        // Outputting an error if operation failed
        std::cerr << "\nERROR: Failed to set system data! \n\n";
    }
    else{ // If operation succeeded, continuing with the conversation
        // Clearing the buffer, and taking in the user's brainrot message
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string brainrotMessage;
        std::cout << "\nPlease enter a message with brainrot, and I'll translate it into professional language: \n";
        std::getline(std::cin, brainrotMessage);
        std::cout << std::endl;
        // Updating the conversation with the message, and checking to ensure it worked
        bool didOperationWork = convo.AddUserData(brainrotMessage);
        if (!didOperationWork) {
            std::cerr << "\nERROR: Failed to update response data! \n\n";
        }
        // Returning the user's input to the while loop in main
        return 2;
    }
    // If the info update failed, ending the conversation
    return 4;
}

// A function to carry out a translation for the Brainrot Professor
int brainrotProfessor(Conversation &convo, std::string database){
    // Updating the context of the conversation based on the selection of bot
    std::string context = database + "You are a helpful bot that explains Gen Z slang, aka 'Brainrot', and gives an explanation and brief historical background in language that the older generation can understand.\n";    
    // Updating system data with new context, and making sure it worked
    bool didOperationWork = convo.ChangeFirstSystemMessage(context);
    if (!didOperationWork) {
        // Outputting an error if operation failed
        std::cerr << "\nERROR: Failed to set system data! \n\n";
    }
    else{ // If operation succeeded, continuing with the conversation
        // Clearing the buffer, and taking in the user's brainrot message
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string brainrotMessage;
        std::cout << "\nPlease enter a message with brainrot, and I'll explain it: \n";
        std::getline(std::cin, brainrotMessage);
        std::cout << std::endl;
        // Updating the conversation with the message, and checking to ensure it worked
        bool didOperationWork = convo.AddUserData(brainrotMessage);
        if (!didOperationWork) {
            std::cerr << "\nERROR: Failed to update response data! \n\n";
        }
        // Returning the user's input to the while loop in main
        return 3;
    }
    // If the info update failed, ending the conversation
    return 4;
}

// A function to get and display the translation for a user
void getTranslation(OpenAI &oai, Conversation &convo){
    // Calling the chat completion endpoint (defaults to GPT 3.5 Turbo), and catching any errors
    try {
        Response response = oai.ChatCompletion->create("gpt-3.5-turbo", convo);
        
        // Updating the conversation with the user's response (and checking to make sure it worked)
        bool didOperationWork = convo.Update(response);
        if (!didOperationWork) {
            std::cerr << "\nERROR: Failed to update response data! \n\n";
        }
        // Printing the chatbot's reply
        std::cout << "Translation: \n" << convo.GetLastResponse() << "\n \n";
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << std::endl;
    }

}

// A function to check for valid menu input, and iterate until valid input is recieved
int getMenuChoice() {
    // Creating a variable to store the user's menu choice
    int choice;
    // Looping infinitely to continuously collect input until input is valid
    while (true) {
        // Displaying the menu for the user
        std::cout << "Would you like to: \n"
                  << "1. Use the casual Brainrot Translator \n"
                  << "2. Use the Professional Brainrot Translator \n"
                  << "3. Use the Brainrot Professor \n"
                  << "4. End the conversation \n"
                  << "Please enter your choice: ";
        // Storing the user's inputted choice
        std::cin >> choice;
        // Checking if the choice was invalid
        if (std::cin.fail() || choice < 1 || choice > 4) {
            // If invalid input, clearing the error and stream, and displaying error + asking again
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "\nError: Please enter 1, 2, 3, or 4.\n\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove any extra input
            return choice;
        }
    }
}
