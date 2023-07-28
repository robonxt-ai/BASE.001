/*
    Project Name:   BASE.001 - 2023 Onwards
    Description:    A (start from small)™ program. Main project for BASE.001
    Programmer:     robonxt
    Date Created:   2022.03.29
    Date Modified:  2023.07.26
    Version:        1.0.2
    Filename:       2023_Full_Robot_Feature_Test.ino

    Changelog:
    - 2022.03.29: Merging reset and squat + other stuff
    - 2022.04.02: Fixing
    - 2022.04.13: hmm
    - 2022.04.19: new stuff with built-in RTOS tasks
    - 2022.04.25: fully using tasks, still need to think about the stacks
    - 2022.07.28: merging new servo calibration values and system from BASE.001_PCA9685_Expander_demo
    - 2022.08.08: trying out a way to clean up the __FILE__ macro
    - 2022.08.09: more movements for buttons
    - 2023.01.01: updated the code to the latest platform.io version from 2022.11.??
    - 2023.05.23: small update to fix the sketch filename displaying the whole path, originally working if on platformio, but I switched back to normal Arduino IDE.
    - 2023.07.20: fixing walking gait to match with old static walking style.
    - 2023.07.25: walkingV13 off from MiniPlan

    To-do:
    - [Not Started] Self-balancing
    - [Not Started] Fall recovery


    Goals:
    - [Not Started] Dynamic walking

*/


#define IS_DEBUGGING_ENABLED false                   // Is debugging enabled for all?
#define __UPLOADTIME__       __DATE__ " " __TIME__  // When was the program uploaded?
char* __SKETCHNAME__;                               // What is the name of the sketch?

// For vTasks delay use only!
#define vDelay(k) vTaskDelay(k / portTICK_PERIOD_MS);

/*  ------------------------------------------------------------------------------------------------------  */
// Default baudrates for each serial port (serial, bluetooth)
#define SERIAL_BAUDRATE 115200  // SERIAL = Serial communication

#define BLUETOOTH_BAUDRATE 115200  // SERIAL = Serial communication

//// For ServoEasing controller ////
// Must specify these before the including ServoEasing.hpp
#define USE_PCA9685_SERVO_EXPANDER
#define DISABLE_COMPLEX_FUNCTIONS
#define MAX_EASING_SERVOS        16
#define PCA9685_EXPANDER_ADDRESS PCA9685_DEFAULT_ADDRESS
#define NUMBER_OF_SERVOS         MAX_EASING_SERVOS
#include <ServoEasing.hpp>

#define R_Y_HIP 10
#define R_R_HIP 11
#define R_P_HIP 12
#define R_P_KNE 13
#define R_P_ANK 14
#define R_R_ANK 15

#define L_Y_HIP 5
#define L_R_HIP 4
#define L_P_HIP 3
#define L_P_KNE 2
#define L_P_ANK 1
#define L_R_ANK 0


/*
    leg ranges
    servo: "center value" "(min deg, max deg)" relative to center value
    hip yaw: 90 (-30, 50)
    hip roll: 90 (-5, 57)
    hip pitch: 80 (-29, +96)
    knee pitch: 180 (-130, +0)
    ankle pitch: 90 (-51, +79)
    ankle roll: 90 (-57, +37)
*/

int R_Y_HIP_deg = 0, R_R_HIP_deg = 0, R_P_HIP_deg = 0, R_P_KNE_deg = 0, R_P_ANK_deg = 0, R_R_ANK_deg = 0;
int L_Y_HIP_deg = 0, L_R_HIP_deg = 0, L_P_HIP_deg = 0, L_P_KNE_deg = 0, L_P_ANK_deg = 0, L_R_ANK_deg = 0;

// -------------------- L_R_ANK L_P_ANK L_P_KNE L_P_HIP L_R_HIP L_Y_HIP ------------------------------- R_Y_HIP R_R_HIP R_P_HIP R_P_KNE R_P_ANK R_R_ANK
int S_MIN[16]    = {    -57,    -51,    -130,   -29,    -5,     -30,    -1,     -1,     -1,     -1,     -30,    -5,     -29,    -130,   -51,    -57     };
int S_CENTER[16] = {    90,     90,     180,    80,     90,     93,     -1,     -1,     -1,     -1,     93,     90,     80,     180,    90,     90      };
int S_MAX[16]    = {    +37,    +79,    +0,     +96,    +57,    +50,    -1,     -1,     -1,     -1,     +50,    +57,    +96,    +0,     +79,    +37     };

// this is the important one! calibrating it for each servo
int S_MS_MIN[16] = {    2630,   545,    460,    600,    2670,   2580,   -1,     -1,     -1,     -1,     485,    470,    500,    430,    525,    640     };
int S_MS_MAX[16] = {    570,    2575,   2555,   2735,   495,    450,    -1,     -1,     -1,     -1,     2540,   2470,   2630,   2500,   2550,   2650    };

#define MOVE_DEFAULT_TIME 750  // Default time of delay for servos
#define READY_ANGLE       15   // stuff
#define BEND_ANGLE        45   // stuff
#define LIFT_ANGLE        70   // stuff
#define MAX_ANGLE         130  // stuff

//// For TFT stuff ////
#include "robonxt_logos.h"
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI(135, 240);

//// For Button stuff ////
#include <Button2.h>
#define BUTTON_PIN_1 35
#define BUTTON_PIN_2 0
Button2 button_1;
Button2 button_2;

//// For robot status ////
bool rIsError  = false;
bool rIsMoving = false;
bool goingToSleep = false;
int legCalibrateTilt = 2;


/*  ------------------------------------------------------------------------------------------------------  */
//! Long time delay, it is recommended to use shallow sleep, which can effectively reduce the current consumption
#define espDelay(ms) \
    esp_sleep_enable_timer_wakeup(ms * 1000); \
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON); \
    esp_light_sleep_start();

