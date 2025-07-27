// web_version/script.js

const API_BASE    = ''; // root of the web server
const POLL_INTERVAL = 2000; // ms

// DOM elements
const soilEl   = document.getElementById('soil');
const tempEl   = document.getElementById('temp');
const humEl    = document.getElementById('hum');
const lightEl  = document.getElementById('light');
const statusEl = document.getElementById('status');

// Helper to set text and optional alert class
function setMetric(el, value, unit = '%') {
  el.textContent = `${value}${unit}`;
}

// Overall status based on any alert flags
function updateStatus(flags) {
  if (flags.anyAlert) {
    statusEl.textContent = '⚠️ ALERT';
    statusEl.classList.remove('ok');
    statusEl.classList.add('alert');
  } else {
    statusEl.textContent = '✅ All Good';
    statusEl.classList.remove('alert');
    statusEl.classList.add('ok');
  }
}

// Fetch latest readings and update UI
async function fetchAndRender() {
  try {
    const res = await fetch(`${API_BASE}/status`);
    if (!res.ok) throw new Error(`HTTP ${res.status}`);
    const json = await res.json();
    // Expect { soil: 0–100, temp: °C, hum: 0–100, light: 0–100, alerts: { soil, temp, hum, light } }
    const { soil, temp, hum, light, alerts } = json;
    setMetric(soilEl, soil, '%');
    setMetric(tempEl, temp.toFixed(1), '°C');
    setMetric(humEl, hum, '%');
    setMetric(lightEl, light, '%');
    updateStatus({ anyAlert: alerts.soil || alerts.temp || alerts.hum || alerts.light });
  } catch (err) {
    console.error('Fetch error:', err);
    statusEl.textContent = '❌ Error fetching data';
    statusEl.classList.remove('ok');
    statusEl.classList.add('alert');
  }
}

// Initial load
fetchAndRender();

// Poll periodically
setInterval(fetchAndRender, POLL_INTERVAL);
