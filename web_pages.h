#include <sys/pgmspace.h>
#ifndef WEB_PAGES_H
#define WEB_PAGES_H

#include <pgmspace.h>

const char html_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>%TITLE%</title>
    <style>
      * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }

      body {
        font-family: 'Arial', sans-serif;
        background-color: #f7f7f7;
        color: #333;
        overflow-x: hidden;
        min-height: 100vh;
        display: flex;
        flex-direction: column;
      }

      header {
        background-color: #1a1a1a;
        color: #f1f1f1;
        padding: 15px;
        text-align: center;
        font-size: 24px;
        font-weight: 600;
        position: sticky;
        top: 0;
        z-index: 1000;
        border: none;
      }

      nav {
        background-color: #1a1a1a;
        display: flex;
        justify-content: center;
        padding: 0;
        margin: 0;
        border: none;
      }

      nav a {
        color: #f1f1f1;
        text-decoration: none;
        padding: 10px 20px;
        font-size: 18px;
        margin: 0;
        transition: background-color 0.3s ease;
      }

      nav a:hover {
        background-color: #555;
      }

      footer {
        background-color: #1a1a1a;
        color: #f1f1f1;
        padding: 10px;
        text-align: center;
        font-size: 14px;
        border-top: 2px solid #444;
        margin-top: auto;
      }

      .container {
        width: 90%;
        max-width: 600px;
        margin: 20px auto 20px auto;
        padding: 30px;
        background-color: white;
        border-radius: 8px;
        box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
      }

      .input-group {
        margin-bottom: 20px;
      }

      label {
        display: block;
        font-size: 14px;
        color: #333;
        margin-bottom: 5px;
      }

      input[type="text"],
      input[type="password"] {
        width: 100%;
        padding: 12px;
        margin-top: 5px;
        border: 2px solid #ddd;
        border-radius: 4px;
        font-size: 14px;
        transition: border-color 0.3s ease, box-shadow 0.3s ease;
      }

      input[type="text"]:focus,
      input[type="password"]:focus {
        border-color: #333;
        box-shadow: 0 0 5px rgba(0, 0, 0, 0.1);
        outline: none;
      }

      .show-password-label {
        font-size: 14px;
        margin-top: 5px;
        color: #333;
        cursor: pointer;
      }

      #show-password {
        margin-right: 5px;
      }

      button,
      input[type='submit'] {
        background-color: #333;
        color: white;
        border: none;
        padding: 10px 18px;
        font-size: 16px;
        border-radius: 4px;
        cursor: pointer;
        width: auto;
        transition: all 0.3s ease;
      }

      button:hover,
      input[type='submit']:hover {
        background-color: #555;
      }

      button:focus,
      input[type='submit']:focus {
        outline: none;
        box-shadow: 0 0 5px rgba(0, 0, 0, 0.2);
      }

      button:active,
      input[type='submit']:active {
        background-color: #444;
        transform: translateY(2px);
      }

      @media (max-width: 600px) {
        header {
          font-size: 24px;
          padding: 15px;
        }

        .container {
          width: 95%;
          padding: 20px;
        }

        nav a {
          font-size: 16px;
          padding: 10px 15px;
        }

        input[type="text"],
        input[type="password"] {
          padding: 10px;
        }

        button {
          font-size: 14px;
          padding: 10px 16px;
        }
      }

      @media (min-width: 601px) {
        header {
          font-size: 28px;
        }

        .container {
          width: 80%;
        }
      }
    </style>
  </head>
  <body>
    <header>
      <a href="/" style="text-decoration: none; color: inherit;">
        <h1>%HEADER%</h1>
      </a>
    </header>

    <nav>
      <a href="/">Home</a>
      <a href="/monitoring">Monitoring</a>
      <a href="/config">Config</a>
      <a href="/reset">Reset</a>
    </nav>

    <div class="container">
      <div class="content"> %CONTENT% </div>
    </div>

    <footer>
      <p class="footer-text">&copy; 2024 %HEADER% Project by <a href="https://zacky.id" target="_blank" style="text-decoration: none; color: inherit;">Zacky Achmad</a></p>
    </footer>
  </body>
</html>
)rawliteral";

