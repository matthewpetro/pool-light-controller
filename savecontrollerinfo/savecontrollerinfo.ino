#include <Preferences.h>

Preferences prefs;

const char CONTROLLER_NAMESPACE[] = "controller";
const char CONTROLLER_ID_KEY[] = "id";
const char CONTROLLER_NAME_KEY[] = "name";

void setup() {
  // Start Serial
  Serial.begin(921600);

  prefs.begin(CONTROLLER_NAMESPACE);

  // Update the next two lines to include the controller ID and name you
  // want to save to flash memory, then run this utility on the microcontroller.
  // It will save the ID and name so that they can be retrieved by the
  // pool light controller each time it starts up.
  prefs.putString(CONTROLLER_ID_KEY, "2");
  prefs.putString(CONTROLLER_NAME_KEY, "OriginalPoolLightController");

  Serial.println("The following values have been stored");
  Serial.print("Controller ID: ");
  Serial.println(prefs.getString(CONTROLLER_ID_KEY));
  Serial.print("Controller name: ");
  Serial.println(prefs.getString(CONTROLLER_NAME_KEY));

  prefs.end();
}

void loop() {
  // put your main code here, to run repeatedly:

}
