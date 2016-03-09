
// MyFirstOpenMesh.h : main header file for the MyFirstOpenMesh application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMyFirstOpenMeshApp:
// See MyFirstOpenMesh.cpp for the implementation of this class
//

class CMyFirstOpenMeshApp : public CWinApp
{
public:
	CMyFirstOpenMeshApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyFirstOpenMeshApp theApp;
