#include "stdafx.h"
#include <iostream>
#include "XBOXController.h"
#include <XInput.h>

XBOXController* Player1;
int _tmain(int argc, _TCHAR* argv[])
{
	Player1 = new XBOXController(1);


	 while(true)
    {
        if(Player1->IsConnected())
        {
            if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
            {
                Player1->Vibrate(65535, 0);
            }

            if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
            {
                Player1->Vibrate(0, 65535);
            }
			if(Player1->GetState().Gamepad.bLeftTrigger > 0 )

          // if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
            {
                Player1->Vibrate(65535, 65535);
            }

            if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
            {
                Player1->Vibrate();
            }

            if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
            {
                break;
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

