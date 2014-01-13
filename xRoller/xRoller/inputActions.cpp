#include "stdafx.h"
#include "inputActions.h"
#include <Windows.h>

#include <mmdeviceapi.h>
#include <endpointvolume.h>
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

	Sleep(400);
}

void inputActions::leftClick(){
	mouseClick(0x0002,0x0004);
}

void inputActions::rightClick(){
	mouseClick(0x0008, 0x0010);
}

void inputActions::simulateKeys(int keyType){
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = keyType;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	//keyup
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

//	Sleep(400);

}



float inputActions::getCurrentVolume(double nVolume,bool bScalar)
{
 
    HRESULT hr=NULL;
    bool decibels = false;
    bool scalar = false;
    double newVolume=nVolume;
 
    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, 
                          __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;
 
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;
 
    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), 
         CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

	float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevel(&currentVolume);
	hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
    //CString strCur=L"";
    //strCur.Format(L"%f",currentVolume);
    //AfxMessageBox(strCur);

	 return currentVolume;
}


bool inputActions::changeVolume(double nVolume,bool bScalar)
{
 
    HRESULT hr=NULL;
    bool decibels = false;
    bool scalar = false;
    double newVolume=nVolume;
 
    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, 
                          __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;
 
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;
 
    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), 
         CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;
 
    // -------------------------
    float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevel(&currentVolume);

    hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
    //CString strCur=L"";
    //strCur.Format(L"%f",currentVolume);
    //AfxMessageBox(strCur);

    if (bScalar==false)
    {
        hr = endpointVolume->SetMasterVolumeLevel((float)newVolume, NULL);
    }
    else if (bScalar==true)
    {
        hr = endpointVolume->SetMasterVolumeLevelScalar((float)newVolume, NULL);
    }
    endpointVolume->Release();
 
    CoUninitialize();
 
    return FALSE;
}

inputActions::~inputActions(void)
{
}
