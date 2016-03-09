
// MyFirstOpenMeshView.cpp : implementation of the CMyFirstOpenMeshView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyFirstOpenMesh.h"
#endif

#include "MyFirstOpenMeshDoc.h"
#include "MyFirstOpenMeshView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyFirstOpenMeshView

IMPLEMENT_DYNCREATE(CMyFirstOpenMeshView, CView)

BEGIN_MESSAGE_MAP(CMyFirstOpenMeshView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMyFirstOpenMeshView construction/destruction

CMyFirstOpenMeshView::CMyFirstOpenMeshView()
{
	m_bLButton = false;

	bool tf  = OpenMesh::IO::read_mesh(m_mesh, "kikyou_R_UV.obj");
	fprintf(stderr, "read Mesg %d\n", tf);

	m_mesh.request_face_normals();
	m_mesh.update_normals();
	m_mesh.request_vertex_normals();
	m_mesh.update_normals();

}

CMyFirstOpenMeshView::~CMyFirstOpenMeshView()
{
}

BOOL CMyFirstOpenMeshView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMyFirstOpenMeshView drawing

void CMyFirstOpenMeshView::OnDraw(CDC* /*pDC*/)
{
	CMyFirstOpenMeshDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_ogl.SetBgColor( EVec4f( 0, 0, 0, 0 ));
	m_ogl.OnDrawBegin();


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(10, 0, 0);
	glEnd();


	auto fIt  = m_mesh.faces_begin();
	auto fEnd = m_mesh.faces_end();
	/*
	glBegin(GL_TRIANGLES);
	for (; fIt != fEnd; ++fIt)
	{
		auto fvIt = m_mesh.cfv_iter(*fIt);
		glVertex3fv( m_mesh.point(*fvIt).data() );
		++fvIt;
		glVertex3fv( m_mesh.point(*fvIt).data());
		++fvIt;
		glVertex3fv( m_mesh.point(*fvIt).data());
	}
	glEnd();
	*/

	glBegin(GL_TRIANGLES);
	for (; fIt != fEnd; ++fIt)
	{
		glNormal3fv(m_mesh.normal(*fIt).data());
		auto fvIt = m_mesh.cfv_iter(*fIt);
		glNormal3fv(m_mesh.normal(*fvIt).data() ); glVertex3fv(m_mesh.point(*fvIt).data()); ++fvIt;
		glNormal3fv(m_mesh.normal(*fvIt).data() ); glVertex3fv(m_mesh.point(*fvIt).data()); ++fvIt;
		glNormal3fv(m_mesh.normal(*fvIt).data() ); glVertex3fv(m_mesh.point(*fvIt).data());

		m_mesh.texcoord2D(*fvIt).data();
	}
	glEnd();


	m_ogl.OnDrawEnd();



}


// CMyFirstOpenMeshView printing

BOOL CMyFirstOpenMeshView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFirstOpenMeshView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFirstOpenMeshView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMyFirstOpenMeshView diagnostics

#ifdef _DEBUG
void CMyFirstOpenMeshView::AssertValid() const
{
	CView::AssertValid();
}

void CMyFirstOpenMeshView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFirstOpenMeshDoc* CMyFirstOpenMeshView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFirstOpenMeshDoc)));
	return (CMyFirstOpenMeshDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyFirstOpenMeshView message handlers


void CMyFirstOpenMeshView::OnDestroy()
{
	CView::OnDestroy();
	m_ogl.OnDestroy();
	// TODO: Add your message handler code here
}






int CMyFirstOpenMeshView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_ogl.OnCreate(this);
	return 0;
}


void CMyFirstOpenMeshView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_ogl.OnSize(cx, cy);
}


BOOL CMyFirstOpenMeshView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


BOOL CMyFirstOpenMeshView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}






void CMyFirstOpenMeshView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bLButton)
	{
		m_ogl.MouseMove(point);
		m_ogl.Redraw();
	}
}


void CMyFirstOpenMeshView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLButton = false;
	m_ogl.BtnUp();
}


void CMyFirstOpenMeshView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLButton = true;
	m_ogl.BtnDown_Rot(point);
}
