// Same.h: interface for the CSame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAME_H__9AB77AF4_95E6_4FA2_AF22_307546F2759B__INCLUDED_)
#define AFX_SAME_H__9AB77AF4_95E6_4FA2_AF22_307546F2759B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define TMAX 4


#define X 0
#define Y 1
struct CELL
{
	char color;
	int count;
	CELL()
	{
		color = ' ';
		count = 0;
	}
};


class CSame  
{
	int *pDel;
  public:
	  void DrawHot(CDC *pDC,int i,int j,CImageList *img);
    int n,m;
	  void Draw(CDC * pDC,CImageList *img);
	  void Random();
	int points;
	int max;
	int ballcount;
	CELL **pCells;
    CSame(int _n, int _m);
	~CSame();
	void Delete(int i,int j,int &c);
	void ReorganizeV();
	void ReorganizeH();
	void Find(int i,int j,int &count);
	POINT Find(int &mx);
	void Zero();
};

#endif // !defined(AFX_SAME_H__9AB77AF4_95E6_4FA2_AF22_307546F2759B__INCLUDED_)
