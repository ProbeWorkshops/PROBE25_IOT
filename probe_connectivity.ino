#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

const char* ssid = "POCO X4 Pro 5G"; // Replace with your Wi-Fi SSID
const char* password = "qwerty1234";   // Replace with your Wi-Fi Password
const char* serverIP = "192.168.42.158"; // Replace with your laptop's IP address (Flask server)
const int serverPort = 5000;  // Flask server port

WiFiClient client;
ESP8266WebServer server(80);  // Start an HTTP server on port 80

// Function to handle incoming requests to the ESP8266 server
void handleEmotionRequest() {
  String emotion = server.arg("emotion");  // e.g., "happy", "sad", or "angry"
  
  if (emotion == "happy" || emotion == "sad" || emotion == "angry") {
    // Request the file from the Flask server based on the emotion
    requestFile(emotion);
    server.send(200, "text/plain", "Requesting file for emotion: " + emotion);
  } else {
    server.send(400, "text/plain", "Invalid emotion. Please use 'happy', 'sad', or 'angry'.");
  }
}

// Function to request file from Flask server based on emotion
void requestFile(String emotion) {
  if (client.connect(serverIP, serverPort)) {  // Connect to Flask server on port 5000
    String httpRequest = "GET /getfile?emotion=" + emotion + " HTTP/1.1\r\n" +
                         "Host: " + String(serverIP) + "\r\n" +
                         "Connection: close\r\n\r\n";
    client.print(httpRequest);

    // Read the response from the Flask server
    bool headersEnded = false;
    while (client.connected() || client.available()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        if (!headersEnded) {
          if (line == "\r") {  // End of HTTP headers
            headersEnded = true;
            Serial.println("\n--- File Content ---");
          }
        } else {
          Serial.println(line);  // Print file content from Flask
        }
      }
    }
    client.stop();
    Serial.println("--- End of File Content ---");
  } else {
    Serial.println("Failed to connect to Flask server.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("ESP IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up the ESP8266 WebServer routes
  server.on("/", HTTP_GET, handleEmotionRequest);  // Route to handle emotion requests

  // Start the server
  server.begin();
}

void loop() {
  // Handle incoming HTTP requests on the server
  server.handleClient();
}
