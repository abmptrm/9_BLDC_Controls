#ifndef EFIREBASE_H_
#define EFIREBASE
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Firebase_ESP_Client.h> 



#include <string.h>

// extern String pathToAllData = "/All Data";
// extern String pathToRealtimeData = "/Realtime Data";
// extern int allDataKey = 240730;

class eFirebase {
    private:

    public:
    void begin(String API_KEY, String DATABASE_URL);
    void sendData(int bldc1, int bldc2, int bldc3, int bldc4, int bldc5, int bldc6, int bldc7, int bldc8, int bldc9, int temp, int press1, int press2, int rpm);    // void sendAllData(int bldc1, int bldc2, int bldc3, int bldc4, int bldc5, int bldc6, int bldc7, int bldc8, int bldc9, int temp, int press);


};

#endif