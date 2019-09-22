// GUIVRoller.h: interface for the CGUIVRoller class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUIVROLLER_H__9C9208EF_90AA_4D25_9178_7123242F545B__INCLUDED_)
#define AFX_GUIVROLLER_H__9C9208EF_90AA_4D25_9178_7123242F545B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*««ª½±²¶b*/
#include "GUIRoller.h"

class CGUIVRoller : public CGUIRoller  
{
private:
	int miNowPosY;
public:
	virtual LONG OnMOUSEMOVE(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam);
	virtual LONG OnLBUTTONUP(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam);
	virtual LONG OnLBUTTONDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam);
	virtual bool Display(void);
	CGUIVRoller();
	virtual ~CGUIVRoller();

};

#endif // !defined(AFX_GUIVROLLER_H__9C9208EF_90AA_4D25_9178_7123242F545B__INCLUDED_)
