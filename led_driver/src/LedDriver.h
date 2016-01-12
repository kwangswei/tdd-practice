#ifndef __LED_DRIVER_H_
#define __LED_DRIVER_H_

const int ALL_LED_ON = ~0;
const int ALL_LED_OFF = ~ALL_LED_ON;

const int FIRST_LED = 1;
const int LAST_LED = 16;


class LedDriver {
    public:
        LedDriver(unsigned short* _address) : address(_address) {
            led_image = ALL_LED_OFF;
            update_hardware();
        }

        void turn_on(int led_num) {
            if (is_led_out_of_bounds(led_num))
                return;

            led_image |= convert_led_number_to_bit(led_num);
            update_hardware();
        }

        void turn_off(int led_num) {
            if (is_led_out_of_bounds(led_num))
                return;

            led_image &= ~convert_led_number_to_bit(led_num);
            update_hardware();
        }

        void turn_all_on() {
            led_image = ALL_LED_ON;
            update_hardware();
        }

        void turn_all_off() {
            led_image = ALL_LED_OFF;
            update_hardware();
        }

        bool is_on(int led_num) {
            if (is_led_out_of_bounds(led_num))
                return false;

            return led_image & convert_led_number_to_bit(led_num);
        }

        bool is_off(int led_num) {
            return !is_on(led_num);
        }



    private:
        void update_hardware() {
            *address = led_image;
        }

        bool is_led_out_of_bounds(int led_num) {
            return led_num < FIRST_LED || led_num > LAST_LED;
        }

        unsigned int convert_led_number_to_bit(int led_num) {
            return 1 << (led_num - 1);
        }

        unsigned short* address;
        unsigned short led_image;
};

#endif