const char index_html[] PROGMEM = R"rawliteral(
<p style="margin-bottom: 20px">
  This device collects and displays weather data, allowing you to monitor
  environmental conditions such as temperature and humidity. It is designed as
  an IoT (Internet of Things) device, enabling seamless integration with devices
  through MQTT (Message Queuing Telemetry Transport) for real-time communication
  and data exchange.
</p>

<p>Below are key details about your device's current status:</p>

<table border="1" cellpadding="8" cellspacing="0" style="width: 100%; border-collapse: collapse; margin-top: 10px; margin-bottom: 20px;">
  <tr>
    <th style="text-align: left; padding: 10px">Information</th>
    <th style="text-align: left; padding: 10px">Details</th>
  </tr>
  <tr>
    <td style="padding: 10px"><strong>Time Server</strong></td>
    <td style="padding: 10px"><span id="timeServer">N/A</span></td>
  </tr>
  <tr>
    <td style="padding: 10px"><strong>Free Memory</strong></td>
    <td style="padding: 10px"><span id="freeMemory">N/A</span> Kbytes</td>
  </tr>
  <tr>
    <td style="padding: 10px"><strong>Wi-Fi SSID</strong></td>
    <td style="padding: 10px"><span id="wifiSSID">N/A</span></td>
  </tr>
  <tr>
    <td style="padding: 10px"><strong>Wi-Fi Signal Strength</strong></td>
    <td style="padding: 10px"><span id="wifiSignalStrength">N/A</span> dBm</td>
  </tr>
  <tr>
    <td style="padding: 10px"><strong>Device IP</strong></td>
    <td style="padding: 10px"><span id="deviceIP">N/A</span></td>
  </tr>
</table>

<script>
  function fetchDeviceInfo() {
    fetch('/device-info')
      .then((response) => response.json())
      .then((data) => {
        document.getElementById('timeServer').innerText = data.timeServer;
        document.getElementById('freeMemory').innerText = data.freeMemory;
        document.getElementById('wifiSSID').innerText = data.wifiSSID;
        document.getElementById('wifiSignalStrength').innerText =
          data.wifiSignalStrength;
        document.getElementById('deviceIP').innerText = data.deviceIP;
      });
  }

  window.onload = function () {
    fetchDeviceInfo();
    setInterval(fetchDeviceInfo, 60000);
  };
</script>
)rawliteral";

const char monitoring_html[] PROGMEM = R"rawliteral(
<h2 style="text-align: center;">Monitoring</h2>
<div style="display: flex; justify-content: center; gap: 30px; flex-wrap: wrap;">
  <div style="width: 45%; max-width: 500px;">
    <canvas id="tempChart" width="500" height="300" style="max-width: 100%;"></canvas>
    <p style="text-align: center; margin-top: 5px; font-size: 1em;">
      Temperature
    </p>
  </div>
  <div style="width: 45%; max-width: 500px;">
    <canvas id="humChart" width="500" height="300" style="max-width: 100%;"></canvas>
    <p style="text-align: center; margin-top: 5px; font-size: 1em;">
      Humidity
    </p>
  </div>
</div>

<div style="text-align: left; margin-top: 35px; font-size: 1em;">
  <h3 style="margin-bottom: 5px">Additional Information</h3>
  <p>Last Update: <span id="lastFetch">N/A</span></p>
  <p>Previous Temperature: <span id="prevTemp">N/A</span> °C</p>
  <p>Previous Humidity: <span id="prevHum">N/A</span> %</p>
</div>

