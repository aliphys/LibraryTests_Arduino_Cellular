/**
 * Test Scenario ID : MID-EMEA-H7-001-Example-DeleteSMS
 * 
 * Via AT commands and the ArduinoCellular library, this sketch demonstrates how create and delete an SMS message.
 * 
 * Test Case IDs :
 * MID-EMEA-H7-001-Example-DeleteSMS-01 -> Set Modem to SMS Text Mode
 * MID-EMEA-H7-001-Example-DeleteSMS-02 -> Select message storage area
 * MID-EMEA-H7-001-Example-DeleteSMS-03 -> Set SMSC number to be stored with text message
 * MID-EMEA-H7-001-Example-DeleteSMS-04 -> Write SMS message
 * MID-EMEA-H7-001-Example-DeleteSMS-05 -> Read SMS message
 * MID-EMEA-H7-001-Example-DeleteSMS-06 -> Delete SMS message
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
 * Initial author: Sebastian Romero @sebromero
 * Modified by: Ali Jahangiri @aliphys
 */

#include "ArduinoCellular.h"

const char testScenarioID[] = "MID-EMEA-H7-001-Example-DeleteSMS";

ArduinoCellular cellular = ArduinoCellular();

void printMessages() {};

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

    Serial.println("Connecting to network...");
    if (cellular.connect()) {
        Serial.println("Connected!");
    } else {
        Serial.println("Failed to connect to network.");
    }

    delay(2000); // Give the modem some time to initialize

    Serial.println("Enabling Echo...");
    ATCommand = "E1";
    response = cellular.sendATCommand(ATCommand.c_str());
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-DeleteSMS-01");

    Serial.println("Setting SMS text mode...");
    ATCommand = "+CMGF=1";
    response = cellular.sendATCommand(ATCommand.c_str());
    Serial.println(response);


    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-DeleteSMS-02");

    Serial.println("Select message storage area...");
    // store all messages in SIM card
    ATCommand = "+CPMS=\"SM\",\"SM\",\"SM\"";
    response = cellular.sendATCommand(ATCommand.c_str());
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-DeleteSMS-03");

    Serial.println("Set SMSC number to be stored with text message...");
    ATCommand = "+CSCA=\"+1234567890\"";
    response = cellular.sendATCommand(ATCommand.c_str());
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-DeleteSMS-04");

    Serial.println("Write SMS message...");
    ATCommand = "+CMGW=\"+1234567890\",145,\"STO UNSENT\" \r \"Life is good\" \x1A";
    response = cellular.sendATCommand(ATCommand.c_str());
    Serial.println(response);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-DeleteSMS-05");
    
    Serial.println("Get unread SMS...");

    std::vector<SMS> readSMS = cellular.getReadSMS();
    if(readSMS.size() > 0){
        Serial.println("Read SMS:");
        printMessages(readSMS);
    }

    std::vector<SMS> unreadSMS = cellular.getUnreadSMS();
    if(unreadSMS.size() > 0){
        Serial.println("Unread SMS:");
        printMessages(unreadSMS);
    }

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-DeleteSMS-06");

    // Prompt user which SMS to delete
    Serial.println("Enter the index of the SMS you want to delete:");
    
    while(Serial.available() == 0);
    auto index = Serial.readStringUntil('\n').toInt();
    Serial.println("Deleting SMS...");

    if(cellular.deleteSMS(index)){
        Serial.println("SMS deleted.");
    } else {
        Serial.println("Failed to delete SMS.");
    }

    Serial.println();
    Serial.println("---------");
    Serial.print("End of Test Scenario ID: ");
    Serial.println(testScenarioID);
    Serial.println("---------");
    Serial.println();
}

void loop(){
  // empty
}

void printMessages(std::vector<SMS> msg) {
     for(int i = 0; i < msg.size(); i++){
        Serial.println("SMS:");
        Serial.print("* Index: "); Serial.println(msg[i].index);
        Serial.print("* From: "); Serial.println(msg[i].sender);
        Serial.print("* Timestamp: "); Serial.println(msg[i].timestamp.getISO8601());
        Serial.println("* Message: "); Serial.println(msg[i].message);
        Serial.println("--------------------\n");
    }
}