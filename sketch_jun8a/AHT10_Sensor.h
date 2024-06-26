#include <Adafruit_AHT10.h>



class AHT10_Sensor
{
private:
    /* data */
    Adafruit_AHT10 aht;

    Adafruit_Sensor *aht_humidity, *aht_temp;

    aht_temp = aht.getTemperatureSensor();

public:
    AHT10_Sensor();   
    ~AHT10_Sensor();
    void AHT10_Sensor_begin() {
        if (!aht.begin()) {
        Serial.println("Failed to find AHT10 chip");
        while (1) {
            delay(10);
            }
        }

        aht_temp->printSensorDetails();
        Serial.println("AHT10 Found!");
    }
    void AHT10_Sensor_readData() {
        return
    }

};

AHT10_Sensor::AHT10_Sensor(/* args */)
{  
}

AHT10_Sensor::~AHT10_Sensor()
{
}


