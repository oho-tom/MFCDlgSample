
// MyApp.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMyApp:
// このクラスの実装については、MyApp.cpp を参照してください
//

class CMyApp : public CWinApp
{
public:
	CMyApp();

// オーバーライド
public:
	//! 初期化処理
	virtual BOOL InitInstance();
	//! 終了処理
	virtual int ExitInstance();

// 実装

	DECLARE_MESSAGE_MAP()

private:
	HANDLE			mutex_app_;		//!< 多重起動防止用ミューテックス
};

extern CMyApp theApp;
