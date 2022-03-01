#if !defined(AFX_DIALOGIMAGE_H__7D8FC2BD_E66A_4306_A18B_924A83B05B12__INCLUDED_)
#define AFX_DIALOGIMAGE_H__7D8FC2BD_E66A_4306_A18B_924A83B05B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogImage.h : header file
//
#include "ImageReelle.h"
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CDialogImage dialog

class CDialogImage : public CDialog
{
// Construction
public:
	CDialogImage(CImageReelle* pImage,CWnd* pParent = NULL);   // standard constructor
	CDialogImage(int, int, CImageReelle* pImage, CWnd* pParent = NULL);   // constructeur avec redimensionnement

// Dialog Data
	//{{AFX_DATA(CDialogImage)
	enum { IDD = IDD_DIALOG_IMAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogImage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogImage)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CImageReelle * ptImage;
	int width, length;
	CPoint Point[20];
	int nbPoints=0, position=0;
	int x[20]; //vecteur pour rec. les coordonnees x
	int y[20]; //vecteur pour rec. les coordonnees y
	int xPrime[20]; //vecteur pour rec. les coordonnees x
	int yPrime[20]; //vecteur pour rec. les coordonnees y

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

private:
	void RepiquageImage();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGIMAGE_H__7D8FC2BD_E66A_4306_A18B_924A83B05B12__INCLUDED_)
