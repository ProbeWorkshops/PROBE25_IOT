#include <Firebase_ESP_Client.h>
#include <ESP8266WiFi.h>

// Insert your network credentials
#define WIFI_SSID "Harsh200"
#define WIFI_PASSWORD "H2a0r0s5h"

// Insert Firebase project API Key
#define API_KEY "AIzaSyA3oxW3Ls_1lnALt0yys_SyIwc3qnkPxQ4"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://procompanion-d26f9-default-rtdb.asia-southeast1.firebasedatabase.app/" 

FirebaseConfig config;
FirebaseAuth auth;
//Define Firebase Data object
FirebaseData fbdo;

String msg = "Enter the array no.: ";
bool signupOK = false;
int arrayNumber;
int arrayValue[50];
int arrayLength = 0;
FirebaseJsonData jsonData;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Sign in anonymously to Firebase
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase Sign-Up Succeeded");
    signupOK = true;
  } else {
    Serial.printf("Firebase Sign-Up Failed: %s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK) {
    arrayNumber = 2; // Change to 3 if accessing array3

    // Retrieve the array from Firebase
    if (Firebase.RTDB.getArray(&fbdo, "/arrays/array" + String(arrayNumber))) {
      if (fbdo.dataType() == "array") {
        FirebaseJsonArray jsonArray = fbdo.jsonArray();
        int arrayLength = jsonArray.size();

        int arrayValue[50]; // Ensure sufficient size
        Serial.println("Array retrieved successfully:");

        // Loop through the array and fetch elements
        for (int i = 155000; i < arrayLength; i++) {
          if (jsonArray.get(jsonData, i)) {
            arrayValue[i] = jsonData.to<int>(); // Convert to integer
            Serial.println(arrayValue[i]);     // Print each element
          } else {
            Serial.println("Error retrieving element at index " + String(i));
          }
        }
      } else {
        Serial.println("Data type mismatch: Expected an array.");
      }
    } else {
      Serial.print("Error retrieving array: ");
      Serial.println(fbdo.errorReason());
    }

    delay(2000); // Adjust delay as needed
  }
}