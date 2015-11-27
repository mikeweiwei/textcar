
// CarStreamTestDlg.h : ͷ�ļ�
//
#include <cv.h>
#include <highgui.h>
#include "CvvImage.h"


#pragma once


// CCarStreamTestDlg �Ի���
class CCarStreamTestDlg : public CDialog
{
// ����
public:
	CCarStreamTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CARSTREAMTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

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
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
