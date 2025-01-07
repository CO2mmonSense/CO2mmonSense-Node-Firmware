#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "TelemetrySensor.h"
#include <SparkFun_Particle_Sensor_SN-GCJA5_Arduino_Library.h>

class SNGCJA5Sensor : public TelemetrySensor
{
  private:
    SFE_PARTICLE_SENSOR SNGCJA5;

  protected:
    virtual void setup() override;

  public:
    SNGCJA5Sensor();
    virtual int32_t runOnce() override;
    virtual bool getMetrics(meshtastic_Telemetry *measurement) override;
};

#endif