#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <HTU21D.h>

const char* ssid = ".";
const char* password = ".";

const char* serverName = "http://192.168.1.154/home/api.php";

// Create an instance of the HTU21D sensor
HTU21D htu;

void setup() {
  // Initialize the serial connection
  Serial.begin(115200);
  delay(10);

  // Connect to the WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  htu.begin();
}

void loop() {
  if(htu.measure()){
    float temperature = htu.getTemperature();
    float humidity = htu.getHumidity();
    Serial.print("temperature is: ");
    Serial.println(temperature);
    Serial.print("humidity is: ");
    Serial.println(humidity);
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      http.begin(client, serverName);
  
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "temperature=" + String(temperature) + "&humidity=" + String(humidity);
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
  else
  {
    Serial.println("HTU21D sensor is not measuring corectly");
  }
  delay(30000);
}
