#include <Preferences.h>

Preferences prefs;

const char WIFI_NAMESPACE[] = "wifi";
const char SSID_KEY[] = "ssid";
const char PASSWORD_KEY[] = "password";

void setup() {
  // Start Serial
  Serial.begin(921600);
  delay(1000);

  prefs.begin(WIFI_NAMESPACE);

  // Update the next two lines to include the SSID and password you
  // want to save to flash memory, then run this utility on the microcontroller.
  // It will save the wifi credentials so that they can be retrieved by the
  // pool light controller each time it starts up.
  prefs.putString(SSID_KEY, "");
  prefs.putString(PASSWORD_KEY, "");
  
  Serial.println("The following values have been stored");
  Serial.print("SSID: ");
  Serial.println(prefs.getString(SSID_KEY));
  Serial.print("Password: ");
  Serial.println(prefs.getString(PASSWORD_KEY));

  prefs.end();
}

void loop() {
  // put your main code here, to run repeatedly:

}
