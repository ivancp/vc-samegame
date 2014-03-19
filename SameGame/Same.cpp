// Same.cpp: implementation of the CSame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SameGame.h"
#include "Same.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int dirs[TMAX][2] =
{
    {1,0},
    {0,1},
    {-1,0},
    {0,-1}
};


CSame::CSame(int _n, int _m)
{

  n = _n;
  m = _m;
  pCells = new CELL*[n];
  pDel =  new int[m];
  for(int i = 0 ; i < n; i++)
  {
     pCells[i] = new CELL[m];
  }
  for(int j = 0 ; j < m ; j++)
	  pDel[j] = 0;
  points = 0;

  Random();
}

CSame::~CSame()
{
  for(int i = 0 ; i < n ; i++)
  {
     delete pCells[i];
  }
  delete pCells;
  delete pDel;
}

void CSame::Zero()
{
  ballcount = 0;
  for(int i = 0 ; i < n ; i++)
  {
     for(int j = 0 ; j < m ; j++)
     {
        pCells[i][j].count = 0;
		if(pCells[i][j].color != ' ') ballcount++;
     }
  }
}
POINT CSame::Find(int &mx)
{
    Zero();
	POINT  p;
	p.x = -1;
	p.y = -1;

	int c;
	max = 0;
	for(int j = 0; j < m ; j++)
	{
		for(int i = n-1 ; i >= pDel[j]; i--)
		{
			if(pCells[i][j].color != ' ' && pCells[i][j].count == 0)
			{
				c = 0;
				Find(i,j,c);
				if(max < c)
				{
					max = c;
					p.x = j;
					p.y = i;
				}
			}
		}
	}
	mx = max;	
	return p;
}
void CSame::Find(int i,int j,int &count)
{
	if(pCells[i][j].color != ' ' && pCells[i][j].count == 0)
	{
  	  count++;
	  pCells[i][j].count = -1;
	  for(int k = 0 ; k < TMAX; k++)
	  {
		 if((((i + dirs[k][Y]) >= 0) && ((i + dirs[k][Y]) < n)) &&
		 (((j + dirs[k][X]) >= 0) && ((j + dirs[k][X]) < m)))
		 {
			 if(pCells[i + dirs[k][Y]][j + dirs[k][X]].color == pCells[i][j].color)
			 {
				
				Find(i + dirs[k][Y],j + dirs[k][X],count);
			 }
		 }
	  }
	}
}
void CSame::ReorganizeV()
{
	// Elimando espacios en blando verticalmente
	int swp;
	for(int k = 0 ; k < m; k++)
	{
		if(pDel[k] > 0)
		{
			swp = pDel[k] - 1;
			while(swp >= 0)
			{
				if(pCells[swp][k].color >= 'B')
				{
					pCells[pDel[k]][k].color  = pCells[swp][k].color ;
					pCells[pDel[k]][k].count = 0;
					pCells[swp][k].count = 0;
					pCells[swp][k].color = ' ';
					pDel[k] -= 1;
				}
				swp--;
			}
		}
	}
}

void CSame::ReorganizeH()
{
	// Elimando espacios en blanco horizontalmente
	int swp1;
	int swp2;
	for(int j = 0 ; j < (m-1); j++)
	{
		if(pDel[j] == (n-1))
		{
			swp1 = j;
			swp2 = j+1;
			while(swp2 < m)
			{
				if(pDel[swp2] < (n-1))
				{
					for(int i = 0 ; i < n; i++)
					{
						pCells[i][swp1].color  = pCells[i][swp2].color;
						pCells[i][swp2].color = ' ';

						pCells[i][swp1].count = 0;
						pCells[i][swp2].count = 0;						
					}
					pDel[swp1] = pDel[swp2];
					pDel[swp2] = (n-1);
					swp1++;
				}
				swp2++;
			}			
		}
	}
}
void CSame::Delete(int i,int j,int &c)
{
  char t = pCells[i][j].color;
  pCells[i][j].color = ' ';
  pCells[i][j].count = 0;

  if(pDel[j] < i)
  {
	  pDel[j] = i;
  }
  c += 1;
  for(int k = 0 ; k < TMAX; k++)
  {
     if((((i + dirs[k][Y]) >= 0) && ((i + dirs[k][Y]) < n)) &&
     (((j + dirs[k][X]) >= 0) && ((j + dirs[k][X]) < m)))
     {
         if(pCells[i + dirs[k][Y]][j + dirs[k][X]].color == t)
		 {
			 Delete(i + dirs[k][Y],j + dirs[k][X],c);
		 }
     }
  }
}
void CSame::Random()
{
  int colors[3] = {'R','G','B'};
  for(int i = 0 ; i < n ; i++)
  {
     for(int j = 0 ; j < m ; j++)
     {
        pCells[i][j].count = 0;
	
		pCells[i][j].color = colors[rand()%3];
     }
  }
}



void CSame::Draw(CDC *pDC,CImageList *img)
{
  int scale = 23;
  POINT pt;
  for(int i = 0 ; i < n ; i++)
  {
	 for(int j = 0 ; j < m ; j++)
	 {
		 pt.x = scale*j;
		 pt.y = scale*i;
		 
		 switch(pCells[i][j].color)
		 {
		 case 'R':
				 img->Draw(pDC,3,pt,ILD_NORMAL);
				 break;
		 case 'G':
				 img->Draw(pDC,4,pt,ILD_NORMAL);
				 break;
		 case 'B':
				 img->Draw(pDC,5,pt,ILD_NORMAL);
				 break;
		 }
	 }
  }
}

void CSame::DrawHot(CDC *pDC,int i,int j,CImageList *img)
{
	POINT pt = {j*23,i*23};
	if(pCells[i][j].color != ' ' && pCells[i][j].count == 0)
	{
	     pCells[i][j].count = -1;

		 switch(pCells[i][j].color)
		 {
			 case 'R':
					 img->Draw(pDC,3,pt,ILD_NORMAL);
					 break;
			 case 'G':
					 img->Draw(pDC,4,pt,ILD_NORMAL);
					 break;
			 case 'B':
					 img->Draw(pDC,5,pt,ILD_NORMAL);
					 break;
		 }

	  for(int k = 0 ; k < TMAX; k++)
	  {
		 if((((i + dirs[k][Y]) >= 0) && ((i + dirs[k][Y]) < n)) &&
		 (((j + dirs[k][X]) >= 0) && ((j + dirs[k][X]) < m)))
		 {
			 if(pCells[i + dirs[k][Y]][j + dirs[k][X]].color == pCells[i][j].color)
			 {
				DrawHot(pDC,i + dirs[k][Y],j + dirs[k][X],img);
			 }
		 }
	  }
	}	
}
