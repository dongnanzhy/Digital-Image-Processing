; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDIP_FinalView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DIP_Final.h"
LastPage=0

ClassCount=10
Class1=CDIP_FinalApp
Class2=CDIP_FinalDoc
Class3=CDIP_FinalView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDD_DIALOG1
Class6=CLinerTrans
Resource3=IDR_MAINFRAME
Class7=CHgdlg
Resource4=IDD_DIALOG3
Class8=Csuofang
Resource5=IDD_DIALOG2
Class9=Cxuan
Resource6=IDD_DIALOG4
Class10=Cpingyi
Resource7=IDD_DIALOG5

[CLS:CDIP_FinalApp]
Type=0
HeaderFile=DIP_Final.h
ImplementationFile=DIP_Final.cpp
Filter=N

[CLS:CDIP_FinalDoc]
Type=0
HeaderFile=DIP_FinalDoc.h
ImplementationFile=DIP_FinalDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CDIP_FinalView]
Type=0
HeaderFile=DIP_FinalView.h
ImplementationFile=DIP_FinalView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_Pingyi


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_RegionGrow




[CLS:CAboutDlg]
Type=0
HeaderFile=DIP_Final.cpp
ImplementationFile=DIP_Final.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=ID_Invert
Command18=ID_Liner
Command19=ID_Weicai
Command20=ID_Colortogrey
Command21=ID_Hgdlg
Command22=ID_Histoave
Command23=ID_Peppernoise
Command24=ID_Randomnoise
Command25=ID_Gradsharp
Command26=ID_Lapchange
Command27=ID_Midchange
Command28=ID_Pinghua
Command29=ID_Suofang
Command30=ID_Xuanzhuan
Command31=ID_Pingyi
Command32=ID_Mirror
Command33=ID_Mirror2
Command34=ID_Erzhi
Command35=ID_Fushi
Command36=ID_Pengzhang
Command37=ID_Tiqu
Command38=ID_TiquLap
Command39=ID_TiquSobel
Command40=ID_Tiqu2
Command41=ID_Jiabianjie
Command42=ID_RegionGrow
CommandCount=42

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG1]
Type=1
Class=CLinerTrans
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_EDIT3,edit,1350631552
Control10=IDC_EDIT4,edit,1350631552

[CLS:CLinerTrans]
Type=0
HeaderFile=LinerTrans.h
ImplementationFile=LinerTrans.cpp
BaseClass=CDialog
Filter=D
LastObject=CLinerTrans
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=CHgdlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_Histogram,static,1342177287

[CLS:CHgdlg]
Type=0
HeaderFile=Hgdlg.h
ImplementationFile=Hgdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CHgdlg
VirtualFilter=dWC

[DLG:IDD_DIALOG3]
Type=1
Class=Csuofang
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_RADIO1,button,1342308361
Control8=IDC_RADIO2,button,1342177289
Control9=IDC_STATIC,button,1342308359

[CLS:Csuofang]
Type=0
HeaderFile=suofang1.h
ImplementationFile=suofang1.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO1
VirtualFilter=dWC

[DLG:IDD_DIALOG4]
Type=1
Class=Cxuan
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342308359
Control4=IDC_RADIO1,button,1342308361
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350631552

[CLS:Cxuan]
Type=0
HeaderFile=xuan.h
ImplementationFile=xuan.cpp
BaseClass=CDialog
Filter=D
LastObject=Cxuan
VirtualFilter=dWC

[DLG:IDD_DIALOG5]
Type=1
Class=Cpingyi
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1350631552

[CLS:Cpingyi]
Type=0
HeaderFile=pingyi.h
ImplementationFile=pingyi.cpp
BaseClass=CDialog
Filter=D
LastObject=Cpingyi
VirtualFilter=dWC