#define tftMsg(msg)                                                     \
    tft.setTextColor(TFT_RED, TFT_BLACK, true);                         \
    tft.setTextSize(1);                                                 \
    tft.setTextDatum(TR_DATUM);                                         \
    tft.setTextWrap(true);                                              \
    tft.setCursor(0, 70);                                               \
    tft.print(F("                                                  ")); \
    tft.setCursor(0, 70);                                               \
    tft.println(F(msg));                                                \
    if (IS_DEBUGGING_ENABLED){ Serial.println(F(msg)); }

/*  ------------------------------------------------------------------------------------------------------  */

//// TIME TO INCLUDE ALL THE FILES ////
#include "move.h"
#include "tasks.h"

void attachServos()
{
    ServoEasing* tServoEasingObjectPtr;
    Serial.print(F("Get ServoEasing objects and attach servos to PCA9685 expander at address=0x"));
    Serial.println(PCA9685_EXPANDER_ADDRESS, HEX);
    for (int i = 0; i < PCA9685_MAX_CHANNELS; ++i)
    {
        tServoEasingObjectPtr = new ServoEasing(PCA9685_EXPANDER_ADDRESS, &Wire);
        tServoEasingObjectPtr->attach(i, S_CENTER[i], S_MS_MIN[i], S_MS_MAX[i]);
        tServoEasingObjectPtr->setEasingType(EASE_QUADRATIC_IN_OUT);
    }
}

void servo_setup()
{
    Wire.begin(26, 27);  // Starts with 100 kHz. Clock will be increased at first attach() except for ESP32.
    checkI2CConnection(PCA9685_EXPANDER_ADDRESS, &Serial);
    attachServos();
    setSpeedForAllServos(30);  // This speed is taken if no further speed argument is given.
    servoReset(false);
}

void about_program()
{
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.pushImage(0, 5, 240, 64, robonxt_logo_thin);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.setTextDatum(TR_DATUM);
    tft.setTextWrap(true);
    tft.setCursor(0, tft.height() - 25);
    tft.println(F("DEV: robonxt"));
    tft.println(F("VER: " __UPLOADTIME__));
    tft.print(F("PRG: "));
    tft.println(F(__SKETCHNAME__));

    Serial.flush();
    Serial.println();
    Serial.println(F("DEV: robonxt"));
    Serial.println(F("VER: " __UPLOADTIME__));
    Serial.print(F("PRG: "));
    Serial.println(F(__SKETCHNAME__));
}

void display_setup()
{
    // init tft!
    tft.init();
    about_program();
}

void esp_deep_sleep(void)
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("DEEP SLEEP MODE", tft.width() / 2, tft.height() / 2);
    espDelay(700);
    tft.writecommand(TFT_DISPOFF);
    tft.writecommand(TFT_SLPIN);
    esp_deep_sleep_disable_rom_logging();
    esp_sleep_config_gpio_isolate();  // Need this to stop the ESP from turning on from other sources!
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 0);

    esp_deep_sleep_start();
}


void handler(Button2& btn)
{
    if (btn == button_1)
    {
        walkingV13(4);
    }
    else if (btn == button_2)
    {
        walkingV10(2, 1);
    }
}

void longhandler(Button2& btn)
{
    unsigned int timePressed = btn.wasPressedFor();
    if (btn == button_1 && timePressed > 1500)
    {
        long currMillis = millis();
        tftMsg("powering down...");
        R_P_HIP_deg = S_CENTER[R_P_HIP] + 60;
        R_P_KNE_deg = S_CENTER[R_P_KNE] - 120;
        R_P_ANK_deg = S_CENTER[R_P_ANK] - 60;
        L_P_HIP_deg = S_CENTER[L_P_HIP] + 60;
        L_P_KNE_deg = S_CENTER[L_P_KNE] - 120;
        L_P_ANK_deg = S_CENTER[L_P_ANK] - 60;
        actionDelayALL(2000);
        goingToSleep = true;
        esp_deep_sleep();
    }
    else if (btn == button_2 && timePressed > 1500)
    {
        rSquatTest();
    }
}

void button_setup()
{
    button_1.begin(BUTTON_PIN_1);
    button_1.setClickHandler(handler);
    button_1.setLongClickHandler(longhandler);

    button_2.begin(BUTTON_PIN_2);
    button_2.setClickHandler(handler);
    button_2.setLongClickHandler(longhandler);
}

/*  ------------------------------------------------------------------------------------------------------  */

void setup()
{
    delay(50);
    // set up Serial
    Serial.begin(SERIAL_BAUDRATE);
    delay(50);
    Serial.flush();
    Serial.print("Wakeup: ");
    Serial.println(esp_sleep_get_wakeup_cause());

    // Set up SKETCHNAME!
#ifdef PLATFORMIO
    char a[] = PROJECT_PATH;
    byte b = sizeof(a);
    while ((b > 0) && (a[b] != '/'))
        b--;
    __SKETCHNAME__ = &a[++b];
#else
    char a[] = __FILE__;
    byte b = sizeof(a);
    while ((b > 0) && (a[b] != '\\'))
        b--;
    __SKETCHNAME__ = &a[++b];
#endif

    ////////////////////////



    // set up tft
    display_setup();

    // set up buttons
    button_setup();

    // set up servos
    servo_setup();

    xTaskCreatePinnedToCore(TaskHeartBeat, "Heartbeat", 1028 /*Stack size*/, NULL, 500 /*Priority*/, NULL, 0);
}

void loop()
{
    espDelay(50);
    // stuff that needs to be looped put here?
    button_1.loop();
    button_2.loop();
    // most stuff done in tasks.h!
}
