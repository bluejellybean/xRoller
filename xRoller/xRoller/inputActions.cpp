#include "stdafx.h"
#include "inputActions.h"
#include <Windows.h>

inputActions::inputActions(void)
{
}


void inputActions::mouseClick(unsigned downClick, unsigned upClick){
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


inputActions::~inputActions(void)
{
}
