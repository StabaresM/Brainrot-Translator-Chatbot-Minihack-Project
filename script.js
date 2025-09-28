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
// Create the overlay div
    const bgDiv = document.createElement('div');
    bgDiv.style.position = 'fixed';
    bgDiv.style.top = 0;
    bgDiv.style.left = 0;
    bgDiv.style.width = '100vw';
    bgDiv.style.height = '100vh';
    bgDiv.style.backgroundImage = "url('tungtung.jpg')"; // Change to your image path
    bgDiv.style.backgroundSize = 'cover';
    bgDiv.style.backgroundPosition = 'center';
    bgDiv.style.opacity = '0.3'; // Adjust opacity as needed
    bgDiv.style.zIndex = '-1';
    bgDiv.style.pointerEvents = 'none'; // So it doesn't block clicks
    document.body.prepend(bgDiv);
    const outputDiv = document.getElementById('output');
// Set background color to black with 30% opacity
outputDiv.style.backgroundColor = 'rgba(255, 255, 255, 1)';
// Optionally, adjust text color for readability
outputDiv.style.color = 'black';
document.getElementById('githubBtn').addEventListener('click', () => {
  window.open('https://github.com/StabaresM/Brainrot-Translator-Chatbot-Minihack-Project', '_blank');
});
const githubBtn = document.getElementById('githubBtn');
Object.assign(githubBtn.style, {
  position: 'fixed',
  top: '10px',
  right: '10px',
  backgroundColor: '#24292e',
  color: '#ffffff',
  border: 'none',
  padding: '10px 15px',
  cursor: 'pointer',
  borderRadius: '5px',
  fontWeight: 'bold',
  fontFamily: 'Arial, sans-serif',
  transition: 'background-color 0.3s ease',
});

// Optional: Add hover effect with JS
githubBtn.addEventListener('mouseenter', () => {
  githubBtn.style.backgroundColor = '#444c56';
});
githubBtn.addEventListener('mouseleave', () => {
  githubBtn.style.backgroundColor = '#24292e';
});


