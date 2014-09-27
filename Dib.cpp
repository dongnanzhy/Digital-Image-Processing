// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DIP_Final.h"
#include "Dib.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/***********************************************************************
* 函数名称：
* CDib()
*说明：无参数的构造函数，对成员变量进行初始化
***********************************************************************/
CDib::CDib()
{
	m_pDib=NULL;
    m_pDibout=NULL;
	m_pDibback=NULL;
	m_rtPosSour.SetRectEmpty();
	m_rtPosDest.SetRectEmpty();
}
/***********************************************************************
* 函数名称：
* ~CDib()
*说明：无参数的析构函数，对成员变量进行析构
***********************************************************************/
CDib::~CDib()
{
	if (m_pDib!=NULL)
	{
		delete []m_pDib;
	}
	if (m_pDibout!=NULL)
	{
		delete []m_pDibout;
	}
	if (m_pDibback!=NULL)
	{
		delete []m_pDibback;
	}
}

/***********************************************************************
* 函数名称：
* LoadFile()
*说明：参数为打开图像的文件名，读入文件进内存
***********************************************************************/
bool CDib::LoadFile( const char *FileName )
{
	CFile File;
	File.Open(FileName,CFile::modeRead|CFile::shareDenyRead,NULL);
	DWORD dwDibSize=File.GetLength()-sizeof(BITMAPFILEHEADER);
	File.Read(&BFH,sizeof(BITMAPFILEHEADER));
	if (BFH.bfType!='MB')
	{
		AfxMessageBox("This file is not a BMP",MB_OK);
		return false;
	}
	m_pDib=new unsigned char[dwDibSize];
	m_pDibout=new unsigned char[dwDibSize];
	m_pDibback=new unsigned char[dwDibSize];
	File.Read(m_pDib,dwDibSize);
	m_pBIH=(BITMAPINFOHEADER *)m_pDib;
	
	
	m_Width = ((m_pBIH->biWidth * m_pBIH->biBitCount)+31)/32*4;
	pixelbyte=m_pBIH->biBitCount/8;
	wide=m_pBIH->biWidth;
	m_Height=m_pBIH->biHeight;
	m_Widthout=m_Width;
	m_Heightout=m_Height;
	
	m_rtPosSour.SetRect(CPoint(0,0),CPoint(wide,m_Height));
	m_rtPosDest = m_rtPosSour;
	
	
	if (m_pBIH->biBitCount>8)
	{
		PaletteEntries=0;
	} 
	else
	{
		PaletteEntries=256;
	}
	m_pDibBits=m_pDib+sizeof(BITMAPINFOHEADER)+PaletteEntries*sizeof(RGBQUAD);
	m_pDibBitsout=m_pDibout+sizeof(BITMAPINFOHEADER)+PaletteEntries*sizeof(RGBQUAD);
	m_pDibBitsback=m_pDibback+sizeof(BITMAPINFOHEADER)+PaletteEntries*sizeof(RGBQUAD);
	
	m_pPalette = (RGBQUAD*) (m_pDib + sizeof(BITMAPINFOHEADER));
	
	memcpy(m_pDibBitsback,m_pDibBits,m_Height*m_Width);
	return true;
}
/***********************************************************************
* 函数名称：
* SaveFile()
*说明：保存图像
***********************************************************************/
bool CDib::SaveFile( const char* pFileName )
{
	if (m_pDib ==NULL) 
	{
		AfxMessageBox("This isn't a BMP File!",MB_OK);
		return false;
	}
	
	CFile file(pFileName, CFile::modeCreate|CFile::modeWrite);
	file.Write(&BFH,sizeof(BITMAPFILEHEADER));
	file.Write(m_pDib,m_Width*m_Height+PaletteEntries*sizeof(RGBQUAD)+sizeof(BITMAPINFOHEADER));
	
	file.Close();
	
	return true;
}
/***********************************************************************
* 函数名称：
* Draw()
*说明：参数为pDC，用来显示图像
***********************************************************************/
void CDib::Draw( CDC *pDC )
{
	if (m_pDib==NULL)
	{
		return;
	} 
	else
	{
		StretchDIBits(pDC->m_hDC,m_rtPosDest.left,m_rtPosDest.top,m_rtPosDest.Width(),m_rtPosDest.Height(),m_rtPosSour.left,m_rtPosSour.top,m_rtPosSour.Width(),m_rtPosSour.Height(),m_pDibBits,(BITMAPINFO *)m_pBIH,DIB_RGB_COLORS,SRCCOPY);
		/*StretchDIBits(pDC->m_hDC,0,0,wide,m_Height,0,0,wide,m_Height,m_pDibBits,(BITMAPINFO *)m_pBIH,BI_RGB,SRCCOPY);*/
	}
}
/***********************************************************************
* 函数名称：
* Invert()
*说明：对像素值求反做负片
***********************************************************************/
void CDib::Invert()
{
	for (int i=0;i<m_Height;i++)
	{
		for (int j=0;j<m_Width;j++)
		{
			*(m_pDibBits+i*m_Width+j)=255-*(m_pDibBits+i*m_Width+j);
		}
	}
}
/***********************************************************************
* 函数名称：
* Liner()
*说明：参数为原图的低灰度值、变换后的低灰度值、原图的高灰度值、变换后的高灰度值，对像素值做线性变换
***********************************************************************/
void CDib::Liner( int X1,int Y1,int X2,int Y2 )
{
	double nSlope;
	nSlope = 0.0 + (Y2-Y1)/(X2-X1);
	for(int i=0; i< m_Height; i++)
	{
		for(int j=0; j< m_Width; j++)
		{
			if ((*(m_pDibBits+i*m_Width+j) <= X2 ) &&(*(m_pDibBits+i*m_Width+j) >=X1))
			{
				*(m_pDibBits+i*m_Width+j) =(BYTE) (nSlope * (*(m_pDibBits+i*m_Width+j) -X1)); 
			} 
			else if((*(m_pDibBits+i*m_Width+j) < X2 ) &&(*(m_pDibBits+i*m_Width+j) <X1))
			{
				*(m_pDibBits+i*m_Width+j) =0; 
			}
			else
			{
				*(m_pDibBits+i*m_Width+j) =255; 
			}
		}
	}
}
/***********************************************************************
* 函数名称：
* GetGreyCountNumber()
*说明：无参数，返回值为每个像素值的点的个数
***********************************************************************/
long* CDib::GetGreyCountNumber()
{
	long * pData=new long [256];
	memset(pData,0,256*sizeof(long));
	for (int i=0;i<m_Height;i++)
	{
		for (int j=0;j<wide;j+=3)
		{
			pData[(*(m_pDibBits+i*wide+j)+*(m_pDibBits+i*wide+j+1)+*(m_pDibBits+i*wide+j+2))/3]++;
		}
	}
	return pData;
}
/***********************************************************************
* 函数名称：
* GetPaletteEntries()
*说明：无参数，返回值为实际用到的颜色数，灰度图像为256，彩色图像为0（直方图中仍用256）
***********************************************************************/
long CDib::GetPaletteEntries()
{
	return 256;
}
/***********************************************************************
* 函数名称：
* Histave()
*说明：无参数，对图像进行直方图均衡
***********************************************************************/
void CDib::Histave()
{
	int s,i,j,hist;
	double map[256];
	int sum,tmp;
	sum=0;
	hist=0;
	
	for (s=0;s<256;s++)
	{
		for (i=0;i<m_Height;i++)
		{
			for (j=0;j<m_Width;j++)
			{
				if (*(m_pDibBits+i*m_Width+j)==s)
				{
					hist++;
				}
			}
		}
		sum=hist+sum;
		map[s]=(double)sum*255/(m_Height*m_Width)+0.5;
		hist=0;
	}
	
	for (i=0;i<m_Height;i++)
	{
		for (j=0;j<m_Width;j++)
		{
			tmp=*(m_pDibBits+i*m_Width+j);
			*(m_pDibBits+i*m_Width+j)=(int)map[tmp];
		}
	}
}
/***********************************************************************
* 函数名称：
* PseuColor()
*说明：伪彩实现
***********************************************************************/
void CDib::PseuColor()
{	
	LPBYTE m_Palette2;						//建立调色板
	m_Palette2=new BYTE[256*4];	
	m_Palette2=(LPBYTE)m_pBIH+40;				//指向调色板首位
	for(int i=0;i<256;i++){
		if (i<50)
		{
			*(m_Palette2+i*4)=50-i;				//b
			*(m_Palette2+i*4+1)=255-i;			//g
			*(m_Palette2+i*4+2)=i;				//r
	    	*(m_Palette2+i*4+3)=i;
		}else if(i>200)
		{
			*(m_Palette2+i*4)=255-0.8*i;			//b	
			*(m_Palette2+i*4+1)=255-i;		        //g
			*(m_Palette2+i*4+2)=i;			        //r
	    	*(m_Palette2+i*4+3)=i;
		}else
		{
			*(m_Palette2+i*4)=i;				//B
			*(m_Palette2+i*4+1)=i;				//G
			*(m_Palette2+i*4+2)=i;				//R
	    	*(m_Palette2+i*4+3)=i;
		}
	
	}
}
/***********************************************************************
* 函数名称：
* Colortogrey()
*说明：将彩色图像变为灰度图像显示（不改变调色板）
***********************************************************************/
void CDib::Colortogrey()
{
	int i,j,k;	
	//灰度变换
	for(i=0;i<m_Height;i++)
		for(j=0;j<wide;j++)
		{
			BYTE b=*(m_pDibBits+i*m_Width+j*pixelbyte);
			BYTE g=*(m_pDibBits+i*m_Width+j*pixelbyte+1);
			BYTE r=*(m_pDibBits+i*m_Width+j*pixelbyte+2);
			BYTE value =(BYTE)(0.299 * r   +   0.587 * g   +   0.114 * b);
			
			for(k=0;k<pixelbyte;k++)
			{
				*(m_pDibBits+i*m_Width+j*pixelbyte+k)=value;
			}
		}
}
/***********************************************************************
* 函数名称：
* AddPepperSaltNoise()
*说明：无参数，加入椒盐噪声
***********************************************************************/
void CDib::AddPepperSaltNoise()
{
	memcpy (m_pDibBitsout , m_pDibBits , m_Width * m_Height);
	int bytecount,i;
	bytecount = m_Width*m_Height; //获取位图数据区的字节数

	if (PaletteEntries!=0)      //处理灰度图像
	{  
        for (i=0;i<bytecount;i++)
        {
			if(rand()>32000)  m_pDibBitsout[i]=0;
			if(rand()<200)    m_pDibBitsout[i]=255;
        }
	}
	else	                 //24位真彩色图像
	{
        for (i=0;i<bytecount;i=i+3)
        {
			int num=rand();
            if (num>32000) 
			{
				m_pDibBitsout[i]=(rand())%255;        //处理每一个像素的RGB值
				m_pDibBitsout[i+1]=(rand())%255;
				m_pDibBitsout[i+2]=(rand())%255;
			}
			if (num<200) 
			{
				m_pDibBitsout[i]=(rand())%255;
				m_pDibBitsout[i+1]=(rand())%255;
				m_pDibBitsout[i+2]=(rand())%255;
			}
        }
	}
	//生成新的DIB位图
	for(i=0;i<m_Height;i++)
	{
		for(int j=0;j<m_Width;j++)
			*(m_pDibBits+i*m_Width+j)= *(m_pDibBitsout+i*m_Width+j);
	}
}
/***********************************************************************
* 函数名称：
* AddRandomNoise()
*说明：无参数，加入随机噪声
***********************************************************************/
void CDib::AddRandomNoise()
{
	memcpy (m_pDibBitsout , m_pDibBits , m_Width * m_Height);
	int bytecount,i;
	bytecount = m_Width*m_Height; //获取位图数据区的字节数
    for( i=0;i<bytecount;i++)
	{
		LONG Temp=rand();
		Temp = m_pDibBitsout[i]*224/256+Temp/512;
		m_pDibBitsout[i] = Temp >= 255 ? 255 : Temp;
    }
	//生成新的DIB位图
	for(i=0;i<m_Height;i++)
	{
		for(int j=0;j<m_Width;j++)
			*(m_pDibBits+i*m_Width+j)= *(m_pDibBitsout+i*m_Width+j);
	}
}
/***********************************************************************
* 函数名称：
* Lapchange()
*说明：无参数，对图像进行拉普拉斯锐化
***********************************************************************/
void CDib::Lapchange()
{
	memcpy(m_pDibBitsout,m_pDibBits,m_Width*m_Height);	
	int pr,pg,pb;     //B G R三通道
	for(int i=1;i<m_Height-1;i++)
		for(int j=1;j<wide-1;j++)
		{
			//    3*3模板
			pb=5*m_pDibBits[i*m_Width+j*pixelbyte]-m_pDibBits[i*m_Width+(j-1)*pixelbyte]-m_pDibBits[i*m_Width+(j+1)*pixelbyte]-m_pDibBits[(i-1)*m_Width+j*pixelbyte]-m_pDibBits[(i+1)*m_Width+j*pixelbyte];
			pg=5*m_pDibBits[i*m_Width+j*pixelbyte+1]-m_pDibBits[i*m_Width+(j-1)*pixelbyte+1]-m_pDibBits[i*m_Width+(j+1)*pixelbyte+1]-m_pDibBits[(i-1)*m_Width+j*pixelbyte+1]-m_pDibBits[(i+1)*m_Width+j*pixelbyte+1];	
			pr=5*m_pDibBits[i*m_Width+j*pixelbyte+2]-m_pDibBits[i*m_Width+(j-1)*pixelbyte+2]-m_pDibBits[i*m_Width+(j+1)*pixelbyte+2]-m_pDibBits[(i-1)*m_Width+j*pixelbyte+2]-m_pDibBits[(i+1)*m_Width+j*pixelbyte+2];
			
			if(pb<0)m_pDibBitsout[i*m_Width+j*pixelbyte]=0;
			else  if(pb>255)m_pDibBitsout[i*m_Width+j*pixelbyte]=255;
			else m_pDibBitsout[i*m_Width+j*pixelbyte]=pb;
			
			
			if(pg<0)m_pDibBitsout[i*m_Width+j*pixelbyte+1]=0;
			else if(pg>255)m_pDibBitsout[i*m_Width+j*pixelbyte+1]=255;
			else m_pDibBitsout[i*m_Width+j*pixelbyte+1]=pg;
			
			if(pr<0)m_pDibBitsout[i*m_Width+j*pixelbyte+2]=0;
			else if(pr>255)m_pDibBitsout[i*m_Width+j*pixelbyte+2]=255;
			else m_pDibBitsout[i*m_Width+j*pixelbyte+2]=pr;
		}
	memcpy(m_pDibBits,m_pDibBitsout,m_Width*m_Height);
}
/***********************************************************************
* 函数名称：
* GarSharp()
*说明：无参数，对图像进行梯度锐化
***********************************************************************/
void CDib::GradSharp()
{
	memcpy (m_pDibBitsout , m_pDibBits , m_Width * m_Height);
	unsigned char bThre=30;
	unsigned char*	pSrc;       // 指向源图像的指针
	unsigned char*	pDst; 	
	unsigned char*	pSrc1;
	unsigned char*	pSrc2;	
	LONG	i,j;				// 循环变量
	int	bTemp;
	int m_nBitCount=m_pBIH->biBitCount;
	if(m_nBitCount != 8)
	{
		AfxMessageBox("只能处理8位灰度图像!");
		return ;
	}
	//创建要复制的图像区域
	
	for(i = 0; i < m_Height; i++)		// 每行
	{		
		for(j = 0; j < m_Width; j++)		// 每列
		{
			//指向新DIB第i行第j列的像素的指针
			pDst = m_pDibBits + m_Width * (m_Height -1 - i) + j;
			
			// 进行梯度运算
			// 指向DIB第i行，第j个象素的指针
			pSrc  = (unsigned char*)m_pDibBitsout + m_Width * (m_Height - 1 - i) + j;			
			// 指向DIB第i+1行，第j个象素的指针
			pSrc1 = (unsigned char*)m_pDibBitsout + m_Width * (m_Height - 2 - i) + j;			
			// 指向DIB第i行，第j+1个象素的指针
			pSrc2 = (unsigned char*)m_pDibBitsout + m_Width * (m_Height - 1 - i) 
				+ j + 1;
			
			bTemp = abs((*pSrc)-(*pSrc1)) + abs((*pSrc)-(*pSrc2));
			
			// 判断是否小于阈值
			if ((bTemp+120) < 255)
			{
				// 判断是否大于阈值，对于小于情况，灰度值不变。
				if (bTemp >= bThre)
				{
					*pSrc = bTemp + 120;
				}
			}
			else
			{
				*pSrc = 255;
			}
			//生成新的DIB像素值
			*pDst = *pSrc;
		}
	}
}
/***********************************************************************
* 函数名称：
* Midchange()
*说明：无参数，对图像中值滤波
***********************************************************************/
void CDib::Midchange()
{
	memcpy (m_pDibBitsout , m_pDibBits , m_Width * m_Height);
	int middle_temp[9],midp;
	int i,j;
	int xx, yy, m;
	int chg,medi;
	for (i = 1; i < m_Height; i++)//行
	{
		for(j = 1; j < wide; j++)//列
		{
			for (int k=0;k<pixelbyte;k++)
			{
				m=0;
				for(xx= i-1; xx<= i+1; xx++)
					for(yy=j-1; yy<=j+1; yy++)
					{
						middle_temp[m]=m_pDibBits [xx*m_Width+yy*pixelbyte+k];
						m++;
					}//核
					do{
						chg=0;
						for(m=0 ; m<8 ;m++)
						{
							if(middle_temp[m]<middle_temp[m+1])
							{
								midp=middle_temp[m];
								middle_temp[m]=middle_temp[m+1];
								middle_temp[m+1]=midp;
								chg=1;
							}
						}
					}while(chg==1);
					medi = middle_temp[4];
				*(m_pDibBitsout+i*m_Width+j*pixelbyte+k)=medi;
			}		
		}
	}
	memcpy(m_pDibBits ,m_pDibBitsout,m_Width*m_Height);
}
/***********************************************************************
* 函数名称：
* Pinghua()
*说明：无参数，对图像平滑滤波
***********************************************************************/
void CDib::Pinghua()
{
	memcpy (m_pDibBitsout , m_pDibBits , m_Width* m_Height);
	int i,j,m,n;
	long temp;
	for (i=1;i<m_Height-1;i++)
	{
		for (j=1;j<wide-1;j++)
		{
			for (int k=0;k<pixelbyte;k++)
			{
				temp=0;
				for (m=-1;m<=1;m++)
				{
					for (n=-1;n<=1;n++)
					{
						temp=temp+*(m_pDibBits+(i+m)*m_Width+(j+n)*pixelbyte+k);
					}
				}
				temp=temp/9;
		    	*(m_pDibBitsout+i*m_Width+j*pixelbyte+k)=temp;
			}
		}
	}
	
	memcpy(m_pDibBits,m_pDibBitsout,m_Width*m_Height);
}
/***********************************************************************
* 函数名称：
* Pingyi()
*说明：参数为X轴偏移量和Y轴偏移量，对图像平移
***********************************************************************/
void CDib::Pingyi( int offsetX,int offsetY )
{
	memcpy(m_pDibBitsout,m_pDibBits,m_Height*m_Width);
	memset(m_pDibBits,255,m_Height*m_Width);
	if (PaletteEntries!=0)
	{
		for (int i=0;i<m_Heightout;i++)
		{
			for (int j=0;j<m_Widthout;j++)
			{
				if (i-offsetY>=0&&i-offsetY<m_Heightout&&j-offsetX>=0&&j-offsetX<m_Widthout)
				{
					*(m_pDibBits+i*m_Width+j)=*(m_pDibBitsout+(i-offsetY)*m_Widthout+(j-offsetX));
				}
				
			}
		}
	} 
	else
	{
		for (int i=0;i<m_Heightout;i++)
		{
			for (int j=0;j<wide;j++)
			{
				for (int k=0;k<3;k++)
				{
					if (i-offsetY>=0&&i-offsetY<m_Heightout&&j-offsetX>=0&&j-offsetX<wide)
					{
						*(m_pDibBits+i*m_Width+j*3+k)=*(m_pDibBitsout+(i-offsetY)*m_Widthout+(j-offsetX)*3+k);
					}
				}
			}
		}
	}
}
/***********************************************************************
* 函数名称：
* Xuanzhuan()
*说明：参数为选择角度，采用邻近插值的方法旋转图像
***********************************************************************/
bool CDib::Xuanzhuan( int angle )
{
	int newwidth,newheight;
	unsigned char *lp;
	unsigned char *lpsrc,*lpdst;
	BITMAPINFOHEADER *lpinfor;
	double arcangle;
	float fsin,fcos;
	int linebytes,OldLineBytes;
	float num1,num2;
	
	int i, j, i0, j0;
	float SrcX1,SrcY1,SrcX2,SrcY2,SrcX3,SrcY3,SrcX4,SrcY4;
	float DstX1,DstY1,DstX2,DstY2,DstX3,DstY3,DstX4,DstY4;
	
	SrcX1 = (float)(-(wide-1)/2);
	SrcY1 = (float)((m_Height-1)/2);
	SrcX2 = (float)((wide-1)/2);
	SrcY2 = (float)((m_Height-1)/2);
	SrcX3 = (float)(-(wide-1)/2);
	SrcY3 = (float)(-(m_Height-1)/2);
	SrcX4 = (float)((wide-1)/2);
	SrcY4 = (float)(-(m_Height-1)/2);
	
	arcangle=(angle*3.14)/180.0;
	fsin = (float) sin(arcangle);
	fcos = (float) cos(arcangle);
	
	DstX1 = fcos * SrcX1 + fsin * SrcY1;
	DstY1 = - fsin * SrcX1 + fcos * SrcY1;
	DstX2 = fcos * SrcX2 + fsin * SrcY2;
	DstY2 = - fsin * SrcX2 + fcos * SrcY2;
	DstX3 = fcos * SrcX3 + fsin * SrcY3;
	DstY3 = - fsin * SrcX3 + fcos * SrcY3;
	DstX4 = fcos * SrcX4 + fsin * SrcY4;
	DstY4 = - fsin * SrcX4 + fcos * SrcY4;
	
	newwidth = (int) (max(fabs(DstX4-DstX1) , fabs(DstX3-DstX2) ) + 0.5);
	newheight = (int) (max(fabs(DstY4-DstY1) , fabs(DstY3-DstY2) ) + 0.5);
	
	m_rtPosDest.SetRect(CPoint(0,0),CPoint(newwidth,newheight));
	m_rtPosSour = m_rtPosDest;
	
	
	num1=(float)(-0.5* newwidth *fcos -0.5 * newheight *fsin + 0.5 * wide);
	num2=(float)(0.5* newwidth *fsin -0.5 * newheight *fcos + 0.5 * m_Height);
	
	linebytes = (newwidth*8*pixelbyte+31)/32*4;
	OldLineBytes = (wide*8*pixelbyte+31)/32*4;
	
	unsigned char *lpDib = new unsigned char [linebytes*newheight+sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD)];
	if (lpDib == NULL){
		return(FALSE);}
	memcpy(lpDib,m_pDib,sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD));
	
	lpinfor = (BITMAPINFOHEADER*) lpDib;
	lpinfor->biWidth= newwidth;
	lpinfor->biHeight= newheight;
	
	lp = lpDib+sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD);
	if (lp==NULL){
		return (FALSE);}
	lp = new unsigned char [linebytes*newheight];
	memset(lp , (BYTE)255 , linebytes*newheight);
	for (i = 0; i < newheight; i++)
	{
		for (j = 0; j < newwidth; j++)
		{
			for(int k=0;k<pixelbyte;k++)
			{
				lpdst=(unsigned char*)lp+(newheight-1-i)*linebytes+j*pixelbyte+k;
				i0=(long)(((float)i)*fcos-1.0f*((float) j)*fsin+num2+0.5);
				j0=(long)(((float)i)*fsin+((float) j)*fcos+num1+0.5);
				if((i0>=0)&&(i0<wide)&&(j0>=0)&&(j0<m_Height))
				{
					lpsrc=(unsigned char*)m_pDibBits+OldLineBytes*(m_Height-1-i0)+j0*pixelbyte+k;
					*lpdst=*lpsrc;
				}
			}
		}
	}
	
	delete []m_pDib;
	m_pDib = lpDib;
	m_pDibBits = lp;
	m_pBIH = lpinfor;
	m_pBIH->biSizeImage = linebytes* newheight;
	wide = lpinfor->biWidth;
	m_Width=linebytes;
	m_Height = lpinfor->biHeight;
	return TRUE;
}
/***********************************************************************
* 函数名称：
* Xuanzhuan2()
*说明：参数为旋转角度，采用双线性插值方法旋转图像
***********************************************************************/
bool CDib::Xuanzhuan2( int angle )
{
		int newwidth,newheight;
	unsigned char *lp;
	BITMAPINFOHEADER *lpinfor;
	double arcangle;
	float fsin,fcos;
	int linebytes,OldLineBytes;
	float num1,num2;
	unsigned char array[2][2];
	
	int i, j;
	float SrcX1,SrcY1,SrcX2,SrcY2,SrcX3,SrcY3,SrcX4,SrcY4;
	float DstX1,DstY1,DstX2,DstY2,DstX3,DstY3,DstX4,DstY4;
	
	SrcX1 = (float)(-(wide-1)/2);
	SrcY1 = (float)((m_Height-1)/2);
	SrcX2 = (float)((wide-1)/2);
	SrcY2 = (float)((m_Height-1)/2);
	SrcX3 = (float)(-(wide-1)/2);
	SrcY3 = (float)(-(m_Height-1)/2);
	SrcX4 = (float)((wide-1)/2);
	SrcY4 = (float)(-(m_Height-1)/2);
	
	arcangle=(angle*3.14)/180.0;
	fsin = (float) sin(arcangle);
	fcos = (float) cos(arcangle);
	
	DstX1 = fcos * SrcX1 + fsin * SrcY1;
	DstY1 = - fsin * SrcX1 + fcos * SrcY1;
	DstX2 = fcos * SrcX2 + fsin * SrcY2;
	DstY2 = - fsin * SrcX2 + fcos * SrcY2;
	DstX3 = fcos * SrcX3 + fsin * SrcY3;
	DstY3 = - fsin * SrcX3 + fcos * SrcY3;
	DstX4 = fcos * SrcX4 + fsin * SrcY4;
	DstY4 = - fsin * SrcX4 + fcos * SrcY4;
	
	newwidth = (int) (max(fabs(DstX4-DstX1) , fabs(DstX3-DstX2) ) + 0.5);
	newheight = (int) (max(fabs(DstY4-DstY1) , fabs(DstY3-DstY2) ) + 0.5);
	
	m_rtPosDest.SetRect(CPoint(0,0),CPoint(newwidth,newheight));
	m_rtPosSour = m_rtPosDest;
	
	
	//num1=(float)(-0.5* newwidth *fcos -0.5 * newheight *fsin + 0.5 * wide);
	//num2=(float)(0.5* newwidth *fsin -0.5 * newheight *fcos + 0.5 * m_Height);

	num1 = (float) (-0.5 * (newwidth - 1) * fcos 
		+ 0.5 * (newheight - 1) * fsin + 0.5 * (wide  - 1));
	num2 = (float) (-0.5 * (newwidth - 1) * fsin
		                - 0.5 * (newheight - 1) * fcos + 0.5 * (m_Height - 1));
	
	linebytes = (newwidth*8*pixelbyte+31)/32*4;
	OldLineBytes = (wide*8*pixelbyte+31)/32*4;
	
	unsigned char *lpDib = new unsigned char [linebytes*newheight+sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD)];
	if (lpDib == NULL){
		return(FALSE);}
	memcpy(lpDib,m_pDib,sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD));
	
	lpinfor = (BITMAPINFOHEADER*) lpDib;
	lpinfor->biWidth= newwidth;
	lpinfor->biHeight= newheight;
	
	lp = lpDib+sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD);
	if (lp==NULL){
		return (FALSE);}
	lp = new unsigned char [linebytes*newheight];
	memset(lp , (BYTE)255 , linebytes*newheight);

    for(i = 0; i < newheight; i++)
	{
		for(j = 0; j < newwidth; j++)
		{		
			// 输出图像像素(j,i)映射到输入图像的坐标
			float coordinateX = j * fcos - i * fsin + num1;
			float coordinateY = j * fsin + i * fcos + num2;

			//对坐标取整
			int Iu=(int)coordinateX;
			int Iv=(int)coordinateY;

			// 判断是否在原图范围内
			if( (coordinateX >= 0) && (coordinateX < wide-1) && (coordinateY >= 0) 
				&& (coordinateY < m_Height-1))
			{
				//将图像每个通道的数据进行分别插值，彩色图像pixelByte为3，
				//灰度图像pixelByte为1
				for(int k=0;k<pixelbyte;k++){
					//将当前处理像素周围2*2邻域像素拷贝至数组array
					array[0][0]=*(m_pDibBits+ Iv*OldLineBytes+ Iu*pixelbyte+k);
					array[0][1]=*(m_pDibBits+ Iv*OldLineBytes+ (Iu+1)*pixelbyte+k);
					array[1][0]=*(m_pDibBits+ (Iv+1)*OldLineBytes+ Iu*pixelbyte+k);
					array[1][1]=*(m_pDibBits+ (Iv+1)*OldLineBytes+ (Iu+1)*pixelbyte+k);
					*(lp + i * linebytes + j*pixelbyte+k)
						=interpolationDblLinear(array, coordinateX-Iu, coordinateY-Iv);
				}
			}
			else
			{
				// 对于不在原图范围内的像象素，赋值为255
				for(int k=0;k<pixelbyte;k++)
					*(lp+i*linebytes+j*pixelbyte+k) = 255;
			}
			
		}
		
	}
	
	delete []m_pDib;
	m_pDib = lpDib;
	m_pDibBits = lp;
	m_pBIH = lpinfor;
	m_pBIH->biSizeImage = linebytes* newheight;
	wide = lpinfor->biWidth;
	m_Width=linebytes;
	m_Height = lpinfor->biHeight;
	return TRUE;
}
/***********************************************************************
* 函数名称：
* Suoxiao()
*说明：参数为X轴缩放倍数和Y轴缩放倍数，采用邻近插值方法缩放图像
***********************************************************************/
bool CDib::Suoxiao( float xratio,float yratio )
{
	m_rtPosDest.SetRect(CPoint(0,0),CPoint(m_Width*xratio,m_Height*yratio));
	m_rtPosSour = m_rtPosDest;
	
	long newwidth = (LONG) (wide * xratio +0.5);
	long newheight = (LONG) (m_Height * yratio+0.5);
	long linebytes = (newwidth*8*pixelbyte+31)/32*4;
	long OldLineBytes = (wide*8*pixelbyte+31)/32*4;
	unsigned char *lpSrc,*lpDst;
	unsigned char *lp;
	BITMAPINFOHEADER *lpinfor;
	int i , j , i0 , j0;
	
	unsigned char *lpDib = new unsigned char [linebytes*newheight+sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD)];
	if (lpDib == NULL){
		return(FALSE);}
	memcpy(lpDib,m_pDib,sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD));
	
	lpinfor = (BITMAPINFOHEADER*) lpDib;
	lpinfor->biWidth= newwidth;
	lpinfor->biHeight= newheight;
	
	lp = lpDib+sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD);
	if (lp==NULL){
		return (FALSE);}
	lp = new unsigned char [linebytes*newheight];
	memset(lp , (BYTE)255 , linebytes*newheight);
	
	for(j = 0; j < newheight - 1; j++)
	{
		for(i = 0; i < newwidth - 1; i++)
		{	
			for(int k=0;k<pixelbyte;k++){
				lpDst = lp + linebytes * j + i*pixelbyte+k;    
				i0=(int)(i / xratio + 0.5);
				j0=(int)(j / yratio + 0.5);	
				if( (i0 >= 0) && (i0 < wide) && (j0 >= 0) && (j0 < m_Height))
				{
					lpSrc=m_pDibBits + OldLineBytes * j0 + i0*pixelbyte+k;	
					*lpDst=*lpSrc;
				}
				else
				{
					*lpDst=255;
				}
		}	}
	} 
	
	delete []m_pDib;
	m_pDib = lpDib;
	m_pDibBits = lp;
	m_pBIH = lpinfor;
	m_pBIH->biSizeImage = linebytes* newheight;
	wide = lpinfor->biWidth;
	m_Width=linebytes;
	m_Height = lpinfor->biHeight;
	return TRUE;
}
/***********************************************************************
* 函数名称：
* Suoxiao2()
*说明：参数为X轴缩放倍数和Y轴缩放倍数，采用双线性插值方法缩放图像
***********************************************************************/
bool CDib::Suoxiao2( float xratio,float yratio )
{
	m_rtPosDest.SetRect(CPoint(0,0),CPoint(m_Width*xratio,m_Height*yratio));
	m_rtPosSour = m_rtPosDest;
	
	unsigned char array[2][2];
	long newwidth = (LONG) (wide * xratio +0.5);
	long newheight = (LONG) (m_Height * yratio+0.5);
	long linebytes = (newwidth*8*pixelbyte+31)/32*4;
	long OldLineBytes = (wide*8*pixelbyte+31)/32*4;
	unsigned char *lp;
	BITMAPINFOHEADER *lpinfor;
	int i , j ;
	
	unsigned char *lpDib = new unsigned char [linebytes*newheight+sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD)];
	if (lpDib == NULL){
		return(FALSE);}
	memcpy(lpDib,m_pDib,sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD));
	
	lpinfor = (BITMAPINFOHEADER*) lpDib;
	lpinfor->biWidth= newwidth;
	lpinfor->biHeight= newheight;
	
	lp = lpDib+sizeof(BITMAPINFOHEADER)+ PaletteEntries*sizeof(RGBQUAD);
	if (lp==NULL){
		return (FALSE);}
	lp = new unsigned char [linebytes*newheight];
	memset(lp , (BYTE)255 , linebytes*newheight);
	for(i=0; i< newheight; i++){
		for(j=0; j< newwidth ; j++){   
			
			//输出图像坐标为(j,i)的像素映射到原图中的坐标值，即插值位置
			float coordinateX=j/xratio;
			float coordinateY=i/yratio;
			
			//对插值位置坐标取整
			int Iu=(int)coordinateX;
			int Iv=(int)coordinateY;
			
			//若插值位置在输入图像范围内，则双线性插值
			if(0<=coordinateX&&coordinateX<wide
				&& coordinateY>=0&&coordinateY<m_Height){
				//将图像每个像素通道的数据进行分别插值，
				//彩图pixelByte为3，灰度图像pixelByte为1
				for(int k=0;k<pixelbyte;k++){
					//将第k个通道的四个像素数据拷贝至array数组中
					array[0][0]=*(m_pDibBits+ Iv*OldLineBytes+ Iu*pixelbyte+k);
					array[0][1]=*(m_pDibBits+ Iv*OldLineBytes+ (Iu+1)*pixelbyte+k);
					array[1][0]=*(m_pDibBits+ (Iv+1)*OldLineBytes+ Iu*pixelbyte+k);
					array[1][1]=*(m_pDibBits+ (Iv+1)*OldLineBytes+ (Iu+1)*pixelbyte+k);
					
					//调用双线性插值函数插值并输出到pImgOut中
					*(lp+ i * linebytes + j*pixelbyte+k)
						=interpolationDblLinear(array, coordinateX-Iu, coordinateY-Iv);
				}
			}
			else{//边缘像素采用近邻插值
				for(int k=0;k<pixelbyte;k++)
					*(lp + i * linebytes + j*pixelbyte + k) =
					*(m_pDibBits+ Iv*OldLineBytes+ Iu*pixelbyte+k);
			}
			
		}
	}
	
	delete []m_pDib;
	m_pDib = lpDib;
	m_pDibBits = lp;
	m_pBIH = lpinfor;
	m_pBIH->biSizeImage = linebytes* newheight;
	wide = lpinfor->biWidth;
	m_Width=linebytes;
	m_Height = lpinfor->biHeight;
	return TRUE;
}
/***********************************************************************
* 函数名称：
* Zoom()
*说明：通过鼠标滚动实现图像的缩放
***********************************************************************/
void CDib::Zoom( float ratio )
{
	if (ratio >=0)
	{
		m_rtPosDest.InflateRect((long)(m_rtPosDest.Width() * ratio),(long)(m_rtPosDest.Height() * ratio));
	} else
	{
		long x = (long)(m_rtPosDest.Width() * fabs(ratio));
		long y = (long)(m_rtPosDest.Height() * fabs(ratio));
		m_rtPosDest.DeflateRect(x,y);
	}
}
/***********************************************************************
* 函数名称：
* interpolationDblLinear()
*说明：参数:   array，2*2数组，存放图像待插值位置周围四个像素灰度值
               xpos，ypos为相对于数组四个像素的插值位置坐标，取小数
       返回值: 插值结果。
       该函数将原图像待插值位置的四个像素数据拷贝到数组array中，根据插值位置坐标对
    应到array的位置，对数组array的四个元素进行双线性插值，返回值为插值的结果。
***********************************************************************/
unsigned char CDib::interpolationDblLinear( unsigned char array[2][2], float xpos, float ypos )
{
	//两个中间变量
	int t1, t2;	
	//先垂直方向线性插值
	t1 = (1-ypos)*array[0][0] + ypos*array[1][0];
	t2 = (1-ypos)*array[0][1] + ypos*array[1][1];	
	//再水平方向线性插值
	float t=(int)((1-xpos)*t1 + xpos*t2);	
	//若插值结果小于0，则输出0
	if(t<0)
		t=0;	
	//若插值结果大于255，则输出255
	if(t>255) 
		t=255;	
	//插值结果返回
	return (unsigned char)t;
}
/***********************************************************************
* 函数名称：
* MirrorVerti()
*说明：对图像垂直镜像
***********************************************************************/
void CDib::MirrorHori()
{
	memcpy(m_pDibBitsout,m_pDibBits,m_Width*m_Height);
	for(int i=0;i<m_Height;i++)
	{
		for(int j=0;j<wide;j++)
		{
			for(int k=0;k<pixelbyte;k++)
				*(m_pDibBits+i*m_Width+j*pixelbyte+k)
				=*(m_pDibBitsout+i*m_Widthout+(wide-1-j)*pixelbyte+k);
		}
	}
}
/***********************************************************************
* 函数名称：
* MirrorVerti()
*说明：对图像垂直镜像
***********************************************************************/
void CDib::MirrorVerti()
{
	memcpy(m_pDibBitsout,m_pDibBits,m_Width*m_Height);
	for(int i=0;i<m_Height;i++)
	{
		for(int j=0;j<wide;j++)
		{
			for(int k=0;k<pixelbyte;k++)
				*(m_pDibBits+i*m_Width+j*pixelbyte+k)
				=*(m_pDibBitsout+(m_Height-1-i)*m_Widthout+j*pixelbyte+k);
		}
	}
}
/***********************************************************************
* 函数名称：
* PointInRect()
*说明：确定指定的点是否在CRect之内
***********************************************************************/
bool CDib::PointInRect( CPoint point )
{
	return m_rtPosDest.PtInRect(point);
}
/***********************************************************************
* 函数名称：
* SetDestRect()
*说明：将CRect移动到指定的偏移
***********************************************************************/
void CDib::SetDestRect( CSize SizeOffset )
{
	m_rtPosDest.OffsetRect(SizeOffset);
}
/***********************************************************************
* 函数名称：
* Erzhi()
*说明：将图像二值化
***********************************************************************/
void CDib::Erzhi()
{
	int T=FindT();   //T值约为205
	long sum;
	for (int i=0;i<m_Height;i++)
	{
		for (int j=0;j<wide;j++)
		{
			sum=0;
			for (int k=0;k<3;k++)
			{
				sum=sum+*(m_pDibBits+i*m_Width+j*3+k);
			}
			sum=sum/3;
			//小于阈值则置黑
			if (sum<T)
			{
				for (int k=0;k<3;k++)
				{
					*(m_pDibBits+i*m_Width+j*3+k)=0;
				}				
			}
			//大于阈值则置白
			else
			{
				for (int k=0;k<3;k++)
				{
					*(m_pDibBits+i*m_Width+j*3+k)=255;
				}
			}
		}
	}
}
/***********************************************************************
* 函数名称：
* FindT()
*说明：找到阈值用于二值化
***********************************************************************/
int CDib::FindT()
{
	int T=127;
	int T1;
	long T0=10;
	long sum=0;
	long sum1=0;
	long sum2=0;
	int  num1=0;
	int  num2=0;
	long u1,u2;
	while(T0>1)
	{
		for (int i=0;i<m_Height;i++)
		{
			for(int j=0;j<wide;j++)
			{
				sum=0;
				for (int k=0;k<3;k++)
				{
					sum=sum+*(m_pDibBits+i*m_Width+j*3+k);
				}
				sum=sum/3;
				if (sum<T)
				{
					sum1=sum1+sum;
					num1++;
				}
				else
				{
					sum2=sum2+sum;
					num2++;
				}
			}
		}
		u1=sum1/num1;
		u2=sum2/num2;
		T1=(u1+u2)/2;
		T0=abs(T-T1);
		T=T1;
	}
	return T;
}
/***********************************************************************
* 函数名称：
* Fushi()
*说明：对图像进行腐蚀处理
***********************************************************************/
void CDib::Fushi()
{
	//以白色为背景
	int i,j;
	memcpy(m_pDibBitsout,m_pDibBits,m_Width*m_Height);
	for (i=3;i<m_Height-3;i++)
	{
		for (j=3;j<wide-3;j++)
		{
			for (int k=0;k<pixelbyte;k++)
			{
				for(int m=i-3;m<i+4;m++)
				{
					for (int n=j-3;n<j+4;n++)
					{
						if (*(m_pDibBitsout+m*m_Width+n*pixelbyte+k)==255)
						{
							*(m_pDibBits+i*m_Width+j*pixelbyte+k)=255;
						}
					}
				}
				
			}
		}
	} 
//7*7模板
}
/***********************************************************************
* 函数名称：
* Pengzhang()
*说明：对图像进行膨胀处理
***********************************************************************/
void CDib::Pengzhang()
{
	//以白色为背景
	int i,j;
	memcpy(m_pDibBitsout,m_pDibBits,m_Width*m_Height);
	for (i=3;i<m_Height-3;i++)
	{
		for (j=3;j<wide-3;j++)
		{
			for (int k=0;k<pixelbyte;k++)
			{
				for(int m=i-3;m<i+4;m++)
				{
					for (int n=j-3;n<j+4;n++)
					{
						if (*(m_pDibBitsout+m*m_Width+n*pixelbyte+k)==0)
						{
							*(m_pDibBits+i*m_Width+j*pixelbyte+k)=0;
						}
					}
				}
				
			}
		}
	} 
//7*7模板
}
/***********************************************************************
* 函数名称：
* TiquRobert()
*说明：采用Robert算子进行边界提取
***********************************************************************/
void CDib::TiquRobert()
{
	int i,j,k;
	int x, y, t;
	memcpy(m_pDibBitsout,m_pDibBits,m_Width*m_Height);
	for(i=1;i<m_Height-1;i++)
	{
		for(j=1;j<wide-1;j++)
		{
			for(k=0;k<pixelbyte;k++)
			{
				//有两个模板
				//x方向梯度
				x=*(m_pDibBits+i*m_Width+j*pixelbyte+k)
					-*(m_pDibBits+(i+1)*m_Width+j*pixelbyte+k);
				
				//y方向梯度
				y=*(m_pDibBits+i*m_Width+j*pixelbyte+k)
					-*(m_pDibBits+i*m_Width+(j+1)*pixelbyte+k);
				
				t=sqrt(x*x+y*y)+0.5;
				if(t>255)
					t=255;
				*(m_pDibBitsout+i*m_Width+j*pixelbyte+k)=t;
			}
		}
	}
	memcpy(m_pDibBits,m_pDibBitsout,m_Width*m_Height);
}
/***********************************************************************
* 函数名称：
* Jiabianjie()
*说明：将边界加到原图
***********************************************************************/
void CDib::Jiabianjie()
{
	memcpy(m_pDibBitsout,m_pDibBits,m_Width*m_Height);
	for (int i=0;i<m_Height;i++)
	{
		for (int j=0;j<wide;j++)
		{
            for (int k=0;k<pixelbyte;k++)
			{
				if (*(m_pDibBitsout+i*m_Width+j*pixelbyte+k)==255)
				{
					if (i==0|i==m_Height-1|j==0|j==wide-1)
					{
						continue;
					}
					*(m_pDibBitsback+i*m_Width+j*pixelbyte+k)=0;
				}
			}
		}
	}
	memcpy(m_pDibBits,m_pDibBitsback,m_Width*m_Height);
}
/***********************************************************************
* 函数名称：
* Tiqu2()
*说明：形态学方法进行边界提取
***********************************************************************/
void CDib::Tiqu2()
{
	if(PaletteEntries!=0){
		long linebytes = (wide*8+31)/32*4;
		unsigned char *lpSrc,*lpDst;
		unsigned char *lp;
		int i,j;
		lpSrc=m_pDibBits;
		lp = new unsigned char [linebytes*m_Height];
		memset(lp , (BYTE)255 , linebytes*m_Height);
		float temp1;
		for(i = 1; i < m_Height-1; i++)
			for(j = 1; j < linebytes-1; j++)
			{	
				
				lpDst=(unsigned char*)lp+i*linebytes+j;										
				if ((lpSrc[i*linebytes+j]==255) &&(lpSrc[i*linebytes+j+1]==255)&&
					(lpSrc[i*linebytes+j-1]==255)&&
					(lpSrc[(i-1)*linebytes+j-1]==255)&&(lpSrc[(i+1)*linebytes+j-1]==255)&&
					(lpSrc[(i+1)*linebytes+j]==255)&&
					(lpSrc[(i-1)*linebytes+j]==255)&&(lpSrc[(i-1)*linebytes+j+1]==255)&&
					(lpSrc[(i+1)*linebytes+j+1]==255))
				{
					*lpDst=255;
				}
				else
				{
					*lpDst=0;
				}
				
			}
			for(i = 0; i < m_Height; i++)
				for(j = 0; j < linebytes; j++)
				{
					lpDst=(unsigned char*)lp+i*linebytes+j;	
					lpSrc=m_pDibBits+i*linebytes+j;
					if(*lpSrc==*lpDst)
					{
						*lpDst=0;
					}
                    else{
						*lpDst=255;}
				}
				memcpy(m_pDibBits,lp,linebytes*m_Height);
				//delete []lp;
	}
	else{
		long linebytes = (wide*8*3+31)/32*4;
		unsigned char *lpSrc,*lpDst;
		unsigned char *lp;
		int i,j;
		lpSrc=m_pDibBits;
		lp = new unsigned char [linebytes*m_Height];
		memset(lp , (BYTE)255 , linebytes*m_Height);
		float temp1;
		for(i = 1; i < m_Height-1; i++)
			for(j = 1; j < linebytes-1; j+=3)
			{	
				
				lpDst=(unsigned char*)lp+i*linebytes+3*j;										
				if ((lpSrc[i*linebytes+3*j]==255) &&(lpSrc[i*linebytes+3*j+3*1]==255)&&
					(lpSrc[i*linebytes+3*j-3*1]==255)&&
					(lpSrc[(i-1)*linebytes+3*j-3*1]==255)&&(lpSrc[(i+1)*linebytes+3*j-3*1]==255)&&
					(lpSrc[(i+1)*linebytes+3*j]==255)&&
					(lpSrc[(i-1)*linebytes+3*j]==255)&&(lpSrc[(i-1)*linebytes+3*j+3*1]==255)&&
					(lpSrc[(i+1)*linebytes+3*j+3*1]==255))
				{
					*lpDst=255;
					*(lpDst+1)=255;
					*(lpDst+2)=255;
				}
				else
				{
					*lpDst=0;
					*(lpDst+1)=0;
					*(lpDst+2)=0;
				}
				
			}
			for(i = 0; i < m_Height; i++)
				for(j = 0; j < linebytes; j++)
				{
					lpDst=(unsigned char*)lp+i*linebytes+3*j;	
					lpSrc=m_pDibBits+i*linebytes+3*j;
					if(*lpSrc==*lpDst)
					{
						*lpDst=0;
						*(lpDst+1)=0;
						*(lpDst+2)=0;
					}
                    else{
						*lpDst=255;
						*(lpDst+1)=255;
						*(lpDst+2)=255;}
				}
				memcpy(m_pDibBits,lp,linebytes*m_Height);
				//	delete []lp;
	}
}
/***********************************************************************
* 函数名称：
* TiquLaplacian()
*说明：拉普拉斯算子提取边界
***********************************************************************/
void CDib::TiquLaplacian()
{
	memcpy(m_pDibBitsout ,m_pDibBits , m_Width*m_Height);
	int i,j,k;
	
	//中间变量
	int t;
	
	//Laplacian算子
	for(i=1;i<m_Height-1;i++){
		for(j=1;j<wide-1;j++){
			for(k=0;k<pixelbyte;k++){
				//只有一个模板
				//由该点的灰度值减去该点邻域的平均灰度值
				t= 4 * *(m_pDibBits+i*m_Width+j*pixelbyte+k)- *(m_pDibBits+(i-1)*m_Width+j*pixelbyte+k)
					- *(m_pDibBits+(i+1)*m_Width+j*pixelbyte+k)- *(m_pDibBits+i*m_Width+(j-1)*pixelbyte+k)
					- *(m_pDibBits+i*m_Width+(j+1)*pixelbyte+k);
				t=abs(t)+0.5;
				if(t>255)
					t=255;
				*(m_pDibBitsout+i*m_Width+j*pixelbyte+k)=t;
			}
		}
	}
	memcpy(m_pDibBits,m_pDibBitsout,m_Width*m_Height);
}
/***********************************************************************
* 函数名称：
* TiquSobel()
*说明：sobel算子提取边界
***********************************************************************/
void CDib::TiquSobel()
{
	memcpy(m_pDibBitsout ,m_pDibBits , m_Width*m_Height);
	int i,j,k;
	
	//中间变量
	int x, y, t;
	
	//Sobel算子
	for(i=1;i<m_Height-1;i++){
		for(j=1;j<wide-1;j++){
			for(k=0;k<pixelbyte;k++){
				//x方向梯度
				x= *(m_pDibBits+(i-1)*m_Width+(j+1)*pixelbyte+k)
					+ 2 * *(m_pDibBits+i*m_Width+(j+1)*pixelbyte+k)
					+ *(m_pDibBits+(i+1)*m_Width+(j+1)*pixelbyte+k)
					- *(m_pDibBits+(i-1)*m_Width+(j-1)*pixelbyte+k)
					- 2 * *(m_pDibBits+i*m_Width+(j-1)*pixelbyte+k)
					- *(m_pDibBits+(i+1)*m_Width+(j-1)*pixelbyte+k);
				
				//y方向梯度
				y= *(m_pDibBits+(i-1)*m_Width+(j-1)*pixelbyte+k)
					+ 2 * *(m_pDibBits+(i-1)*m_Width+j*pixelbyte+k)
					+ *(m_pDibBits+(i-1)*m_Width+(j+1)*pixelbyte+k)
					- *(m_pDibBits+(i+1)*m_Width+(j-1)*pixelbyte+k)
					- 2 * *(m_pDibBits+(i+1)*m_Width+j*pixelbyte+k)
					- *(m_pDibBits+(i+1)*m_Width+(j+1)*pixelbyte+k);
				
				t=sqrt(x*x+y*y)+0.5;
				if(t>255)
					t=255;
				*(m_pDibBitsout+i*m_Width+j*pixelbyte+k)=t;
			}
		}
	}
	memcpy(m_pDibBits,m_pDibBitsout,m_Width*m_Height);
}
/***********************************************************************
* 函数名称：
* RegionGrow()
*说明：区域生长，模板函数，阈值设定为80，种子坐标(130,80)
***********************************************************************/
void CDib::RegionGrow()
{
	//循环变量
	int i, j;
	
	CPoint seed;
	int thresh;
	
	seed=(130,80);
	thresh=80;           //这两个参数的选择是关键！！！
	m_pDibBitsout=new unsigned char[m_Width*m_Height];
	
	
	//将输出图像初始化置255,用0代表像素的生长标记
	for(i=0;i<m_Height;i++){
		for(j=0;j<wide;j++){              //这里要用linebytes
			*(m_pDibBitsout+i*m_Width+j)=255;
		}
	}
	
	//二维数组direction代表中心像素点8邻域坐标与该点在x和y方向上的偏移,
	//其中第一列为x方向的偏移,第二列为y方向的偏移
	int direction[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
	
	//栈申请，此处假定进栈的像素最多为图像总像素数
	CPoint *stack=new CPoint[wide*m_Height];
	
	//栈顶指针
	int top;
	
	//当前正处理的点和弹出的点
	CPoint currentPoint, popPoint;
	
	//循环变量，遍历array数组的第一维下标
	int k;
	
	//标记变量
	int label;
	
	//临时变量
	int temp1, temp2;
	
	//记录种子像素的灰度值
	temp1=*(m_pDibBits+seed.y*m_Width+seed.x);
	
	//将给定种子点置标记0,入栈
	*(m_pDibBitsout+seed.y*m_Width+seed.x)=0;
	top=0;
	stack[top].x=seed.x;
	stack[top].y=seed.y;
	
	//堆栈
	while(top>-1){
		//弹出栈顶元素,该元素已经生长过
		popPoint.x=stack[top].x;
		popPoint.y=stack[top].y;
		top--;
		
		//考察弹出像素周围是否有没有生长的像素
		for(k=0;k<8;k++){
			
			//待考察的邻域点
			currentPoint.x=popPoint.x+direction[k][0];
			currentPoint.y=popPoint.y+direction[k][1];
			
			//如果待考察的点不在图像内，则跳过
			if(currentPoint.x<0||currentPoint.x>wide-1||
				currentPoint.y<0||currentPoint.y>m_Height-1)
				continue;
			
			//该点标号
			label=*(m_pDibBitsout+currentPoint.y*m_Width+currentPoint.x);
			
			//弹出的点周围有尚没生长的点
			if(label==255){
				temp2=*(m_pDibBits+currentPoint.y*m_Width+currentPoint.x);
				//如果当前被考察的像素灰度值与种子点灰度值之差小于给定的阈值,
				//则认为相似,将其进栈处理
				if(abs(temp1-temp2)<thresh){
					//给该点置生长标记0
					*(m_pDibBitsout+currentPoint.y*m_Width+currentPoint.x)=0;
					top++;
					stack[top].x=currentPoint.x;
					stack[top].y=currentPoint.y;
				}
			}
		}
		
	}
	memcpy(m_pDibBits,m_pDibBitsout,m_Width*m_Height);
	
	//清除缓冲区
	delete []stack;
}
