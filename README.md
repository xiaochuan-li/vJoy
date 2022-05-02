# VJoy

Short for virtual joystick, witch use the headpose as the input to control games.

## Several hight-lights:
* [mediapipe](https://github.com/google/mediapipe) as face-tracking module, which means light weight(cpu), fast(real-time) ...
* [ViGEm](https://github.com/ViGEm/ViGEmBus) for the driver support. No need for extra configurations.
* [QHotKey](https://github.com/Skycoder42/QHotkey) for global hotkey support. Eazy to use.

## Refer to the release for prebuild packages
Do remember to install ViGEmBus at the very begining.

## What's next ?
- [x] Qt implementation 
- [ ] more complex operations
- [ ] direct communication with ViGEm
- [ ] ...

## Updates
- 2022/5/3 
    - replacing ViGEm-interface with ViGEmClient, making the movements contiue and smooth.
    - adding necessary dlls to the archive, including opencv_world452, zlib and hdf5.