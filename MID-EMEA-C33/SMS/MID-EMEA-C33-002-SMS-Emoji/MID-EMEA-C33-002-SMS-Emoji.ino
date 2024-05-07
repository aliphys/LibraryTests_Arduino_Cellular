/**
 * Test Scenario ID : MID-EMEA-C33-002-SMS-Emoji
 * 
 * This sketch sends emojis to a phone number.
 * 
 * Test Case IDs :
 * MID-EMEA-C33-002-SMS-Emoji-01 -> Send Tears of Joy emoji (😂)
 * MID-EMEA-C33-002-SMS-Emoji-02 -> Send Thumbs Up with Medium Skin Tone (👍🏽)
 * MID-EMEA-C33-002-SMS-Emoji-03 -> Send Man Cartwheeling (🤸‍♂️)
 * 
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

const char testScenarioID[] = "MID-EMEA-C33-002-SMS-Emoji";

String phoneNumber = "+46XXXXXXXXX";
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
    Serial.println("MID-EMEA-C33-002-SMS-Emoji-01");
    Serial.println("Send Tears of Joy emoji (😂)...");
    message = "😂";
    Serial.println(message);
    cellular.sendSMS(phoneNumber, message);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-C33-002-SMS-Emoji-02");
    Serial.println("Send Thumbs Up with Medium Skin Tone (👍🏽)...");
    message = "👍🏽";
    Serial.println(message);
    cellular.sendSMS(phoneNumber, message);
    
    
    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-C33-002-SMS-Emoji-03");
    Serial.println("Send Man Cartwheeling (🤸‍♂️)...");
    message = "🤸‍♂️";
    Serial.println(message);
    cellular.sendSMS(phoneNumber, message);  
    

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