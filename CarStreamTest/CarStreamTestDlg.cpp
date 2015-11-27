
// CarStreamTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarStreamTest.h"
#include "CarStreamTestDlg.h"
#include "CvvImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
int image_W = 640;
int image_H = 480;
int n1,n2,n3,n4;



class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCarStreamTestDlg 对话框




CCarStreamTestDlg::CCarStreamTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCarStreamTestDlg::IDD, pParent)
	, m_Number1(0)
	, m_Number2(0)
	, m_Number3(0)
	, m_Number4(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCarStreamTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM1, m_Number1);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_Number2);
	DDX_Text(pDX, IDC_EDIT_NUM3, m_Number3);
	DDX_Text(pDX, IDC_EDIT_NUM4, m_Number4);
}

BEGIN_MESSAGE_MAP(CCarStreamTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK, &CCarStreamTestDlg::OnBnClickedCheck)
	ON_BN_CLICKED(IDC_STOP, &CCarStreamTestDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDOK, &CCarStreamTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCarStreamTestDlg 消息处理程序

BOOL CCarStreamTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	n1=0;
	n2=0;
	n3=0;
	n4=0;
	pDC_src_image1 = GetDlgItem(IDC_PICTURE)->GetDC();
	hDC_src_image1 = pDC_src_image1->GetSafeHdc();
	GetDlgItem(IDC_PICTURE)->GetClientRect(&rect_src_image1);

	pDC_src_image2 = GetDlgItem(IDC_PICTURE2)->GetDC();
	hDC_src_image2 = pDC_src_image2->GetSafeHdc();
	GetDlgItem(IDC_PICTURE2)->GetClientRect(&rect_src_image2);

	pDC_src_image3 = GetDlgItem(IDC_PICTURE3)->GetDC();
	hDC_src_image3 = pDC_src_image3->GetSafeHdc();
	GetDlgItem(IDC_PICTURE3)->GetClientRect(&rect_src_image3);

	pDC_src_image4 = GetDlgItem(IDC_PICTURE4)->GetDC();
	hDC_src_image4 = pDC_src_image4->GetSafeHdc();
	GetDlgItem(IDC_PICTURE4)->GetClientRect(&rect_src_image4);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCarStreamTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCarStreamTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCarStreamTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//车道1
UINT ImgAcqRunCQ(LPVOID pParam)
{
	CCarStreamTestDlg *MultiThrDlg = (CCarStreamTestDlg*) pParam;

 	static int Car1_imageCount = 0;
	static int Car2_imageCount = 0;
	static int Car3_imageCount = 0;
	static int Car4_imageCount = 0;

 	double Car1_minVal, Car1_maxVal;
	double Car2_minVal, Car2_maxVal;
	double Car3_minVal, Car3_maxVal;
	double Car4_minVal, Car4_maxVal;

	CvPoint Car1_minLoc, Car1_maxLoc;
	CvPoint Car2_minLoc, Car2_maxLoc;
	CvPoint Car3_minLoc, Car3_maxLoc;
	CvPoint Car4_minLoc, Car4_maxLoc;
   
	int Car1_people=0;
	int Car1_MOVEMENT=0;

	int Car2_people=0;
	int Car2_MOVEMENT=0;

	int Car3_people=0;
	int Car3_MOVEMENT=0;

	int Car4_people=0;
	int Car4_MOVEMENT=0;

	IplImage* Car1_tempFrame1;
	IplImage* Car2_tempFrame1;
	IplImage* Car3_tempFrame1;
	IplImage* Car4_tempFrame1;


	int Car1_X1 = 220;
	int Car1_Y1 = image_H-180;
	int Car1_X2 = image_W-180;
	int Car1_Y2 = image_H-30;

	int Car2_X1 = 220;
	int Car2_Y1 = image_H-180;
	int Car2_X2 = image_W-220;
	int Car2_Y2 = image_H-30;

	int Car3_X1 = 220;
	int Car3_Y1 = image_H-180;
	int Car3_X2 = image_W-220;
	int Car3_Y2 = image_H-30;

	int Car4_X1 = 220;
	int Car4_Y1 = image_H-180;
	int Car4_X2 = image_W-220;
	int Car4_Y2 = image_H-30;

	CString Car1_NUM;
	CString Car2_NUM;
	CString Car3_NUM;
	CString Car4_NUM;
	CString fileWrite;

	IplImage* Car1_ROIFrameBGR = cvCreateImage(cvSize(Car1_X2-Car1_X1, Car1_Y2-Car1_Y1), IPL_DEPTH_8U, 3);
	IplImage* Car1_ROIFrameBGRPrior = cvCreateImage(cvSize(Car1_X2-Car1_X1, Car1_Y2-Car1_Y1), IPL_DEPTH_8U, 3);
	IplImage* Car1_diffFrame = cvCreateImage(cvSize(image_W, image_H), IPL_DEPTH_8U, 1);
	IplImage* Car1_currentFrame = cvCreateImage(cvSize(image_W, image_H), IPL_DEPTH_8U, 1);
	IplImage* Car1_backgroundFrame;

	IplImage* Car2_ROIFrameBGR = cvCreateImage(cvSize(Car2_X2-Car2_X1, Car2_Y2-Car2_Y1), IPL_DEPTH_8U, 3);
	IplImage* Car2_ROIFrameBGRPrior = cvCreateImage(cvSize(Car2_X2-Car2_X1, Car2_Y2-Car2_Y1), IPL_DEPTH_8U, 3);
	IplImage* Car2_diffFrame = cvCreateImage(cvSize(image_W, image_H), IPL_DEPTH_8U, 1);
	IplImage* Car2_currentFrame = cvCreateImage(cvSize(image_W, image_H), IPL_DEPTH_8U, 1);
	IplImage* Car2_backgroundFrame;

	IplImage* Car3_ROIFrameBGR = cvCreateImage(cvSize(Car2_X2-Car2_X1, Car2_Y2-Car2_Y1), IPL_DEPTH_8U, 3);
	IplImage* Car3_ROIFrameBGRPrior = cvCreateImage(cvSize(Car2_X2-Car2_X1, Car2_Y2-Car2_Y1), IPL_DEPTH_8U, 3);
	IplImage* Car3_diffFrame = cvCreateImage(cvSize(image_W, image_H), IPL_DEPTH_8U, 1);
	IplImage* Car3_currentFrame = cvCreateImage(cvSize(image_W, image_H), IPL_DEPTH_8U, 1);
	IplImage* Car3_backgroundFrame;

	IplImage* Car4_ROIFrameBGR = cvCreateImage(cvSize(Car2_X2-Car2_X1, Car2_Y2-Car2_Y1), IPL_DEPTH_8U, 3);
	IplImage* Car4_ROIFrameBGRPrior = cvCreateImage(cvSize(Car2_X2-Car2_X1, Car2_Y2-Car2_Y1), IPL_DEPTH_8U, 3);
	IplImage* Car4_diffFrame = cvCreateImage(cvSize(image_W, image_H), IPL_DEPTH_8U, 1);
	IplImage* Car4_currentFrame = cvCreateImage(cvSize(image_W, image_H), IPL_DEPTH_8U, 1);
	IplImage* Car4_backgroundFrame;

	cvZero(Car1_ROIFrameBGR);
	cvZero(Car2_ROIFrameBGR);
	cvZero(Car3_ROIFrameBGR);
	cvZero(Car4_ROIFrameBGR);

	Car1_tempFrame1 = cvQueryFrame(MultiThrDlg->VideoFile1);
	Car2_tempFrame1 = cvQueryFrame(MultiThrDlg->VideoFile2);
	Car3_tempFrame1 = cvQueryFrame(MultiThrDlg->VideoFile3);
	Car4_tempFrame1 = cvQueryFrame(MultiThrDlg->VideoFile4);

	int thresoldvalue = 100;

	for(;;)
	{
		Car1_tempFrame1 = cvQueryFrame(MultiThrDlg->VideoFile1);
		Car2_tempFrame1 = cvQueryFrame(MultiThrDlg->VideoFile2);
		Car3_tempFrame1 = cvQueryFrame(MultiThrDlg->VideoFile3);
		Car4_tempFrame1 = cvQueryFrame(MultiThrDlg->VideoFile4);
// 		Sleep(40);

		if ((Car1_tempFrame1 != NULL)&&
			(Car2_tempFrame1 != NULL)&&
			(Car3_tempFrame1 != NULL)&&
			(Car4_tempFrame1 != NULL))
		{
			//----------------车道1----------------//
			{
				IplImage* Car1_imageshow = cvCloneImage(Car1_tempFrame1);

				cvSmooth(Car1_tempFrame1, Car1_tempFrame1, CV_GAUSSIAN, 7,7);
				cvCvtColor(Car1_tempFrame1, Car1_currentFrame, CV_BGR2GRAY);

				if (Car1_imageCount==0)
					Car1_backgroundFrame = cvCloneImage(Car1_currentFrame);        //获取背景图像

				cvAbsDiff(Car1_currentFrame,Car1_backgroundFrame,Car1_diffFrame);
				IplImage* Car1_ROIFrame = cvCloneImage(Car1_diffFrame);

				cvSetImageROI(Car1_ROIFrame, cvRect(Car1_X1, Car1_Y1, Car1_X2-Car1_X1, Car1_Y2-Car1_Y1));
				cvMinMaxLoc(Car1_ROIFrame, &Car1_minVal, &Car1_maxVal, &Car1_minLoc, &Car1_maxLoc, NULL);

				if (Car1_maxVal <100)
				{
					cvZero(Car1_ROIFrameBGRPrior);
					Car1_MOVEMENT=0;
				}
				else
				{
					cvSetImageCOI(Car1_ROIFrameBGRPrior, 1);
					if( (Car1_MOVEMENT==0) && (cvCountNonZero(Car1_ROIFrameBGRPrior)==0) )
					{
						cvZero(Car1_ROIFrameBGR);
						Car1_MOVEMENT=1;
						Car1_people++;
						n1=Car1_people;
					}
					cvCircle(Car1_ROIFrameBGR, Car1_maxLoc, 1, CV_RGB(255, 0, 0), 1);
					Car1_ROIFrameBGRPrior = cvCloneImage(Car1_ROIFrameBGR);
				}

				cvRectangle(Car1_imageshow, cvPoint(Car1_X1, Car1_Y1), cvPoint(Car1_X2, Car1_Y2), CV_RGB(255,255,0), 1);

				MultiThrDlg->cvv_src_Image.CopyOf(Car1_imageshow);
				MultiThrDlg->cvv_src_Image.DrawToHDC(MultiThrDlg->hDC_src_image1, &MultiThrDlg->rect_src_image1);
				Car1_NUM.Format("%d",Car1_people);
				MultiThrDlg->GetDlgItem(IDC_EDIT_NUM1)->SetWindowText(Car1_NUM);
				cvReleaseImage(&Car1_imageshow);
				cvReleaseImage(&Car1_ROIFrame);

				Car1_imageCount++;
			}

			//----------------车道2----------------//
			{
				IplImage* Car2_imageshow = cvCloneImage(Car2_tempFrame1);

				cvSmooth(Car2_tempFrame1, Car2_tempFrame1, CV_GAUSSIAN, 7,7);
				cvCvtColor(Car2_tempFrame1, Car2_currentFrame, CV_BGR2GRAY);

				if (Car2_imageCount==0)
					Car2_backgroundFrame = cvCloneImage(Car2_currentFrame);        //获取背景图像

				cvAbsDiff(Car2_currentFrame,Car2_backgroundFrame,Car2_diffFrame);
				IplImage* Car2_ROIFrame = cvCloneImage(Car2_diffFrame);

				cvSetImageROI(Car2_ROIFrame, cvRect(Car2_X1, Car2_Y1, Car2_X2-Car2_X1, Car2_Y2-Car2_Y1));
				cvMinMaxLoc(Car2_ROIFrame, &Car2_minVal, &Car2_maxVal, &Car2_minLoc, &Car2_maxLoc, NULL);

				if (Car2_maxVal <90)
				{
					cvZero(Car2_ROIFrameBGRPrior);
					Car2_MOVEMENT=0;
				}
				else
				{
					cvSetImageCOI(Car2_ROIFrameBGRPrior, 1);
					if( (Car2_MOVEMENT==0) && (cvCountNonZero(Car2_ROIFrameBGRPrior)==0) )
					{
						cvZero(Car2_ROIFrameBGR);
						Car2_MOVEMENT=1;
						Car2_people++;
						n2=Car2_people;
					}
					cvCircle(Car2_ROIFrameBGR, Car2_maxLoc, 1, CV_RGB(255, 0, 0), 1);
					Car2_ROIFrameBGRPrior = cvCloneImage(Car2_ROIFrameBGR);
				}

				cvRectangle(Car2_imageshow, cvPoint(Car2_X1, Car2_Y1), cvPoint(Car2_X2, Car2_Y2), CV_RGB(255,255,0), 1);

				MultiThrDlg->cvv_src_Image.CopyOf(Car2_imageshow);
				MultiThrDlg->cvv_src_Image.DrawToHDC(MultiThrDlg->hDC_src_image2, &MultiThrDlg->rect_src_image2);
				Car2_NUM.Format("%d",Car2_people);
				MultiThrDlg->GetDlgItem(IDC_EDIT_NUM2)->SetWindowText(Car2_NUM);
				cvReleaseImage(&Car2_imageshow);
				cvReleaseImage(&Car2_ROIFrame);

				Car2_imageCount++;
			}

			//----------------车道3----------------//
			{
				IplImage* Car3_imageshow = cvCloneImage(Car3_tempFrame1);

				cvSmooth(Car3_tempFrame1, Car3_tempFrame1, CV_GAUSSIAN, 7,7);
				cvCvtColor(Car3_tempFrame1, Car3_currentFrame, CV_BGR2GRAY);

				if (Car3_imageCount==0)
					Car3_backgroundFrame = cvCloneImage(Car3_currentFrame);        //获取背景图像

				cvAbsDiff(Car3_currentFrame,Car3_backgroundFrame,Car3_diffFrame);
				IplImage* Car3_ROIFrame = cvCloneImage(Car3_diffFrame);

				cvSetImageROI(Car3_ROIFrame, cvRect(Car3_X1, Car3_Y1, Car3_X2-Car3_X1, Car3_Y2-Car3_Y1));
				cvMinMaxLoc(Car3_ROIFrame, &Car3_minVal, &Car3_maxVal, &Car3_minLoc, &Car3_maxLoc, NULL);

				if (Car3_maxVal <thresoldvalue)
				{
					cvZero(Car3_ROIFrameBGRPrior);
					Car3_MOVEMENT=0;
				}
				else
				{
					cvSetImageCOI(Car3_ROIFrameBGRPrior, 1);
					if( (Car3_MOVEMENT==0) && (cvCountNonZero(Car3_ROIFrameBGRPrior)==0) )
					{
						cvZero(Car3_ROIFrameBGR);
						Car3_MOVEMENT=1;
						Car3_people++;
						n3=Car3_people;
					}
					cvCircle(Car3_ROIFrameBGR, Car3_maxLoc, 1, CV_RGB(255, 0, 0), 1);
					Car3_ROIFrameBGRPrior = cvCloneImage(Car3_ROIFrameBGR);
				}

				cvRectangle(Car3_imageshow, cvPoint(Car3_X1, Car3_Y1), cvPoint(Car3_X2, Car3_Y2), CV_RGB(255,255,0), 1);

				MultiThrDlg->cvv_src_Image.CopyOf(Car3_imageshow);
				MultiThrDlg->cvv_src_Image.DrawToHDC(MultiThrDlg->hDC_src_image3, &MultiThrDlg->rect_src_image3);
				Car3_NUM.Format("%d",Car3_people);
				MultiThrDlg->GetDlgItem(IDC_EDIT_NUM3)->SetWindowText(Car3_NUM);
				cvReleaseImage(&Car3_imageshow);
				cvReleaseImage(&Car3_ROIFrame);

				Car3_imageCount++;
			}

			//----------------车道4----------------//
			{
				IplImage* Car4_imageshow = cvCloneImage(Car4_tempFrame1);

				cvSmooth(Car4_tempFrame1, Car4_tempFrame1, CV_GAUSSIAN, 7,7);
				cvCvtColor(Car4_tempFrame1, Car4_currentFrame, CV_BGR2GRAY);

				if (Car4_imageCount==0)
					Car4_backgroundFrame = cvCloneImage(Car1_backgroundFrame);        //获取背景图像
// 					Car4_backgroundFrame = cvCloneImage(Car4_currentFrame);        //获取背景图像

				cvAbsDiff(Car4_currentFrame,Car4_backgroundFrame,Car4_diffFrame);
				IplImage* Car4_ROIFrame = cvCloneImage(Car4_diffFrame);

				cvSetImageROI(Car4_ROIFrame, cvRect(Car4_X1, Car4_Y1, Car4_X2-Car4_X1, Car4_Y2-Car4_Y1));
				cvMinMaxLoc(Car4_ROIFrame, &Car4_minVal, &Car4_maxVal, &Car4_minLoc, &Car4_maxLoc, NULL);

				if (Car4_maxVal <thresoldvalue)
				{
					cvZero(Car4_ROIFrameBGRPrior);
					Car4_MOVEMENT=0;
				}
				else
				{
					cvSetImageCOI(Car4_ROIFrameBGRPrior, 1);
					if( (Car4_MOVEMENT==0) && (cvCountNonZero(Car4_ROIFrameBGRPrior)==0) )
					{
						cvZero(Car4_ROIFrameBGR);
						Car4_MOVEMENT=1;
						Car4_people++;
						n4=Car4_people;
					}
					cvCircle(Car4_ROIFrameBGR, Car4_maxLoc, 1, CV_RGB(455, 0, 0), 1);
					Car4_ROIFrameBGRPrior = cvCloneImage(Car4_ROIFrameBGR);
				}

				cvRectangle(Car4_imageshow, cvPoint(Car4_X1, Car4_Y1), cvPoint(Car4_X2, Car4_Y2), CV_RGB(455,455,0), 1);

				MultiThrDlg->cvv_src_Image.CopyOf(Car4_imageshow);
				MultiThrDlg->cvv_src_Image.DrawToHDC(MultiThrDlg->hDC_src_image4, &MultiThrDlg->rect_src_image4);
				Car4_NUM.Format("%d",Car4_people);
				MultiThrDlg->GetDlgItem(IDC_EDIT_NUM4)->SetWindowText(Car4_NUM);
				cvReleaseImage(&Car4_imageshow);
				cvReleaseImage(&Car4_ROIFrame);

				Car4_imageCount++;
			}
 		}
		else
		{
			cvReleaseCapture(&MultiThrDlg->VideoFile1);
			cvReleaseCapture(&MultiThrDlg->VideoFile2);
			cvReleaseCapture(&MultiThrDlg->VideoFile3);
			cvReleaseCapture(&MultiThrDlg->VideoFile4);
			break;
		}
		fileWrite=Car1_NUM +"\r\n"+Car2_NUM  +"\r\n"+Car3_NUM +"\r\n"+Car4_NUM;
		CFile file("file.txt",CFile::modeCreate|CFile::modeWrite);
		file.Write(fileWrite,strlen(fileWrite));
		file.Close();
	}

	
	return 0;
}
void CCarStreamTestDlg::OnBnClickedCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	VideoFile1 = cvCaptureFromFile("车道1.avi");
	VideoFile2 = cvCaptureFromFile("车道2.avi");
	VideoFile3 = cvCaptureFromFile("车道3.avi");
	VideoFile4 = cvCaptureFromFile("车道4.avi");
	if (VideoFile1&&
		VideoFile2&&
		VideoFile3&&
		VideoFile4)
		m_pThread = AfxBeginThread(ImgAcqRunCQ,this,0,0,0,NULL);
	else
		MessageBox("读取文件失败！");
}

void CCarStreamTestDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pThread->SuspendThread();
}

void CCarStreamTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
