#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "SNGCJA5Sensor.h"
#include "TelemetrySensor.h"
#include <SparkFun_Particle_Sensor_SN-GCJA5_Arduino_Library.h>
#include <typeinfo>

SNGCJA5Sensor::SNGCJA5Sensor() : TelemetrySensor(meshtastic_TelemetrySensorType_PANASONIC_PM, "SNGCJA5") {}

int32_t SNGCJA5Sensor::runOnce()
{
    LOG_INFO("Init sensor: %s", sensorName);
    if (!hasSensor()) {
        return DEFAULT_SENSOR_MINIMUM_WAIT_TIME_BETWEEN_READS;
    }
    status = SNGCJA5.begin(*nodeTelemetrySensorsMap[sensorType].second); //dereferenced

    //bme280.setSampling(Adafruit_BME280::MODE_FORCED,
    //                   Adafruit_BME280::SAMPLING_X1, // Temp. oversampling
    //                   Adafruit_BME280::SAMPLING_X1, // Pressure oversampling
    //                   Adafruit_BME280::SAMPLING_X1, // Humidity oversampling
    //                   Adafruit_BME280::FILTER_OFF, Adafruit_BME280::STANDBY_MS_1000);

    return initI2CSensor();
}

void SNGCJA5Sensor::setup() {}

bool SNGCJA5Sensor::getMetrics(meshtastic_Telemetry *measurement)
{
    measurement->variant.air_quality_metrics.has_pm10_environmental = true;
    measurement->variant.air_quality_metrics.has_pm25_environmental = true;
    measurement->variant.air_quality_metrics.has_pm100_environmental = true;

    LOG_DEBUG("SNGCJA5 getMetrics");
    measurement->variant.air_quality_metrics.pm10_environmental = SNGCJA5.getPM1_0();
    measurement->variant.air_quality_metrics.pm25_environmental = SNGCJA5.getPM2_5();
    measurement->variant.air_quality_metrics.pm100_environmental = SNGCJA5.getPM10();

    return true;
}
#endif