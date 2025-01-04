#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "SCD30Sensor.h"
#include "TelemetrySensor.h"
#include <Adafruit_SCD30.h>
#include <typeinfo>

SCD30Sensor::SCD30Sensor() : TelemetrySensor(meshtastic_TelemetrySensorType_CUSTOM_SENSOR, "SCD30") {}

int32_t SCD30Sensor::runOnce()
{
    LOG_INFO("Init sensor: %s", sensorName);
    if (!hasSensor()) {
        return DEFAULT_SENSOR_MINIMUM_WAIT_TIME_BETWEEN_READS;
    }
    status = scd30.begin(nodeTelemetrySensorsMap[sensorType].first, nodeTelemetrySensorsMap[sensorType].second);

    //bme280.setSampling(Adafruit_BME280::MODE_FORCED,
    //                   Adafruit_BME280::SAMPLING_X1, // Temp. oversampling
    //                   Adafruit_BME280::SAMPLING_X1, // Pressure oversampling
    //                   Adafruit_BME280::SAMPLING_X1, // Humidity oversampling
    //                   Adafruit_BME280::FILTER_OFF, Adafruit_BME280::STANDBY_MS_1000);

    return initI2CSensor();
}

void SCD30Sensor::setup() {}

bool SCD30Sensor::getMetrics(meshtastic_Telemetry *measurement)
{
    measurement->variant.environment_metrics.has_temperature = true;
    measurement->variant.environment_metrics.has_relative_humidity = true;
    measurement->variant.air_quality_metrics.has_co2 = true;

    LOG_DEBUG("SCD30 getMetrics");
    scd30.read();
    measurement->variant.environment_metrics.temperature = scd30.temperature;
    measurement->variant.environment_metrics.relative_humidity = scd30.relative_humidity;
    measurement->variant.air_quality_metrics.co2 = scd30.CO2;

    return true;
}
#endif