/**
 * Test Scenario ID : MID-GLOBAL-C33-001-Example-AnalogToSMS
 * 
 * This sketch reads the analog pin and sends the raw value as a text messages
 * to a specified phone number using the Arduino_Cellular library.
 * 
 * Test Case IDs :
 * MID-GLOBAL-C33-001-Example-AnalogToSMS-01 -> Send analog pin A0 value once
 * MID-GLOBAL-C33-001-Example-AnalogToSMS-02 -> Send analog pin A0 value 3 times
 * MID-GLOBAL-C33-001-Example-AnalogToSMS-02 -> Send analog pin A0 value every 5 seconds for 30 seconds
 * 
 * NOTE: Enter the phone number you want to send the SMS to, starting with +(countrycode).
 * 
 * Instructions:
 *  1. Insert a SIM card (without PIN code) in the Arduino Mid Carrier.
 *  2. Connect the Serial (J17) to the adjacent PCIE Breakout Pins (J16): 
 *    Serial 1 (J17)            -> PCIE Breakout (J16)
 *    RX (Pin 1)                -> CK_N (Pin 1)
 *    TX (Pin 2)                -> CK_P (Pin 3)
 *    RTS (Pin 3)               -> RX_N (Pin 5)
 *    CTS (Pin 4)               -> RX_P (Pin 7)
 *    mPCIE_GPIO_RST (Pin 5)    -> mPCIE_RST (Pin 9)
 *  3. On J9, connect the following pins:
 *    3V3 PCIE (Pin 1)          -> 3V3 BUCK (Pin 3)
 *    OUT VCC (Pin 2)           -> 3V3 BUCK EN (Pin 4) 
 *  4. Insert the Arduino Pro 4G Module in the Arduino Mid Carrier.
 *  5. Screw one black post with a white nut from under the Mid Carrier. Using another black post, 
 *    screw the board to the post. Place two washers on top, and one underneath the Pro 4G Module.
 *    So that the board is fixed to the post snuggly and horizontally. 
 *  6. (EMEA and GNSS variants) Connect the cellular antenna (flat antenna in TPX00219)
 *    to the left microUFL connector marked MAIN.
 *  7. (PRO 4G GNSS only) Connect the GNSS antenna (square antenna in TPX00219)
 *    to the middle microUFL connector marked GNSS.
 *  8. Insert the Portenta Board into the marked location. The USB-c port of the Portenta board,
 *    should be next to the Ethernet port on the Mid Carrier.
 *  9. Insert a Terminal Block 2-pin > DC female adapter. Ensure that the negative (-) pin is connected to GND.
 * 10. Use a a 5V adapter that can output at least 2A and connect it to the DC female adapter.
 * 11. Connect the Portenta board to your computer using a USB-C cable.
 * 12. Upload sketch to the Portenta board. And open the Serial monitor
 * 13. Save Serial monitor output for future reference.
 * 
 * Initial author: Ali Jahangiri @aliphys
 */

#include "ArduinoCellular.h"

const char testScenarioID[] = "MID-GLOBAL-C33-001-Example-AnalogToSMS";

String phoneNumber = "+46XXXXXXXXX";
const int analogInPin = A0; // Pin values to read from
int sensorValue = 0 ;
String message = "";

ArduinoCellular cellular = ArduinoCellular();

void setup(){
    Serial.begin(115200);
    while (!Serial);

    Serial.println();
    Serial.println("---------");
    Serial.print("Test Scenario ID: ");
    Serial.println(testScenarioID);
    Serial.println("---------");
    Serial.println();

    cellular.setDebugStream(Serial);
    cellular.begin();

    delay(2000); // Give the modem some time to initialize

    Serial.println("Connecting to network...");
    if (cellular.connect()) {
        Serial.println("Connected!");
    } else {
        Serial.println("Failed to connect to network.");
    }

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-GLOBAL-C33-001-Example-AnalogToSMS-01");

    Serial.println("Send analog pin A0 value once...");
    sensorValue = analogRead(analogInPin);
    message = "Single Analog value: " + String(sensorValue);
    Serial.println(message);
    cellular.sendSMS(phoneNumber, message);

    delay(1000);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-GLOBAL-C33-001-Example-AnalogToSMS-02");

    Serial.println("Send analog pin A0 value three times...");
    for (int i = 1; i <= 3; i++) {
        sensorValue = analogRead(analogInPin);
        message = String(i) + "/3 Analog value: " + String(sensorValue);
        cellular.sendSMS(phoneNumber, message);
        Serial.println(message);
    }

    delay(1000);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-GLOBAL-C33-001-Example-AnalogToSMS-03");

    Serial.println("Send analog pin A0 value every 5 seconds for 30 seconds...");
    for (int i = 1; i <= 6; i++) {
        sensorValue = analogRead(analogInPin);
        message = String(i) + "/6 Analog value: " + String(sensorValue);
        cellular.sendSMS(phoneNumber, message);
        Serial.println(message);
        delay(5000);
    }

    Serial.println();
    Serial.println("---------");
    Serial.print("End of Test Scenario ID: ");
    Serial.println(testScenarioID);
    Serial.println("---------");
    Serial.println();
}

void loop(){
    // Empty loop
}