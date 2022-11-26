#include <Preferences.h>

Preferences prefs;

const char WIFI_NAMESPACE[] = "wifi";
const char SSID_KEY[] = "ssid";
const char PASSWORD_KEY[] = "password";

void setup() {
  // Start Serial
  Serial.begin(921600);

  prefs.begin(WIFI_NAMESPACE);

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
