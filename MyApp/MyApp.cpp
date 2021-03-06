
// MyApp.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "MyApp.h"
#include "MyAppDlg.h"

#include "constant.h"
#include "string_utility.h"
#include "winapi_utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace string_utility;
using namespace winapi_utility;

// CMyApp

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyApp の構築

CMyApp::CMyApp()
	: mutex_app_(NULL)
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CMyApp オブジェクト

CMyApp theApp;


// CMyApp の初期化

BOOL CMyApp::InitInstance()
{
	CWinApp::InitInstance();


	// ダイアログにシェル ツリー ビューまたはシェル リスト ビュー コントロールが
	// 含まれている場合にシェル マネージャーを作成します。
	CShellManager *pShellManager = new CShellManager;

	// MFC コントロールでテーマを有効にするために、"Windows ネイティブ" のビジュアル マネージャーをアクティブ化
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	// ツールのパス
	CString module_directory;
	GetModuleDirectory(module_directory);

	//--------------------------------------------------------------------------
	// 多重起動検査
	//--------------------------------------------------------------------------
	mutex_app_ = ::CreateMutex(NULL, TRUE, (LPTSTR)kAppName);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox(kMessageAppDuplicated, MB_OK | MB_ICONERROR);
		return false;
	}

	CMyAppDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: ダイアログの作成に失敗しました。アプリケーションは予期せずに終了します。\n");
		TRACE(traceAppMsg, 0, "警告: ダイアログで MFC コントロールを使用している場合、#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS を指定できません。\n");
	}

	// 上で作成されたシェル マネージャーを削除します。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

/*
@brief 終了処理
@param なし
@retval TRUE 正常終了
@retval FALSE 異常終了
*/
int CMyApp::ExitInstance()
{
	//--------------------------------------------------------------------------
	// ミューテックスの破棄
	//--------------------------------------------------------------------------
	if (mutex_app_ != NULL)
	{
		::ReleaseMutex(mutex_app_);
		CloseHandle(mutex_app_);
		mutex_app_ = NULL;
	}

	return CWinApp::ExitInstance();
}
