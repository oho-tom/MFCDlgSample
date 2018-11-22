
// MyAppDlg.h : ヘッダー ファイル
//

#pragma once


// CMyAppDlg ダイアログ
class CMyAppDlg : public CDialogEx
{
// コンストラクション
public:
	CMyAppDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonSelectInputPath();
	afx_msg void OnBnClickedButtonSelectOutputPath();
	afx_msg void OnBnClickedButtonExecute();

private:
	// 入力パス
	CEdit edit_input_path;
	// 出力パス
	CEdit edit_output_path;
	// アプリケーションの状態(待機中、実行中)
	CEdit edit_app_status;

	// 入出力パスのチェック
	bool CheckPath();
	// 実行処理
	static UINT Execute(LPVOID pParam);
	// ダイアログのアイテムの有効無効を切り替える
	void EnableDialogItem(const bool& isEnable);
};
