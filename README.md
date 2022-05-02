# VJoy

Short for virtual joystick, witch use the headpose as the input to control games.

## Several hight-lights:
* [mediapipe](https://github.com/google/mediapipe) as face-tracking module, which means light weight(cpu), fast(real-time) ...
* [ViGEm](https://github.com/ViGEm/ViGEmBus) for the driver support. No need for extra configurations.
* [QHotKey](https://github.com/Skycoder42/QHotkey) for global hotkey support. Eazy to use.

## Refer to the release for prebuild packages
Do remember to install ViGEmBus at the very begining (a prebuilt .msi setupfile is provided in /path/to/your/installation/mediapipe/, just double click it and ViGEmBus will be installed).
## How to use ?
Just double click the icon to start the program. press `ctrl + S` to enable/disable emulation, and press `ctrl + Q` to stop the program.
## What's next ?
- [x] Qt implementation 
- [ ] more complex operations
- [ ] direct communication with ViGEm
- [ ] ...

## Updates
- 2022/5/3 
    - replacing [ViGEm-interface](https://github.com/henrikvik/vigem-interface) with [ViGEmClient](https://github.com/ViGEm/ViGEmClient), making the movements contiue and smooth.
    - adding necessary dlls to the archive, including opencv_world452, zlib and hdf5.