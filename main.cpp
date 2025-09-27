#include <iostream>
#include "liboai.h"
using namespace liboai;

int main() {
    OpenAI oai;
    // Set API key from environment variable
    if (!oai.auth.SetKeyEnv("OPENAI_API_KEY")) {
        std::cerr << "API key not set!" << std::endl;
        return 1;
    }

    // Set up the conversation with a system prompt
    Conversation convo;
    convo.SetSystemData("You are a helpful bot that translates Gen Z slang to standard English.");

    // Example user input
    std::string user_input;
    std::cout << "Enter Gen Z slang: ";
    std::getline(std::cin, user_input);
    convo.AddUserData(user_input);

    try {
        // Call the chat completion endpoint
        Response response = oai.ChatCompletion->create("gpt-3.5-turbo", convo);
        // Update conversation with response
        convo.Update(response);
        // Print the chatbot's reply
        std::cout << "Translation: " << convo.GetLastResponse() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
