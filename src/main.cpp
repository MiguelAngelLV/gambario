//
// Created by miguel on 10/02/19.
//


#include "esphomelib.h"
#include "Config.h"


#define LIGHT D6
#define FAN D7
#define TEMP D3

using namespace esphomelib;


void setup() {

    App.set_name(NAME);
    App.init_wifi(SSID, PASSWORD);
    App.init_mqtt(MQTT_HOST, MQTT_USER, MQTT_PASSWORD);

    App.init_ota()->start_safe_mode();


    auto * light = App.make_gpio_output(LIGHT);
    auto * dallas = App.make_dallas_component(TEMP);
    auto fan = App.make_fan("Ventilador");


    fan.output->set_speed(App.make_esp8266_pwm_output(FAN));

    App.register_fan(fan.state);
    App.register_sensor(dallas->get_sensor_by_index("Temperatura", 0));


    App.make_binary_light("Luz", light);


    App.setup();
}


void loop() {
    App.loop();

}