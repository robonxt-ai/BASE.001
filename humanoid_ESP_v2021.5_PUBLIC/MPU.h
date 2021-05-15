/*
    MPU code for BASE.001
    ------
    A (start from small)™ program
    ------
    Designed for version: humanoid_ESP_v2021.4.ino
    Last modified: 2021.03.24
    Programmer: robonxt
    ------
    Changelogs:
    2021.03.24: Initial commit.

*/

// Working as of 2021.03.24

void calibrateMPU()
{

    // Calibration
    Debug.print(DBG_INFO, F("Calibrating..."));

    mpu.Calibrate();

    Debug.print(DBG_ERROR, F("GyroX Offset: %.2f \nGyroY Offset: %.2f  \nGyroZ Offset: %.2f"), mpu.GetGyroXOffset() , mpu.GetGyroYOffset() , mpu.GetGyroZOffset() );

    if ((mpu.GetGyroXOffset() == (mpu.GetGyroYOffset())) || (mpu.GetGyroXOffset() == (mpu.GetGyroZOffset())) )
    {
        gSTATE = -1;
        Debug.print(DBG_ERROR, F("GYRO CALIBRATION ERROR!"));
    }
    else
    {
        gSTATE = 0;
        Debug.print(DBG_INFO, F("Calibration complete!"));
    }
}

void setupMPU()
{
    Debug.print(DBG_INFO, F("- Gyro setup %s -"), "START");

    // Initialization
    mpu.Initialize();
    // Calibration

    //calibrateMPU();

    // If calibration fails, try this one!
    // Calibrated on 2021.04.14 in robot body in sitting pose upright
    mpu.SetGyroOffsets(746.73, -117.34, 38.99);
    Debug.print(DBG_INFO, F("- Gyro setup %s -"), "DONE");

}

void MPU_print()
{
    mpu.Execute();
    Debug.print(DBG_INFO, F("AngX: %.2f  / AngY: %.2f  / AngZ: %.2f"), mpu.GetAngX() , mpu.GetAngY() , mpu.GetAngZ() );
}
