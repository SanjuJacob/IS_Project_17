#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "Sanju's iPhone";
const char* password = "Sanjujacob03";

// Create an instance of the ESP8266WebServer on port 80
ESP8266WebServer server(80);

// Define the LED pin
const int ledPin = D1; // GPIO5

// Variable to keep track of the LED state
bool ledState = false;

// HTML content for the web page
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP8266 LED Control</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }
        button { padding: 20px; font-size: 20px; }
    </style>
</head>
<body>
    <h1>ESP8266 LED Control</h1>
    <p>LED is <span id="ledState">OFF</span></p>
    <button onclick="toggleLED()">Toggle LED</button>
    <script>
        function toggleLED() {
            fetch('/toggle')
                .then(response => response.text())
                .then(state => {
                    document.getElementById('ledState').textContent = state;
                });
        }
    </script>
</body>
</html>
)rawliteral";

void setup() {
    // Initialize serial communication
    Serial.begin(115200);
    delay(100); // Small delay to allow serial communication to set up
    Serial.println();

    // Initialize the LED pin
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    // Connect to Wi-Fi
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
        attempts++;
        if (attempts > 20) {  // Try for 20 seconds
            Serial.println("Failed to connect to WiFi");
            return;
        }
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Define the routes
    server.on("/", HTTP_GET, handleRoot);
    server.on("/toggle", HTTP_GET, handleToggle);

    // Start the server
    server.begin();
    Serial.println("HTTP server started.");
}

void loop() {
    // Handle client requests
    server.handleClient();
}

void handleRoot() {
    Serial.println("Serving root page");
    server.send(200, "text/html", htmlPage);
}

void handleToggle() {
    Serial.println("Toggle LED requested");
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    server.send(200, "text/plain", ledState ? "ON" : "OFF");
}
