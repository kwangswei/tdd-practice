#ifndef __LIGHT_CONTROLLER_H_
#define __LIGHT_CONTROLLER_H_

const int LIGHT_ID_UNKNOWN = -1;
const int LIGHT_STATE_UNKNOWN = 100;

const int LIGHT_ON = 1;
const int LIGHT_OFF = 0;

class LightController {
    public:
        virtual ~LightController() {}

        virtual void on(int id) = 0;
        virtual void off(int id) = 0;
    private:

};

#endif
