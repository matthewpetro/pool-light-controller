// Import required libraries
#include <WiFi.h>
#include <aREST.h>
#include <Preferences.h>

// Create a Preferences instance
Preferences prefs;

// Create aREST instance
aREST rest = aREST();

// Create an instance of the server
WiFiServer server(8080);

// Declare functions to be exposed
int setPower(String command);
int setScene(String command);

// Declare variables to be exposed
String power;
String scene;

// Relay control pin
const int RELAY_PIN = 13;

const int RELAY_CLOSED = HIGH;
const int RELAY_OPEN = LOW;

const String POWER_STATE_ON = "on";
const String POWER_STATE_OFF = "off";

const int FLIP_WAIT_TIME = 250;
const int FLIP_INTERVAL_TIME = 400;

const char WIFI_NAMESPACE[] = "wifi";
const char SSID_KEY[] = "ssid";
const char PASSWORD_KEY[] = "password";

const int DEFAULT_WIFI_CONNECTION_CHECK_DELAY = 15000;

String wifiSsid;
String wifiPassword;

void setup()
{
  // Start Serial
  Serial.begin(921600);
  delay(1000);

  pinMode(RELAY_PIN, OUTPUT);

  // Init variables and expose them to REST API
  power = POWER_STATE_OFF;
  scene = "unknown";
  rest.variable("power",&power);
  rest.variable("scene",&scene);

  // Function to be exposed
  rest.function("power",setPower);
  rest.function("scene",setScene);

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("1");
  rest.set_name("PoolLightController");

  readWifiCredentials();
  wifiConnect(5000);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi not connected, attempting to reconnect");
    wifiConnect(30000);
  }
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("Got client, waiting for it to become available");
  while(!client.available()){
    delay(1);
  }
  IPAddress clientIP = client.remoteIP();
  int clientPort = client.remotePort();
  Serial.println("Handling client request from " + clientIP.toString() + ":" + clientPort);
  rest.handle(client);
}

void readWifiCredentials() {
  prefs.begin(WIFI_NAMESPACE, true);

  wifiSsid = prefs.getString(SSID_KEY);
  wifiPassword = prefs.getString(PASSWORD_KEY);
  
  prefs.end();
}

void wifiConnect(int connectionCheckDelay) {
  // Default connection check timeout
  int connectionCheckTimeout = DEFAULT_WIFI_CONNECTION_CHECK_DELAY;
  if (connectionCheckDelay > 0 ){
    connectionCheckTimeout = connectionCheckDelay;
  }
  char ssid[wifiSsid.length()+1];
  char password[wifiPassword.length()+1];
  wifiSsid.toCharArray(ssid, wifiSsid.length()+1);
  wifiPassword.toCharArray(password, wifiPassword.length()+1);

  // Connect to WiFi
  Serial.println("Connecting to wifi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(connectionCheckTimeout);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

int setPower(String command) {
  Serial.print("Executing setPower with command string: ");
  Serial.println(command);

  if (command.equalsIgnoreCase(POWER_STATE_ON)) {
    Serial.println("Turning light on");
    digitalWrite(RELAY_PIN, RELAY_CLOSED);
    power = POWER_STATE_ON;
    return 1;
  } else {
    Serial.println("Turning light off");
    digitalWrite(RELAY_PIN, RELAY_OPEN);
    power = POWER_STATE_OFF;
    return 0;
  }
}

int setScene(String command) {
  Serial.print("Executing setScene with command string: ");
  Serial.println(command);

  if (power.equalsIgnoreCase(POWER_STATE_OFF)) {
    setPower(POWER_STATE_ON);
    delay(5000);
  }

  int numFlips = getNumFlips(command);

  if (numFlips > 0) {
    for (int i=0; i<numFlips; i++) {
      flipPower();
      delay(FLIP_INTERVAL_TIME);
    }
    scene = command;
    return numFlips;
  }

  return 0;
}

int getNumFlips(String scene) {
  if (scene.equalsIgnoreCase("sam")) {
    return 1;
  } else if (scene.equalsIgnoreCase("party")) {
    return 2;
  } else if (scene.equalsIgnoreCase("romance")) {
    return 3;
  } else if (scene.equalsIgnoreCase("caribbean")) {
    return 4;
  } else if (scene.equalsIgnoreCase("american")) {
    return 5;
  } else if (scene.equalsIgnoreCase("california")) {
    return 6;
  } else if (scene.equalsIgnoreCase("royal")) {
    return 7;
  } else if (scene.equalsIgnoreCase("blue")) {
    return 8;
  } else if (scene.equalsIgnoreCase("green")) {
    return 9;
  } else if (scene.equalsIgnoreCase("red")) {
    return 10;
  } else if (scene.equalsIgnoreCase("white")) {
    return 11;
  } else if (scene.equalsIgnoreCase("magenta")) {
    return 12;
  } else {
    return 0;
  }
}

void flipPower() {
  if (power.equalsIgnoreCase(POWER_STATE_ON)) {
    digitalWrite(RELAY_PIN, RELAY_OPEN);
    delay(FLIP_WAIT_TIME);
    digitalWrite(RELAY_PIN, RELAY_CLOSED);
  }
}
