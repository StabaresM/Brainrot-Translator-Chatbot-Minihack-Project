const express = require('express');
const cors = require('cors');
const OpenAI = require('openai');
const fs = require('fs');
const path = require('path');

const openai = new OpenAI();
const app = express();
app.use(cors());
app.use(express.json());
app.use(express.static('.'));

// Load and build database string once
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
const slang_db = loadSlangDatabase('Brainrot-terms-and-translations-database.csv');
const database = buildDatabaseString(slang_db);

// Helper to get system prompt
function getSystemPrompt(mode, database) {
  if (mode === 'casual') {
    return database + "You are a helpful bot that translates Gen Z slang, aka 'Brainrot,' to casual, conversational terms.";
  } else if (mode === 'professional') {
    return database + "You are a helpful bot that translates Gen Z slang, aka 'Brainrot', into professional language (for older generations in a working environment).";
  } else if (mode === 'professor') {
    return database + "You are a helpful bot that explains Gen Z slang, aka 'Brainrot', and gives an explanation and brief historical background in language that the older generation can understand.";
  } else {
    return database;
  }
}

app.post('/api/translate', async (req, res) => {
  const { message, mode } = req.body;
  const systemPrompt = getSystemPrompt(mode, database);
  try {
    const response = await openai.chat.completions.create({
      model: 'gpt-3.5-turbo',
      messages: [
        { role: 'system', content: systemPrompt },
        { role: 'user', content: message }
      ]
    });
    res.json({ translation: response.choices[0].message.content });
  } catch (err) {
    res.json({ error: 'Error contacting OpenAI: ' + err.message });
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log('Server running on http://localhost:' + PORT);
});
