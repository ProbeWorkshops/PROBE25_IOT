#include <Firebase_ESP_Client.h>
#include <ESP8266WiFi.h>

// Insert your network credentials
#define WIFI_SSID "Harsh200"
#define WIFI_PASSWORD "H2a0r0s5h"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBuvqStOzPopKS9zkN2AM4PLrAL6LPzQ5Y"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://companion-5bd5f-default-rtdb.asia-southeast1.firebasedatabase.app/" 

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

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready()) {
    Serial.println(msg);
    //while (Serial.available()==0)
    //{
    //}
    arrayNumber=3;
    
    if (Firebase.RTDB.getArray(&fbdo, "/arrays/array"+String(arrayNumber))) {
      if (fbdo.dataType() == "array") {
        FirebaseJsonArray jsonArray = fbdo.jsonArray();
        int arrayLength = jsonArray.size();
        for(int i=0; i<arrayLength; i++){// Get the element at index i
            jsonArray.get(jsonData, "/arrays/array"+String(arrayNumber));  // Get the data at index i and store it in jsonData

            // Convert the data to integer and store it in the array
            arrayValue[i] = jsonData.to<int>();
        }

        // Print the values
        Serial.println("Array retrieved successfully:");
        for (int i = 0; i < arrayLength; i++) {
            Serial.println(arrayValue[i]);
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }
}