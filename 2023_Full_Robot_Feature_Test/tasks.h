 void TaskHeartBeat(void *pvParameters)  // This is a task.
 {
     for (;;)
     {
         tft.fillCircle((tft.width() - 5), 5, 3, (rIsError ? TFT_RED : TFT_GREEN));
         vDelay(500);
         tft.fillCircle((tft.width() - 5), 5, 3, TFT_BLACK);
         vDelay(500);
     }
 }
