#include "eFirebase.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// String pathToAllData = "/All Data/";
// String pathToRealtimeData = "/Realtime Data/";

WiFiUDP ntpUDP;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);

String getFormattedTime() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();

  epochTime += 7 * 3600;  // 7 hours * 3600 seconds/hour
  
  struct tm *ptm = gmtime((time_t *)&epochTime);

  int year = ptm->tm_year + 1900;
  int month = ptm->tm_mon + 1;
  int day = ptm->tm_mday;
  int hour = ptm->tm_hour;
  int minute = ptm->tm_min;
  int second = ptm->tm_sec;

  // Format the time as "year:month:day hour:minute:second"
  char formattedTime[20];
  sprintf(formattedTime, "%04d:%02d:%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

  return String(formattedTime);
}

void eFirebase::begin(String WIFI_SSID, String WIFI_PASSWORD, String API_KEY, String DATABASE_URL){

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED){
        Serial.print(F("."));
        delay(300);
    }
    
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    timeClient.begin();
    while (!timeClient.update()) {
        timeClient.forceUpdate();
    }

    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    if (Firebase.signUp(&config, &auth, "", "")){
        Serial.println("ok");
        signupOK = true;
    }
    else{
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }

    config.token_status_callback = tokenStatusCallback; 
    config.max_token_generation_retry = 5;
    
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

void eFirebase::sendData(int bldc1, int bldc2, int bldc3, int bldc4, int bldc5, int bldc6, int bldc7, int bldc8, int bldc9, int temp, int press1, int press2, int rpm){   
    
    static int allDataKey = 240730; // 2407301 (+1)

    String main_path = "/Realtime Data";
    String second_path = "/All Data/" + String(allDataKey);

    String sensor_path = "/Sensor";
    String temp_path = sensor_path + "/Temperature";
    String press1_path = sensor_path + "/Pressure/Before";
    String press2_path = sensor_path + "/Pressure/After";

    String bldc_path = "/BLDC";

    String bldc_paths[] = {
        bldc_path + "/1",
        bldc_path + "/2",
        bldc_path + "/3",
        bldc_path + "/4",
        bldc_path + "/5",
        bldc_path + "/6",
        bldc_path + "/7",
        bldc_path + "/8",
        bldc_path + "/9"
    };

    String formattedDateTime = getFormattedTime();
    String timestamp_path = "/timestamp";

    String rpm_path = "/RPM";
    // String rpm_value = rpm;


    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
        sendDataPrevMillis = millis();

        json.clear();

        json.set(temp_path, temp);
        json.set(press1_path, press1);
        json.set(press2_path, press2);

        int bldc_values[] = {bldc1, bldc2, bldc3, bldc4, bldc5, bldc6, bldc7, bldc8, bldc9};
        
        // json.set(bldc_paths[1] + "/Speed", bldc_values[1]);
        // json.set(bldc_paths[2] + "/Speed", bldc_values[2]);
        // json.set(bldc_paths[3] + "/Speed", bldc_values[3]);
        // json.set(bldc_paths[4] + "/Speed", bldc_values[4]);
        // json.set(bldc_paths[5] + "/Speed", bldc_values[5]);
        // json.set(bldc_paths[6] + "/Speed", bldc_values[6]);
        // json.set(bldc_paths[7] + "/Speed", bldc_values[7]);
        // json.set(bldc_paths[8] + "/Speed", bldc_values[8]);
        

        for (int i = 0; i < 9; i++)
        {
            json.set(bldc_paths[i] + "/Speed", bldc_values[i]);
            Serial.printf("bldc_values[%d]: %d\n", i, bldc_values[i]);
        }

        json.set(rpm_path, rpm);
        
        json.set(timestamp_path, formattedDateTime);

        Serial.print("JSON data: ");
        String jsonStr;
        json.toString(jsonStr);
        Serial.println(jsonStr);

        Serial.printf("Send To Realtime Data..... %s\n", Firebase.RTDB.setJSON(&fbdo, main_path.c_str(), &json) ? "success!" : fbdo.errorReason().c_str());    
        Serial.printf("Send To All Data..... %s\n", Firebase.RTDB.setJSON(&fbdo, second_path.c_str(), &json) ? "success!" : fbdo.errorReason().c_str());    

        allDataKey += 1;
    }   
}