#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "XBOXController.h"
#include "inputActions.h"
#include <XInput.h>

XBOXController* Player1;
float currentVolume = 0;

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
                inputActions.leftClick();
				
            }

            if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
            {
                inputActions.rightClick();
				Sleep(400);
            }

			if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y){
				
			}

			if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
            {
				inputActions.simulateKeys(0xA6);//browser back
				Sleep(400);
            }

			if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
            {
				inputActions.simulateKeys(0xA7);//browser forward
				Sleep(400);
            }

			if(Player1->GetState().Gamepad.bLeftTrigger > 0 )
			{
				//inputActions.simulateKeys(0x20);
			}

			if(Player1->GetState().Gamepad.bRightTrigger > 0 )
			{
				
				currentVolume = inputActions.getCurrentMasterVolume(0, true); //TODO: look into getting rid of 0 and true, may not need

				while (Player1->GetState().Gamepad.bRightTrigger > 0 )
				{
					double triggerValue = ((Player1->GetState().Gamepad.bRightTrigger * 1000) / 255) / 10 * .01;
					double newVolume = currentVolume - triggerValue;
					inputActions.changeVolume(newVolume, true);
				}

				inputActions.changeVolume(currentVolume, true);
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