/**
 * Test Scenario ID : MID-GLOBAL-H7-001-Example-HTTPClient
 * 
 * This sketch demonstrates how to get the time with the Arduino Pro 4G Module.
 * 
 * Test Case IDs :
 * MID-GLOBAL-H7-001-Example-HTTPClient-01 -> Connect to Network via SIM card
 * MID-GLOBAL-H7-001-Example-HTTPClient-02 -> Perform GET request
 * 
 * NOTE: This example uses a test server that may not be available in the future.
 * NOTE: Enter your APN in arduino_secrets.h file.
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
 * Initial author: Cristian Dragomir @cristidragomir97
 * Modified by: Ali Jahangiri @aliphys
 */

#define ARDUINO_CELLULAR_DEBUG

#include "ArduinoCellular.h"
#include "arduino_secrets.h"

const char testScenarioID[] = "MID-GLOBAL-H7-001-Example-HTTPClient";

const char server[]   = "vsh.pp.ua";
const char resource[] = "/TinyGSM/logo.txt";
const int  port       = 80;

ArduinoCellular cellular = ArduinoCellular();
HttpClient client = cellular.getHTTPClient(server, port);

void getResource();

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

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-GLOBAL-H7-001-Example-HTTPClient-01");

    Serial.println("Connecting...");
    if(!cellular.connect(SECRET_GPRS_APN)){
        Serial.println("Failed to connect to the network.");
    } else {
        Serial.println("Connected to the network!");
    }

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-GLOBAL-H7-001-Example-HTTPClient-02");

    getResource();

    Serial.println();
    Serial.println("---------");
    Serial.print("End of Test Scenario ID: ");
    Serial.println(testScenarioID);
    Serial.println("---------");
    Serial.println();
}

void loop(){}


void getResource(){

  Serial.println("Making GET request...");

  client.get(resource);

  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  client.stop();
}
