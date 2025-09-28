##Welcome to our team's OSC MiniHack project!

**Project description:**
This project is a translator for Gen Z “brainrot” slang in the style of a menu-based AI chatbot. It offers three modes: casual conversation, professional workplace communication, and an educational mode that explains slang origins. The tool improves intergenerational and professional communication by making “brainrotted” messages clearer, with measurable impact based on the percentage of slang words translated.
Modes breakdown: 
  * Brainrot Translator: Takes input of brainrot terms/words/phrases, and translates it into casual language (for older people who might not be in touch with Gen Z terminology).
  * Professional translator: Brainrot translation into formal/professional language for better communication in professional settings.
  * Brainrot Teacher: Describes the meaning of brainrot words, including time period, historical context, and sample usage, for educational purposes.

**Usage/implementation:**
  * The code base can be set up with the following steps:
  * Open the lasest version in GitHub Codespaces (or another IDE)
  * Get submodule (only for the first time):
   * Enter into the terminal:
   * git submodule update --init --recursive
  * Get your OpenAI API key
   * Go to the following website: https://platform.openai.com/account/api-keys
   * Log in, create a new key, and copy it. (to use it, you may have to pay the minimum $5.)
   * Paste it into:
   * export OPENAI_API_KEY=YOUR_KEY_HERE
   * Where YOUR_KEY_HERE is the pasted key you got from OpenAI; paste this line into the terminal.
  * Build and run the program
   * Enter the following lines into the terminal (the first two just on the first run; takes about a minute to build on the first run):
   * cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
   * cmake --build build
   * ./build/myapp
  * And, the program should start up. Interact with the chatbot via a menu-based text interface, and when finished, simply choose option 4 to finish the conversation.

**Measurable impact:**
  * To quantify our program’s usefulness, we developed a metric called **brainrot density**—the ratio of slang terms to total words in a message. The percent density equals the percent increase in comprehensibility after translation, since the output always contains 0% brainrot.
  * Example:
   * Original sentence: _Yass queen, that fit lowkey slaps harder than Ohio memes._
   * Translated: _Yes, girl, that outfit is subtly impressive, even more so than Ohio memes._
   * Original brainrot density: 0.70
   * Comprehensibility increase: 70%
Across test cases, our program improved comprehensibility by an **average of 52.4%**, showing that communication between generations can become more than 50% more effective. Spreadsheet of test cases: https://docs.google.com/spreadsheets/d/1cqGR4hRyEnGiHXrLELIkEkzWW8atNrGTTim61mfrakM/edit?usp=sharing

**Code sources:**
  * The program is powered by OpenAI’s **GPT-3.5-turbo** model, connected through the open-source **liboai** C++ library and the **vcpkg** dependency manager.
  * liboai link: https://github.com/D7EAD/liboai/
  * Custom database of brainrot terms: https://docs.google.com/spreadsheets/d/11FuqvSW5wStwxwTjPpFSK9AIkF33U7zM-zqy972GKgQ/edit?usp=sharing

**Program use cases:**
  * This program effectively increases communication between generations, such as for a Gen Z to talk to their parents or grandparents, measurably increasing their quality of life through ensuring effective communication.
  * In addition, allows for professional communication in the workplace with Professional Brainrot Translator mode, to allow for better job prospects and working relationships.
  * Not to mention, allows for older generations (Millenial, Gen X, Boomers) to become more in touch with the language of Gen Z today, to increase inter-generational communication and quality of life.
