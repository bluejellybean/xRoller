#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "XBOXController.h"
#include "inputActions.h"
#include <XInput.h>
#include <math.h>

XBOXController* Player1;

int _tmain(int argc, _TCHAR* argv[])
{
	Player1 = new XBOXController(1);
	inputActions inputActions;
				int x = 100;
				int y = 100;
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

				float normLX = max(-1, (float) Player1->GetState().Gamepad.sThumbLX / 32767);
				float normLY = max(-1, (float) Player1->GetState().Gamepad.sThumbLY / 32767);
				std::cout<<normLX<<" "<<normLY<<std::endl;

				float deadzoneX = 0.09f;
				float deadzoneY = 0.15f;
 
				float leftStickX = (abs(normLX) < deadzoneX ? 0 : normLX);
				float leftStickY = (abs(normLY) < deadzoneY ? 0 : normLY);

				std::cout<<leftStickX<<" "<<leftStickY<<std::endl;

				//Sleep(100);

				if(leftStickX > .3 ){
					x+=1;
				} else if (leftStickX < -.3){
					x-=1;
				}

				if(leftStickY > .3) {
					y-=1;
				} else if (leftStickY < -.3){
					y+=1;
				}
				
				
				std::cout<<x<<" "<<y<<std::endl;
				SetCursorPos(x,y);
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