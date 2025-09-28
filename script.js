const sendBtn = document.getElementById('sendBtn');
const userInput = document.getElementById('userInput');
const output = document.getElementById('output');
const mode = document.getElementById('mode');

sendBtn.onclick = async () => {
  output.textContent = 'Translating...';
  const res = await fetch('/api/translate', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
      message: userInput.value,
      mode: mode.value
    })
  });
  const data = await res.json();
  output.textContent = data.translation || data.error || 'No response.';
};
