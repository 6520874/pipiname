#pragma once

class CKeyboardHook
{
public:
	CKeyboardHook(void);
	~CKeyboardHook(void);
	LRESULT CALLBACK LowLevelKeyboardProc(int nCode,WPARAM wParam,LPARAM lParam);

};
