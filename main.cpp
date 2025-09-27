#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "liboai.h"
using namespace liboai;

int main() {
    OpenAI oai;
    // Set API key from environment variable
    if (!oai.auth.SetKeyEnv("OPENAI_API_KEY")) {
        std::cerr << "API key not set!" << std::endl;
        return 1;
    }

    // Loading in a CSV database of brainrot terms for reference
    std::unordered_map<std::string, std::string> slang_db;
    std::ifstream file("Brainrot-terms-and-translations-database.csv");
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string phrase, translation;
        std::getline(ss, phrase, ',');
        std::getline(ss, translation, ',');
        slang_db[phrase] = translation;
    }

    // Build a prompt with some database entries for context
    std::string context = "You are a helpful bot that translates Gen Z slang, aka 'Brainrot' to conversational English. Here are some Gen Z slang terms and their meanings:\n";
    int count = 0;
    for (const auto& [term, meaning] : slang_db) {
        if (count++ > 100) break; 
        context += term + ": " + meaning + "\n";
    }
    // context += "\nTranslate the following: " + user_input;

    // Set up the conversation with a system prompt
    Conversation convo;
    convo.SetSystemData(context);

    // Taking user input
    std::string user_input;
    std::cout << "\nWelcome to the Brainrot Translator! \nPlease enter a message with brainrot, and I'll translate it: \n";
    std::getline(std::cin, user_input);
    std::cout << std::endl;
    convo.AddUserData(user_input);

    try {
        // Call the chat completion endpoint (defaults to GPT 3.5 Turbo)
        Response response = oai.ChatCompletion->create("gpt-3.5-turbo", convo);
        // Update the conversation with the user's response
        convo.Update(response);
        // Print the chatbot's reply
        std::cout << "Translation: " << convo.GetLastResponse() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
