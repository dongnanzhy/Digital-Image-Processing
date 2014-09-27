// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__CF2B2C9B_FFFE_4678_A973_C5823C7F4444__INCLUDED_)
#define AFX_DIB_H__CF2B2C9B_FFFE_4678_A973_C5823C7F4444__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDib  
{
public:
	CDib();
	virtual ~CDib();

	bool LoadFile(const char *FileName);           //读入图像
	bool SaveFile( const char* pFileName);         //保存图像
	void Draw(CDC *pDC);                           //画图像
	long* GetGreyCountNumber();                    //
    long GetPaletteEntries();                      //求颜色数
    /* 简单图像处理*/
	void Invert();                                 //负片
	void Liner(int X1,int Y1,int X2,int Y2);       //线性变换
	void Histave();                                //直方图均衡
	void PseuColor();                              //伪彩
	void Colortogrey();                            //彩色变灰度
    /*图像增强*/
	void AddPepperSaltNoise();                     //加椒盐噪声
	void AddRandomNoise();                         //加随机噪声
	void Lapchange();                              //拉普拉斯锐化
	void GradSharp();                              //梯度锐化
	void Midchange();                              //中值滤波
	void Pinghua();                                //平滑滤波
    /*图像几何变换*/
	void Pingyi(int offsetX,int offsetY);          //平移
	bool Xuanzhuan(int angle);                     //旋转 邻近插值
	bool Xuanzhuan2(int angle);                    //旋转 双线性插值
	bool Suoxiao(float xratio,float yratio);       //缩放 邻近插值
	bool Suoxiao2(float xratio,float yratio);      //缩放 双线性插值
	unsigned char interpolationDblLinear(unsigned char array[2][2], float xpos, float ypos);
	void MirrorHori();                             //水平镜像
	void MirrorVerti();                            //垂直镜像
	bool PointInRect( CPoint point );              //判断是否在矩形内
	void SetDestRect( CSize SizeOffset );          //改变矩形大小位置
	void Zoom( float ratio );                      //图像的鼠标缩放
    /*形态学及分割*/
	void Erzhi();                                  //对彩色图像二值化
	int FindT();                                   //找到门限
	void Fushi();                                  //腐蚀    
	void Pengzhang();                              //膨胀
	void TiquRobert();                             //提取边界Robert算子
	void TiquLaplacian();                          //提取边界拉普拉斯算子
	void TiquSobel();                              //提取边界sobel算子                  
	void Tiqu2();                                  //提取边界形态学
	void Jiabianjie();                             //边界加到原图上
	void RegionGrow();                             //区域增长

private:
	unsigned char *m_pDib;
	unsigned char *m_pDibout;
	unsigned char *m_pDibback;
	unsigned char *m_pDibBits;
	unsigned char *m_pDibBitsout;
	unsigned char *m_pDibBitsback;
	CPalette m_Palette;
	int PaletteEntries;
	long m_Width;
	long pixelbyte;
	long wide;
	long m_Height;
	long m_Widthout;
	long m_Heightout;
	BITMAPINFOHEADER *m_pBIH;
	BITMAPFILEHEADER BFH;
	RGBQUAD *m_pPalette;
	CRect m_rtPosSour,m_rtPosDest;
};

#endif // !defined(AFX_DIB_H__CF2B2C9B_FFFE_4678_A973_C5823C7F4444__INCLUDED_)
