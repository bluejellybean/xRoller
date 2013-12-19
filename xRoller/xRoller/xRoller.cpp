#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "XBOXController.h"
#include "inputActions.h"
#include <XInput.h>

XBOXController* Player1;

int _tmain(int argc, _TCHAR* argv[])
{
	Player1 = new XBOXController(1);
	inputActions inputActions;

	 while(true)
    {
        if(Player1->IsConnected())
        {
            if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
            {
				std::cout<<"Left Click"<<std::endl;
                inputActions.mouseClick(0x0002,0x0004);//left down and up
				Sleep(200);
            }

            if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
            {
				std::cout<<"Right Click"<<std::endl;
                inputActions.mouseClick(0x0008, 0x0010);
				Sleep(200);
            }
			if(Player1->GetState().Gamepad.bLeftTrigger > 0 )

          // if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
            {
                Player1->Vibrate(65535, 65535);
            }

            if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
            {
                mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
				Sleep(200);
            }

			if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
            {
                mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120, 0);
				Sleep(200);
            }
        }
        else
        {
            std::cout << "\n\tERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
            std::cout << "Press Any Key To Exit.";
            std::cin.get();
            break;
        }
    }

	     delete(Player1);

	return 0;
}