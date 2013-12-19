#pragma once
#include <windows.h>
#include <XInput.h>

#pragma comment(lib, "XInput.lib")

class XBOXController
{
private:
    XINPUT_STATE _controllerState;
    int _controllerNum;
public:
    XBOXController(int playerNumber);
    XINPUT_STATE GetState();
    bool IsConnected();
    void Vibrate(int leftVal = 0, int rightVal = 0);
};
//test comment
