const fs = require('fs');
const readline = require('readline');
const OpenAI = require('openai');
const openai = new OpenAI();

// You'd import OpenAI here if needed, e.g.:
// const { OpenAI } = require('openai');
function loadSlangDatabase(filename) {
  const slang_db = {};
  const data = fs.readFileSync(filename, 'utf8');
  const lines = data.split('\n');
  for (let line of lines) {
    const [phrase, translation] = line.split(',');
    if (phrase && translation) {
      slang_db[phrase.trim()] = translation.trim();
    }
  }
  return slang_db;
}
function buildDatabaseString(slang_db) {
  let database = 'Here is a database of Gen Z slang terms and their meanings:\n';
  let count = 0;
  for (const term in slang_db) {
    if (count++ > 120) break;
    database += `${term}: ${slang_db[term]}\n`;
  }
  return database;
}
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

function getMenuChoice() {
  return new Promise((resolve) => {
    rl.question(
      'Would you like to:\n' +
      '1. Use the casual Brainrot Translator\n' +
      '2. Use the Professional Brainrot Translator\n' +
      '3. Use the Brainrot Professor\n' +
      '4. End the conversation\n' +
      'Please enter your choice: ',
      (answer) => {
        const choice = parseInt(answer);
        if ([1,2,3,4].includes(choice)) {
          resolve(choice);
        } else {
          console.log('Error: Please enter 1, 2, 3, or 4.');
          resolve(getMenuChoice());
        }
      }
    );
  });
}
async function brainrotTranslator(database) {
  const message = await ask("\nPlease enter a message with brainrot, and I'll translate it into casual language:\n");
  const systemPrompt = database + "You are a helpful bot that translates Gen Z slang, aka 'Brainrot,' to casual, conversational terms.";
  try {
    const response = await openai.chat.completions.create({
      model: "gpt-3.5-turbo",
      messages: [
        { role: "system", content: systemPrompt },
        { role: "user", content: message }
      ]
    });
    console.log('Translation:', response.choices[0].message.content);
  } catch (error) {
    console.error('Error calling OpenAI:', error);
  }
}

async function professionalBrainrotTranslator(database) {
  const message = await ask("\nPlease enter a message with brainrot, and I'll translate it into professional language:\n");
  const systemPrompt = database + "You are a helpful bot that translates Gen Z slang, aka 'Brainrot', into professional language (for older generations in a working environment).";
  try {
    const response = await openai.chat.completions.create({
      model: "gpt-3.5-turbo",
      messages: [
        { role: "system", content: systemPrompt },
        { role: "user", content: message }
      ]
    });
    console.log('Translation:', response.choices[0].message.content);
  } catch (error) {
    console.error('Error calling OpenAI:', error);
  }
}

async function brainrotProfessor(database) {
  const message = await ask("\nPlease enter a message with brainrot, and I'll explain it:\n");
  const systemPrompt = database + "You are a helpful bot that explains Gen Z slang, aka 'Brainrot', and gives an explanation and brief historical background in language that the older generation can understand.";
  try {
    const response = await openai.chat.completions.create({
      model: "gpt-3.5-turbo",
      messages: [
        { role: "system", content: systemPrompt },
        { role: "user", content: message }
      ]
    });
    console.log('Explanation:', response.choices[0].message.content);
  } catch (error) {
    console.error('Error calling OpenAI:', error);
  }
}

async function main() {
  const slang_db = loadSlangDatabase('Brainrot-terms-and-translations-database.csv');
  const database = buildDatabaseString(slang_db);
  console.log("\nWelcome to the Brainrot Translator!\n");
  let botChoice;
  do {
    botChoice = parseInt(await ask(
      'Would you like to:\n' +
      '1. Use the casual Brainrot Translator\n' +
      '2. Use the Professional Brainrot Translator\n' +
      '3. Use the Brainrot Professor\n' +
      '4. End the conversation\n' +
      'Please enter your choice: '
    ));
    switch (botChoice) {
      case 1:
        await brainrotTranslator(database);
        break;
      case 2:
        await professionalBrainrotTranslator(database);
        break;
      case 3:
        await brainrotProfessor(database);
        break;
      case 4:
        console.log("\nThanks for using the Brainrot Translator, have a skibidi day!\n");
        rl.close();
        break;
      default:
        console.log('Error: Please enter 1, 2, 3, or 4.');
    }
  } while (botChoice !== 4);
}

main();

async function getTranslationFromOpenAI(systemPrompt, userMessage) {
  const response = await openai.chat.completions.create({
    model: 'gpt-3.5-turbo', // or 'gpt-4o' if you have access
    messages: [
      { role: 'system', content: systemPrompt },
      { role: 'user', content: userMessage }
    ]
  });
  return response.choices[0].message.content;
}

function ask(question) {
  return new Promise(resolve => rl.question(question, resolve));
}




main();
