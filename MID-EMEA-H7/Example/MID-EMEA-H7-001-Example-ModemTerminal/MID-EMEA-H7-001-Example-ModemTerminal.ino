/**
 * Test Scenario ID : MID-EMEA-H7-001-Example-ModemTerminal
 * 
 * This sketch demonstrates sending AT commands to the Arduino Pro 4G Module with the Arduino_Cellular library.
 * 
 * Test Case IDs :
 * MID-EMEA-H7-001-Example-ModemTerminal-01 -> Connect to cellular modem (APN)
 * MID-EMEA-H7-001-Example-ModemTerminal-02 -> Send AT
 * MID-EMEA-H7-001-Example-ModemTerminal-03 -> Send ATE0
 * MID-EMEA-H7-001-Example-ModemTerminal-04 -> Send ATE1
 * MID-EMEA-H7-001-Example-ModemTerminal-05 -> Send AT+CFUN?
 * MID-EMEA-H7-001-Example-ModemTerminal-06 -> Send AT+CPIN?
 * MID-EMEA-H7-001-Example-ModemTerminal-07 -> Send AT+CSQ
 * MID-EMEA-H7-001-Example-ModemTerminal-08 -> Send AT+CGDCONT?
 * MID-EMEA-H7-001-Example-ModemTerminal-09 -> Send AT+CGATT?
 * MID-EMEA-H7-001-Example-ModemTerminal-10 -> Send AT+COPS?
 * 
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

#include "ArduinoCellular.h"
#include "arduino_secrets.h"

const char testScenarioID[] = "MID-EMEA-H7-001-Example-ModemTerminal";

ArduinoCellular cellular = ArduinoCellular();

String response = "";
String ATCommand = "";

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
    Serial.println("MID-EMEA-H7-001-Example-ModemTerminal-01");

    if(!cellular.connect(SECRET_GPRS_APN)){
        Serial.println("Failed to connect to the network.");
    } else {
        Serial.println("Connected to the network!");
    }
    
    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-ModemTerminal-02");
    Serial.println("Send AT...");
    response = cellular.sendATCommand("");
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-ModemTerminal-03");
    Serial.println("Send ATE0...");
    response = cellular.sendATCommand("E0");
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-ModemTerminal-04");
    Serial.println("Send ATE1...");
    response = cellular.sendATCommand("E1");
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-ModemTerminal-05");
    Serial.println("Send AT+CFUN?...");
    response = cellular.sendATCommand("+CFUN?");
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-ModemTerminal-06");
    Serial.println("Send AT+CPIN?...");
    response = cellular.sendATCommand("+CPIN?");
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-ModemTerminal-07");
    Serial.println("Send AT+CSQ...");
    response = cellular.sendATCommand("+CSQ");
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-ModemTerminal-08");
    Serial.println("Send AT+CGDCONT?...");
    response = cellular.sendATCommand("+CGDCONT?");
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-ModemTerminal-09");
    Serial.println("Send AT+CGATT?...");
    response = cellular.sendATCommand("+CGATT?");
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-ModemTerminal-09");
    Serial.println("Send AT+COPS?...");
    response = cellular.sendATCommand("+COPS?");
    Serial.println(response);

    Serial.println();
    Serial.println("---------");
    Serial.print("End of Test Scenario ID: ");
    Serial.println(testScenarioID);
    Serial.println("---------");
    Serial.println();
}

void loop() {
    // Empty loop
}