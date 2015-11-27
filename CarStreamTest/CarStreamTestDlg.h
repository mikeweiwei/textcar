
// CarStreamTestDlg.h : 头文件
//
#include <cv.h>
#include <highgui.h>
#include "CvvImage.h"


#pragma once


// CCarStreamTestDlg 对话框
class CCarStreamTestDlg : public CDialog
{
// 构造
public:
	CCarStreamTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CARSTREAMTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CvvImage cvv_src_Image;
	HDC hDC_src_image1;
	HDC hDC_src_image2;
	HDC hDC_src_image3;
	HDC hDC_src_image4;
	CRect rect_src_image1;
	CRect rect_src_image2;
	CRect rect_src_image3;
	CRect rect_src_image4;
	CDC *pDC_src_image1;
	CDC *pDC_src_image2;
	CDC *pDC_src_image3;
	CDC *pDC_src_image4;
	CWinThread* m_pThread;
	CvCapture* VideoFile1;
	CvCapture* VideoFile2;
	CvCapture* VideoFile3;
	CvCapture* VideoFile4;
	CvSize frame_size;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_Number1;
	int m_Number2;
	int m_Number3;
	int m_Number4;
	afx_msg void OnBnClickedCheck();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedOk();
};
