#ifndef STICK_H
#define STICK_H

#include <Windows.h>
#include <ViGEm/Client.h>
#include <iostream>
#include <map>
#include <functional>
#include <limits>
#undef min
#undef max


class Stick
{
public:
    PVIGEM_CLIENT client;
    PVIGEM_TARGET x360c;
    XUSB_REPORT state;
    static const SHORT SHORT_MAX = std::numeric_limits<SHORT>::max();
    Stick(){
        client = vigem_alloc();
        vigem_connect(client);
        x360c = vigem_target_x360_alloc();
        vigem_target_add(client, x360c);
        state = {};
    };
    void update(float x, float y){
        state.wButtons |=  XUSB_GAMEPAD_LEFT_THUMB;
        state.sThumbLX = x * SHORT_MAX;
        state.sThumbLY = y * SHORT_MAX;
        vigem_target_x360_update(client, x360c, state);
    };
    ~Stick(){
        vigem_target_free(x360c);
        vigem_free(client);
    };

};

#endif // STICK_H
