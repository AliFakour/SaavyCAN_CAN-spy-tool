// ICDILight.h : main header file for the ICDILight application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CICDILightApp:
// See ICDILight.cpp for the implementation of this class
//

class CICDILightApp : public CWinApp
{
public:
	CICDILightApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CICDILightApp theApp;
