/* 
 * File:   application.c
 * Author: LEGION
 *
 * Created on August 10, 2024, 10:07 PM
 */


#include "application.h"



led_t led_1 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};

led_t led_2 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_LOW
};

led_t led_3 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .led_status = GPIO_LOW
};

led_t led_4 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN3,
    .led_status = GPIO_LOW
};

led_t led_5 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN4,
    .led_status = GPIO_LOW
};

led_t led_6 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN5,
    .led_status = GPIO_LOW
};

led_t led_7 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN6,
    .led_status = GPIO_LOW
};
led_t led_8 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN7,
    .led_status = GPIO_LOW
};

button_t btn_high = {
    .button_pin.port = PORTD_INDEX,
    .button_pin.pin = GPIO_PIN0,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn_low = {
    .button_pin.port = PORTD_INDEX,
    .button_pin.pin = GPIO_PIN1,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_HIGH,
    .button_connection = BUTTON_ACTIVE_LOW,
    .button_state = BUTTON_RELEASED
};

relay_t relay_1 = {
    .relay_port = PORTD_INDEX,
    .relay_pin = GPIO_PIN2,
    .relay_status = RELAY_OFF_STATUS
};
/*
relay_t relay_2 = {
    .relay_port = PORTD_INDEX,
    .relay_pin = GPIO_PIN3,
    .relay_status = RELAY_OFF_STATUS
};
*/

STD_ReturnType ret = E_NOK;

button_state_t btn_status_high;
button_state_t btn_status_low;

uint8 flag = 0;
uint32 btn_high_valid = 0;
button_state_t btn_high_valid_status = BUTTON_RELEASED;
button_state_t btn_high_last_valid_status = BUTTON_RELEASED;

uint32 btn_low_valid = 0;
button_state_t btn_low_valid_status = BUTTON_RELEASED;
button_state_t btn_low_last_valid_status = BUTTON_RELEASED;

int main() {

    application_initialize();
   relay_turn_off(&relay_1);
    while (1) {

  
        ret = button_read_state(&btn_high, &btn_status_high);
        ret = button_read_state(&btn_low, &btn_status_low);
        /*
              led_turn_toggle(&led_1);
              __delay_ms(500);
              led_turn_toggle(&led_2);
              __delay_ms(500);
              led_turn_toggle(&led_3);
              __delay_ms(500);
              led_turn_toggle(&led_4);
              __delay_ms(500);
              led_turn_toggle(&led_5);
              __delay_ms(500);
              led_turn_toggle(&led_6);
              __delay_ms(500);
              led_turn_toggle(&led_7);
              __delay_ms(500);
              led_turn_toggle(&led_8);
              __delay_ms(500);

         */

        if (BUTTON_PRESSED == btn_status_high) {
            btn_high_valid++;
            if (btn_high_valid > 500) {
                btn_high_valid_status = BUTTON_PRESSED;
            }

        } else {
            btn_high_valid = 0;
            btn_high_valid_status = BUTTON_RELEASED;
        }

        if (btn_high_valid_status != btn_high_last_valid_status) {
            btn_high_last_valid_status = btn_high_valid_status;
            if ((BUTTON_PRESSED == btn_high_valid_status) && (0 == flag)) {
                led_turn_on(&led_1);
                led_turn_on(&led_2);
                led_turn_on(&led_3);
                led_turn_on(&led_4);
                relay_turn_on(&relay_1);
               // ret = relay_turn_on(&relay_2);
                flag = 1;
            } else if ((BUTTON_PRESSED == btn_high_valid_status) && (1 == flag)) {
                led_turn_off(&led_1);
                led_turn_off(&led_2);
                led_turn_off(&led_3);
                led_turn_off(&led_4);
                relay_turn_off(&relay_1);
                //ret = relay_turn_off(&relay_2);
                flag = 0;
            }
        }

        if (BUTTON_PRESSED == btn_status_low) {
            btn_low_valid++;
            if (btn_low_valid > 200) {
                btn_low_valid_status = BUTTON_PRESSED;
            }

        } else {
            btn_low_valid = 0;
            btn_low_valid_status = BUTTON_RELEASED;
        }

        if (btn_low_valid_status != btn_low_last_valid_status) {
            btn_low_last_valid_status = btn_low_valid_status;
            if (BUTTON_PRESSED == btn_low_valid_status) {
                led_turn_on(&led_5);
                led_turn_on(&led_6);
                led_turn_on(&led_7);
                led_turn_on(&led_8);

            } else {
                led_turn_off(&led_5);
                led_turn_off(&led_6);
                led_turn_off(&led_7);
                led_turn_off(&led_8);
            }
        }



        /*
        if ((BUTTON_PRESSED == btn_status_high) && (0 == flag)) {
            led_turn_on(&led_1);
            led_turn_on(&led_2);
            led_turn_on(&led_3);
            led_turn_on(&led_4);
            flag = 1;
        } else if ((BUTTON_PRESSED == btn_status_high) && (1 == flag)) {
            led_turn_off(&led_1);
            led_turn_off(&led_2);
            led_turn_off(&led_3);
            led_turn_off(&led_4);
            flag = 0;
        }
         
        if (BUTTON_PRESSED == btn_status_low) {
            led_turn_on(&led_5);
            led_turn_on(&led_6);
            led_turn_on(&led_7);
            led_turn_on(&led_8);
        } else {
            led_turn_off(&led_5);
            led_turn_off(&led_6);
            led_turn_off(&led_7);
            led_turn_off(&led_8);
        }
         */
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void) {

    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    ret = led_initialize(&led_3);
    ret = led_initialize(&led_4);
    ret = led_initialize(&led_5);
    ret = led_initialize(&led_6);
    ret = led_initialize(&led_7);
    ret = led_initialize(&led_8);

    ret = button_initialize(&btn_high);
    ret = button_initialize(&btn_low);

    ret = relay_initialize(&relay_1);
    //ret = relay_initialize(&relay_2);
}

