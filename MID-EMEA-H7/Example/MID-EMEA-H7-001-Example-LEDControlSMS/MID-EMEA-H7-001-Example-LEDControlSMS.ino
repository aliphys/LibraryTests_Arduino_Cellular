/**
 * Test Scenario ID : MID-EMEA-H7-001-Example-LEDControlSMS
 * 
 * This sketch demonstrates how to control the build-in Portenta LED with SMS messages.
 * 
 * Test Case IDs :
 * MID-EMEA-H7-001-Example-LEDControlSMS-01 -> Blink LED 3 times upon startup
 * MID-EMEA-H7-001-Example-LEDControlSMS-02 -> Turn LED on when sending "on"
 * MID-EMEA-H7-001-Example-LEDControlSMS-03 -> Turn LED off when sending "off"
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

constexpr int NEW_SMS_INTERRUPT_PIN = A0;

ArduinoCellular cellular = ArduinoCellular();
volatile boolean smsReceived = false;
constexpr int POLLING_INTERVAL_MS = 1 * 10 * 1000; // 10 seconds

const char testScenarioID[] = "MID-EMEA-H7-001-Example-LEDControlSMS";

volatile boolean stateChange = false;

void printMessages();
void onSMSReceived();    

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
    Serial.println("MID-EMEA-H7-001-Example-LEDControlSMS-01");
    Serial.println("Blink LED 3 times upon startup...");
    pinMode(LED_BUILTIN, OUTPUT);
    for (int i = 0; i < 3; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
    }

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-LEDControlSMS-02");
    Serial.println("Turn LED on when sending 'on'...");

    // Register interrupt based callback for new SMS
    attachInterrupt(digitalPinToInterrupt(NEW_SMS_INTERRUPT_PIN), onSMSReceived, RISING);

    stateChange = false;
    Serial.println("Waiting for SMS...");

    while(!stateChange){
        static unsigned long lastPoll = 0;
        static bool checkForNewSMS = false;

        if(millis() - lastPoll > POLLING_INTERVAL_MS){
            checkForNewSMS = true;
            lastPoll = millis();
        }

        if(smsReceived || checkForNewSMS){
            smsReceived = false;
            checkForNewSMS = false;
            std::vector<SMS> unreadSMS = cellular.getUnreadSMS();

            if (unreadSMS.size() > 0){
                Serial.println("Unread SMS:");
                printMessages(unreadSMS);
                for(int i = 0; i < unreadSMS.size(); i++){
                    if(unreadSMS[i].message == "on"){
                        digitalWrite(LED_BUILTIN, HIGH);
                        Serial.println("LED turned HIGH");
                        stateChange = true;
                    } else if(unreadSMS[i].message == "off"){
                        digitalWrite(LED_BUILTIN, LOW);
                        Serial.println("LED already LOW");
                    }
                    cellular.deleteSMS(unreadSMS[i].index);
                }
            }
        }

        delay(POLLING_INTERVAL_MS);
    }

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println("MID-EMEA-H7-001-Example-LEDControlSMS-03");
    Serial.println("Turn LED off when sending 'off'...");


    stateChange = false;
    Serial.println("Waiting for SMS...");

    while(!stateChange){
        static unsigned long lastPoll = 0;
        static bool checkForNewSMS = false;

        if(millis() - lastPoll > POLLING_INTERVAL_MS){
            checkForNewSMS = true;
            lastPoll = millis();
        }

        if(smsReceived || checkForNewSMS){
            smsReceived = false;
            checkForNewSMS = false;
            std::vector<SMS> unreadSMS = cellular.getUnreadSMS();

            if (unreadSMS.size() > 0){
                Serial.println("Unread SMS:");
                printMessages(unreadSMS);
                for(int i = 0; i < unreadSMS.size(); i++){
                    if(unreadSMS[i].message == "on"){
                        digitalWrite(LED_BUILTIN, HIGH);
                        Serial.println("LED already HIGH");
                        stateChange = true;
                    } else if(unreadSMS[i].message == "off"){
                        digitalWrite(LED_BUILTIN, LOW);
                        Serial.println("LED turned LOW");
                        stateChange = true;
                    }
                    cellular.deleteSMS(unreadSMS[i].index);
                }
            }
        }

        delay(POLLING_INTERVAL_MS);
    }


}

void loop(){
    // empty loop
}

void printMessages(std::vector<SMS> msg){
     for(int i = 0; i < msg.size(); i++){
        Serial.println("SMS:");
        Serial.print("* Index: "); Serial.println(msg[i].index);
        Serial.print("* From: "); Serial.println(msg[i].sender);
        Serial.print("* Timestamp: "); Serial.println(msg[i].timestamp.getISO8601());
        Serial.println("* Message: "); Serial.println(msg[i].message);
        Serial.println("--------------------\n");
    }
}
void onSMSReceived(){
    smsReceived = true;
    Serial.println("SMS Received!");
}