#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "XBOXController.h"
#include <XInput.h>

XBOXController* Player1;
void mouseClick(unsigned downClick, unsigned upClick);
int _tmain(int argc, _TCHAR* argv[])
{
	Player1 = new XBOXController(1);


	 while(true)
    {
        if(Player1->IsConnected())
        {
            if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
            {
				std::cout<<"Left Click"<<std::endl;
                mouseClick(0x0002,0x0004);//left down and up
				Sleep(200);
            }

            if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
            {
				std::cout<<"Right Click"<<std::endl;
                mouseClick(0x0008, 0x0010);
				Sleep(200);
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

void mouseClick(unsigned downClick, unsigned upClick){  
	 //leftdown/up  == 0x0002, 0x0004
	 //rightdown/up == 0x0008, 0x0010

	INPUT    Input={0};
	// left down 
	Input.type      = INPUT_MOUSE;
	Input.mi.dwFlags  = downClick;// MOUSEEVENTF_LEFTDOWN
	::SendInput(1,&Input,sizeof(INPUT));

	// left up
	::ZeroMemory(&Input,sizeof(INPUT));
	Input.type      = INPUT_MOUSE;
	Input.mi.dwFlags  = upClick;//MOUSEEVENTF_LEFTUP;
	::SendInput(1,&Input,sizeof(INPUT));
}