<script>
  let prevTemp = null;
  let prevHum = null;
  let isFetching = false;

  function drawBarChart(canvasId, value, maxVal, color, unit) {
    const ctx = document.getElementById(canvasId).getContext('2d');
    const width = ctx.canvas.width;
    const height = ctx.canvas.height;
    const margin = 30;

    ctx.clearRect(0, 0, width, height);

    const barWidth = (width - 2 * margin) * 0.6;
    const barHeight = (value / maxVal) * (height - 2 * margin);
    const x = (width - barWidth) / 2;
    const y = height - margin - barHeight;

    // Gambar bar
    ctx.fillStyle = color;
    ctx.fillRect(x, y, barWidth, barHeight);

    // Gambar nilai di bar
    ctx.fillStyle = "#000";
    ctx.font = "bold 22px Arial";
    ctx.textAlign = "center";
    ctx.fillText(value.toFixed(1) + " " + unit, x + barWidth / 2, y - 15);

    // Gambar sumbu dasar
    ctx.strokeStyle = "#000";
    ctx.beginPath();
    ctx.moveTo(margin, height - margin);
    ctx.lineTo(width - margin, height - margin);
    ctx.stroke();
  }

  function fetchData() {
    const prevData = JSON.parse(localStorage.getItem('sensorData'));

    if (prevData) {
        if (prevData.temperature !== "Error" && prevData.humidity !== "Error") {
            document.getElementById('prevTemp').innerText = prevData.temperature.toFixed(1);
            document.getElementById('prevHum').innerText = prevData.humidity.toFixed(1);
        }
    }

    fetch('/sensor-data')
          .then(response => response.json())
          .then(data => {
              document.getElementById('lastFetch').innerText = data.timeServer;

              if (data.temperature !== "Error" && data.humidity !== "Error") {
                  drawBarChart('tempChart', data.temperature, 50, '#FF5733', '°C');
                  drawBarChart('humChart', data.humidity, 100, '#3498DB', '%');

                  localStorage.setItem('sensorData', JSON.stringify(data));

                  document.getElementById('prevTemp').innerText = data.temperature.toFixed(1);
                  document.getElementById('prevHum').innerText = data.humidity.toFixed(1);
              }
          });
  }

  window.onload = function () {
    fetchData();
    setInterval(fetchData, 10000);
  };
</script>
)rawliteral";

const char config_html[] PROGMEM = R"rawliteral(
<h2 style="margin-bottom: 10px">MQTT Configuration</h2>

<form action="/config" method="post">
  <div class="input-group">
    <label for="mqtt_broker">Broker Address:</label>
    <input
      type="text"
      id="mqtt_broker"
      name="mqtt_broker"
      value="%MQTT_BROKER%"
      required
    />
  </div>

  <div class="input-group">
    <label for="mqtt_port">Port:</label>
    <input
      type="text"
      id="mqtt_port"
      name="mqtt_port"
      value="%MQTT_PORT%"
      required
    />
  </div>

  <div class="input-group">
    <label for="mqtt_topic">Topic:</label>
    <input
      type="text"
      id="mqtt_topic"
      name="mqtt_topic"
      value="%MQTT_TOPIC%"
      required
    />
  </div>

  <div class="input-group">
    <label for="mqtt_username">Username:</label>
    <input
      type="text"
      id="mqtt_username"
      name="mqtt_username"
      value="%MQTT_USERNAME%"
    />
  </div>

  <div class="input-group">
  <label for="mqtt_password">Password:</label>
  <input
    type="password"
    id="mqtt_password"
    name="mqtt_password"
    value="%MQTT_PASSWORD%"
  />
  <label for="show-password" class="show-password-label">
      <input type="checkbox" id="show-password" />
      Show Password
    </label>
  </div>

  <button type="submit" style="margin-top:10 px">Save</button>
</form>

<script>
  document.getElementById("show-password").addEventListener("change", function() {
    let passwordInput = document.getElementById("mqtt_password");
    if (this.checked) {
      passwordInput.type = "text";
    } else {
      passwordInput.type = "password";
    }
  });
</script>
)rawliteral";

const char config_post_html[] PROGMEM = R"rawliteral(
<h2 style="margin-bottom: 10px">MQTT Configuration</h2>
<p>Your configuration has been saved successfully. The device will restart shortly to apply changes.</p>
<script>
  setTimeout(function() {
    window.location.href = '/config';
  }, 10000);
</script>
)rawliteral";

const char reset_html[] PROGMEM = R"rawliteral(
<h2 style="margin-bottom: 10px;">Reset Device</h2>
<p>Are you sure you want to reset all configuration on your %HEADER% device?</p>
<form action="/reset" method="post" style="margin-top:10 px">
  <button type="submit" style="margin-top: 20px;">Yes, Reset Configuration</button>
</form>
)rawliteral";

const char reset_post_html[] PROGMEM = R"rawliteral(
<h2 style="margin-bottom: 10px">Reset Device</h2>
<p style="margin-bottom: 20px">Your device has been reset and will now restart. It will attempt to connect to the default Wi-Fi network: <strong>%HEADER%</strong>.</p>
<p style="margin-bottom: 20px">Use the password: <strong>%DEFAULT_PASSWORD%</strong> to connect.</p>
<p>Once connected, access the configuration page to reconfigure your device.</p>
)rawliteral";

#endif
