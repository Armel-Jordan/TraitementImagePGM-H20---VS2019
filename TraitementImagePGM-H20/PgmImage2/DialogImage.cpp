// DialogImage.cpp : implementation file
//

#include "stdafx.h"
#include "PgmImage2.h"
#include "DialogImage.h"
#include <vector>
#include <math.h>
#include "Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogImage dialog


CDialogImage::CDialogImage(CImageReelle* pImage, CWnd* pParent /*=NULL*/)
	: CDialog(CDialogImage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogImage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
		ptImage = pImage;
		width=pImage->NbColonnes;
		length=pImage->NbLignes;
	
}
CDialogImage::CDialogImage(int largeur, int longueur, CImageReelle* pImage, CWnd* pParent /*=NULL*/)
	: CDialog(CDialogImage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogImage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
		ptImage = pImage;
		width=largeur;
		length=longueur;
}


void CDialogImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogImage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogImage, CDialog)
	//{{AFX_MSG_MAP(CDialogImage)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogImage message handlers

void CDialogImage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	int HorizontalShift=0;  //decalages entre les bords de la boite de dialogue et l'image
	int VerticalShift=0;
	int SX=8, SY=6; // facteur de scaling pour reduire la dimension de l'image originale
	int i, j; // compteurs
	float valeur; //valeur du niveau de gris en un point
	CClientDC ClientDC(this);

   
	for (i=0;i<length;i+=SY){
	  for (j = 0; j<width; j+=SX) {
	    if (ptImage->matrice[i][j]>=0)
			valeur = ptImage->matrice[i][j];
		else 
			valeur = 256+ptImage->matrice[i][j];
	    ClientDC.SetPixelV((j+HorizontalShift)/SX, (i+VerticalShift)/SY, RGB(valeur, valeur,valeur));
		
	  
	  }
    }

}

void CDialogImage::OnLButtonDown(UINT nFlags, CPoint point) //point c'est la coordonnee du point qui a ete selectionne 
{
	if (nbPoints == 18) {
		MessageBox(TEXT("Le nombre maximal de points de selection est atteint"), TEXT("Erreur !"), NULL);
		return;
	}

	CClientDC ClientDC(this);

	
	CPen pen;
	CPen penLine;
	CBrush brush;

	penLine.CreatePen(PS_SOLID, 2, RGB(0,0,255));
	

	pen.CreatePen(PS_SOLID, 2, RGB(255,0,0));
	ClientDC.SelectObject(&pen);

	brush.CreateSolidBrush(RGB(0,255,0));
	ClientDC.SelectObject(&brush);
	ClientDC.Ellipse(point.x-5,point.y-5,point.x+5,point.y+5);

	/*ClientDC.SelectObject(&penLine);
		
		
	ClientDC.MoveTo(point.x,point.y);
	ClientDC.LineTo(point.x + 100, point.y);

	ClientDC.SelectObject(&penLine);

	ClientDC.MoveTo(point.x,point.y);
	ClientDC.LineTo(point.x, point.y+100);*/
	if (nbPoints % 2 == 0) {
		x[position] = point.x;
		y[position] = point.y;
		Point[nbPoints++] = point;
	}
	else {
		xPrime[position] = point.x;
		yPrime[position] = point.y;
		Point[nbPoints++] = point;
		position++;
	}
	
	
	

	CDialog::OnLButtonDown(nFlags, point);
}

void CDialogImage::OnRButtonDown(UINT nFlags, CPoint point) //point c'est la coordonnee du point qui a ete selectionne 
{
	if (nbPoints < 12) {
		MessageBox(TEXT("Il faut selectionner au minimum six paires de points"), TEXT("Attention !"), NULL);
		return;
	}
	else {
		MessageBox(TEXT("Excellent"), TEXT("Attention !!! !"), NULL);
	}
	CClientDC ClientDC(this);


	int X[20], Y[20]; // pour 20 pixels selectionnes max.
	double wmax, wmin, ** a, ** u, * w, ** v, * b, * x;
	int i, j;

	Util util;

	// selectionner un minimum de 6 points a approximer
	//….// selectionner  un maximum de 20 points a approximer
	  // premier indice de X, Y, est 1
	int m = tabPoint.size();// est le nombre de points  selectionnes
	//pour gérer la condition sur m
	if (m < 4 || m>20)
	{
		return;
	}


	a = util.matrix(1, m, 1, 4); // matrice A de mX6
	u = util.matrix(1, m, 1, 4); // m: nombre de points a approximer
	w = util.vector(1, 4);
	v = util.matrix(1, 4, 1, 4);
	b = util.vector(1, m); // 0
	x = util.vector(1, 4); // vecteur des sol’n

	//initialisation de la matrice a
	for (i = 1; i <= m; i++)
	{
		a[i][1] = tabPoint[i - 1].x;
		a[i][2] = tabPoint[i - 1].y;
		a[i][3] = tabPoint[i - 1].z;
		a[i][4] = 1.0;
	}

	// initialiser le vecteur  b
	for (i = 1; i <= m; i += 1)
	{
		b[i] = 0.0;
	}

	//algorithme de resolution
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= 4; j++)
		{
			u[i][j] = a[i][j];
		}
	}

	//appel du svdcmp
	util.svdcmp(u, m, 4, w, v);

	//trouver le max
	wmax = 0.0;
	for (j = 1; j <= 4; j++)
	{
		if (w[j] > wmax)
			wmax = w[j];
	}

	//trouver le min
	int minPos = 0;
	wmin = wmax; // trouver la valeur propre min. dans w
	for (j = 1; j <= 4; j++)
	{
		if ((w[j] < wmin) && w[j] != 0.0)
		{
			wmin = w[j];
			minPos = j;
		}
	}

	//matrice solution
	for (j = 1; j <= 4; j++)
	{
		x[j] = v[j][minPos]; // x contient la solution
	}

	//calculer la moyenne en x (l'ensemble des coordonnées en x divisé par le nombre de points
	double sommeX = 0.0, moyenneX = 0.0;
	for (i = 1; i <= m; i++)
	{
		sommeX += tabPoint[i - 1].x;
	}
	moyenneX = sommeX / m;


	//calculer la moyenne en y
	double sommeY = 0.0, moyenneY = 0.0;
	for (i = 1; i <= m; i++)
	{
		sommeY += tabPoint[i - 1].y;
	}
	moyenneY = sommeY / m;


	//calcul du vecteur unitaire de la solution
	double sommeCarre = 0.0, inverseRacine;
	double* normale = util.vector(1, 4);
	for (i = 1; i <= 3; i++)
	{
		sommeCarre += x[i] * x[i];
	}
	inverseRacine = 1.0 / sqrt(sommeCarre);
	for (i = 1; i <= 3; i++)
	{
		normale[i] = inverseRacine * x[i];
	}

	CPen penLine;
	CBrush brush;

	penLine.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	//dessiner le vecteur avec clientMoveTo et LineTo
	ClientDC.SelectObject(penLine);
	ClientDC.MoveTo(590 + moyenneX, 360 + moyenneY);
	ClientDC.LineTo(590 + moyenneX + normale[1] * 100.0, 360 + moyenneY + normale[2] * 100.0);


	//liberer mon vecteur et ma matrice
	util.free_matrix(a, 1, 4, 1, 4);
	util.free_vector(normale, 1, 4);

	CDialog::OnLButtonDown(nFlags, point);
}


