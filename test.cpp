//#include <Windows.h>
//#include <ViGEm/Client.h>
//#include <iostream>
//#include <map>
//#include <functional>
//#include <limits>
//#undef min
//#undef max

//int main() {
//    PVIGEM_CLIENT client = vigem_alloc();
//    vigem_connect(client);

//    PVIGEM_TARGET x360c = vigem_target_x360_alloc();
//    vigem_target_add(client, x360c);

//    XUSB_REPORT state = {};

//    std::map<std::string, std::function<void(char)>> cmds;

//    // Clear
//    cmds.emplace("", [&](char mod) {
//        if (mod == '@') state = {};
//    });

//    // A
//    cmds.emplace("A", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_A; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_A; break;
//        }
//    });

//    // B
//    cmds.emplace("B", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_B; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_B; break;
//        }
//    });

//    // X
//    cmds.emplace("X", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_X; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_X; break;
//        }
//    });

//    // Y
//    cmds.emplace("Y", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_Y; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_Y; break;
//        }
//    });

//    // Left Shoulder
//    cmds.emplace("LB", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_LEFT_SHOULDER; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_LEFT_SHOULDER; break;
//        }
//    });

//    // Right Shoulder
//    cmds.emplace("RB", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_RIGHT_SHOULDER; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_RIGHT_SHOULDER; break;
//        }
//    });

//    // Left Trigger
//    cmds.emplace("LT", [&](char mod) {
//        switch (mod) {
//        case '+': state.bLeftTrigger = std::numeric_limits<BYTE>::max(); break;
//        case '-': state.bLeftTrigger = 0; break;
//        }
//    });

//    // Right Trigger
//    cmds.emplace("RT", [&](char mod) {
//        switch (mod) {
//        case '+': state.bLeftTrigger = std::numeric_limits<BYTE>::max(); break;
//        case '-': state.bLeftTrigger = 0; break;
//        }
//    });

//    // Start
//    cmds.emplace("START", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_START; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_START; break;
//        }
//    });

//    // Back
//    cmds.emplace("BACK", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_BACK; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_BACK; break;
//        }
//    });

//    // Guide
//    cmds.emplace("GUIDE", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_GUIDE; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_GUIDE; break;
//        }
//    });

//    // DPad
//    cmds.emplace("D", [&](char mod) {
//        state.wButtons &= ~0xF;

//        switch (mod) {
//        case '1':
//            state.wButtons |= XUSB_GAMEPAD_DPAD_LEFT;
//            state.wButtons |= XUSB_GAMEPAD_DPAD_DOWN;
//            break;
//        case '2':
//            state.wButtons |= XUSB_GAMEPAD_DPAD_DOWN;
//            break;
//        case '3':
//            state.wButtons |= XUSB_GAMEPAD_DPAD_RIGHT;
//            state.wButtons |= XUSB_GAMEPAD_DPAD_DOWN;
//            break;
//        case '4':
//            state.wButtons |= XUSB_GAMEPAD_DPAD_LEFT;
//            break;
//        case '5':
//            break;
//        case '6':
//            state.wButtons |= XUSB_GAMEPAD_DPAD_RIGHT;
//            break;
//        case '7':
//            state.wButtons |= XUSB_GAMEPAD_DPAD_LEFT;
//            state.wButtons |= XUSB_GAMEPAD_DPAD_UP;
//            break;
//        case '8':
//            state.wButtons |= XUSB_GAMEPAD_DPAD_UP;
//            break;
//        case '9':
//            state.wButtons |= XUSB_GAMEPAD_DPAD_RIGHT;
//            state.wButtons |= XUSB_GAMEPAD_DPAD_UP;
//            break;
//        }
//    });

//    // Left Stick
//    cmds.emplace("L", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_LEFT_THUMB; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_LEFT_THUMB; break;
//        }

//        state.sThumbLX = 0;
//        state.sThumbLY = 0;

//        static const SHORT SHORT_MIN = std::numeric_limits<SHORT>::min();
//        static const SHORT SHORT_MAX = std::numeric_limits<SHORT>::max();

//        switch (mod) {
//        case '1':
//            state.sThumbLX = SHORT_MIN;
//            state.sThumbLY = SHORT_MIN;
//            break;
//        case '2':
//            state.sThumbLY = SHORT_MIN;
//            break;
//        case '3':
//            state.sThumbLX = SHORT_MAX;
//            state.sThumbLY = SHORT_MIN;
//            break;
//        case '4':
//            state.sThumbLX = SHORT_MIN;
//            break;
//        case '5':
//            break;
//        case '6':
//            state.sThumbLX = SHORT_MAX;
//            break;
//        case '7':
//            state.sThumbLX = SHORT_MIN;
//            state.sThumbLY = SHORT_MAX;
//            break;
//        case '8':
//            state.sThumbLY = SHORT_MAX;
//            break;
//        case '9':
//            state.sThumbLX = SHORT_MAX;
//            state.sThumbLY = SHORT_MAX;
//            break;
//        }
//    });

//    // Right Stick
//    cmds.emplace("R", [&](char mod) {
//        switch (mod) {
//        case '+': state.wButtons |=  XUSB_GAMEPAD_RIGHT_THUMB; break;
//        case '-': state.wButtons &= ~XUSB_GAMEPAD_RIGHT_THUMB; break;
//        }

//        state.sThumbRX = 0;
//        state.sThumbRY = 0;

//        static const SHORT SHORT_MIN = std::numeric_limits<SHORT>::min();
//        static const SHORT SHORT_MAX = std::numeric_limits<SHORT>::max();

//        switch (mod) {
//        case '1':
//            state.sThumbRX = SHORT_MIN;
//            state.sThumbRY = SHORT_MIN;
//            break;
//        case '2':
//            state.sThumbRY = SHORT_MIN;
//            break;
//        case '3':
//            state.sThumbRX = SHORT_MAX;
//            state.sThumbRY = SHORT_MIN;
//            break;
//        case '4':
//            state.sThumbRX = SHORT_MIN;
//            break;
//        case '5':
//            break;
//        case '6':
//            state.sThumbRX = SHORT_MAX;
//            break;
//        case '7':
//            state.sThumbRX = SHORT_MIN;
//            state.sThumbRY = SHORT_MAX;
//            break;
//        case '8':
//            state.sThumbRY = SHORT_MAX;
//            break;
//        case '9':
//            state.sThumbRX = SHORT_MAX;
//            state.sThumbRY = SHORT_MAX;
//            break;
//        }
//    });


//    char c;
//    std::string cmd;
//    while (c = std::cin.get(), c != '!') {
//        if (c == ' ' || c == '\n') {
//            if (cmd.size() > 0) {
//                auto i = cmds.find(cmd.substr(0, cmd.size() - 1));
//                if (i != cmds.end()) {
//                    i->second(cmd[cmd.size() - 1]);
//                    vigem_target_x360_update(client, x360c, state);
//                }
//                cmd = "";
//            }
//        } else {
//            cmd += c;
//        }
//    }

//    vigem_target_free(x360c);
//    vigem_free(client);

//    return 0;
//}
