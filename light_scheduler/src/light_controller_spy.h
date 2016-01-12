#ifndef __LIGHT_CONTROLLER_SPY_H_
#define __LIGHT_CONTROLLER_SPY_H_

#include "light_controller.h"

class LightControllerSpy : public LightController {
    public:
        LightControllerSpy() : last_id(LIGHT_ID_UNKNOWN), last_state(LIGHT_STATE_UNKNOWN) {}

        int get_last_id() {
            return last_id;
        }

        int get_last_state() {
            return last_state;
        }

        void on(int id) {
            last_id = id;
            last_state = LIGHT_ON;
        }

        void off(int id) {
            last_id = id;
            last_state = LIGHT_OFF;
        }

        int last_id;
        int last_state;
};

#endif
