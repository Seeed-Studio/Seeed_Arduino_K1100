#include "grove_soil_sensor.h"
#include "SensorsUtils.h"

grove_soil_sensor::grove_soil_sensor() {
}
void grove_soil_sensor::init() {
    is_available = (Grove_I2C_Check(softwarei2c)) ? false : true;
}

bool grove_soil_sensor::read(struct sensor_data *sdata) {
    uint16_t sum = 0, data[READ_NUM] = {0};
    double   variance = 0.0;
    init();
    if (!is_available) {
        return false;
    }
    analogRead(SOILPIN);
    delay(2);
    // sum
    for (int i = 0; i < READ_NUM; i++) {
        data[i] = analogRead(SOILPIN);
        delayMicroseconds(2);
        sum += data[i];
    }
    //Find the variance
    for (int i = 0; i < READ_NUM; i++) {
        variance = variance + pow(data[i] - sum / READ_NUM, 2);
    }
    variance = variance / READ_NUM;

    if (variance > DATA_VARIANCE_MAX || sum / READ_NUM > SOIL_DATA_MAX)
        return false;
    soil_value       = sum / READ_NUM;
    sdata->data      = &soil_value;
    sdata->data_type = SENSOR_DATA_TYPE_INT32;
    sdata->size      = sizeof(soil_value);
    sdata->id        = GROVE_SOIL;
    sdata->name      = name;
    sdata->ui_type   = SENSOR_UI_TYPE_NORMAL;
    sdata->data_unit = data_unit;
    sdata->status    = true;
    return true;
}

const char *grove_soil_sensor::get_name() {
    return "soil";
}

// grove_soil_sensor  buildin_soil;       // Serial.println("Measurement failed!");