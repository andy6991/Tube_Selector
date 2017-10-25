// Tube_Selector.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CTube_SelectorApp:
// See Tube_Selector.cpp for the implementation of this class
//

class CTube_SelectorApp : public CWinApp
{
public:
	CTube_SelectorApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTube_SelectorApp theApp;