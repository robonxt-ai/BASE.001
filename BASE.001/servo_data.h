// Servo setting default values and stuff
#define MAX_SERVO_ALLOWED 33        // Remember that code starts from 0 , but only have servos 1-32
#define SERVO_FACTORY_POS 1500      // Range of board is ~500-2500ms, half is 1500ms (for programmer use only)
#define SERVOS_IN_LEG 5             // Number of servos per leg
#define MOVE_DEFAULT_TIME 550       // Default time of delay for servos
#define SERVO_MIN_DURATION 100      // Minimum time that servos can delay (last checked was 100ms)

// Easy to read names for the servos. Also lets us know which one is connected to which port
#define L_HIP_ROLL      8
#define L_HIP_PITCH     9

#define L_KNEE_PITCH    10
#define L_ANKLE_PITCH   11
#define L_ANKLE_ROLL    12

#define R_ANKLE_ROLL    21
#define R_ANKLE_PITCH   22
#define R_KNEE_PITCH    23

#define R_HIP_PITCH     24
#define R_HIP_ROLL      25

// [servo_id (manual) | "center position" (manual)]
int SERVODEFAULT[][2]
{
    8, 970,     // L_HIP_ROLL
    9, 1390,    // L_HIP_PITCH
    10, 1490,   // L_KNEE_PITCH
    11, 1490,   // L_ANKLE_PITCH
    12, 1490,   // L_ANKLE_ROLL
    21, 1520,   // R_ANKLE_ROLL
    22, 1485,   // R_ANKLE_PITCH
    23, 1570,   // R_KNEE_PITCH
    24, 1550,   // R_HIP_PITCH
    25, 2010    // R_HIP_ROLL
};


// [servo_id (manual) | default (manual) | rel_min (manual) | rel_max (manual) | abs_min (generated) | abs_max (generated)]
//int SERVODEFAULT[33][6]
//{
//    0,  -1, -1, -1, -1, -1,         // Does not exist. There is no "Servo 0"
//    1,  1500, 1000, 1000, -1, -1,   // HEAD_YAW
//    2,  -1500, 1000, 1000, -1, -1,   // L_ARM_ROLL
//    3,  -1500, 1000, 1000, -1, -1,   // L_SHOULD_ROLL
//    4,  -1500, 1000, 1000, -1, -1,   // L_SHOULD_PITCH
//    5,  -1, -1, -1, -1, -1,
//    6,  -1, -1, -1, -1, -1,
//    7,  -1, -1, -1, -1, -1,
//    8,   970, 300, 1200, -1, -1,    // L_HIP_ROLL
//    9,  1430, 1000, 1000, -1, -1,   // L_HIP_PITCH
//    10, 1510, 1000, 1000, -1, -1,   // L_KNEE_PITCH
//    11, 1490, 1000, 1000, -1, -1,   // L_ANKLE_PITCH
//    12, 1460, 280, 520, -1, -1,     // L_ANKLE_ROLL
//    13, -1, -1, -1, -1, -1,
//    14, -1, -1, -1, -1, -1,
//    15, -1, -1, -1, -1, -1,
//    16, -1, -1, -1, -1, -1,
//    17, -1, -1, -1, -1, -1,
//    18, -1, -1, -1, -1, -1,
//    19, -1, -1, -1, -1, -1,
//    20, -1, -1, -1, -1, -1,
//    21, 1480, 520, 280, -1, -1,     // R_ANKLE_ROLL
//    22, 1550, 1000, 1000, -1, -1,   // R_ANKLE_PITCH
//    23, 1500, 1000, 1000, -1, -1,   // R_KNEE_PITCH
//    24, 1550, 1000, 1000, -1, -1,   // R_HIP_PITCH
//    25, 2040, 1200, 300, -1, -1,    // R_HIP_ROLL
//    26, -1, -1, -1, -1, -1,
//    27, -1, -1, -1, -1, -1,
//    28, -1, -1, -1, -1, -1,
//    29, -1500, 1000, 1000, -1, -1,   // R_SHOULD_PITCH
//    30, -1500, 1000, 1000, -1, -1,   // R_SHOULD_ROLL
//    31, -1550, 1000, 1000, -1, -1,   // R_ARM_ROLL
//    32, -1, -1, -1, -1, -1
//};
