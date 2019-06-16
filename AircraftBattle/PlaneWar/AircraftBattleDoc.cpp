
// AircraftBattleDoc.cpp : CAircraftBattleDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "AircraftBattle.h"
#endif

#include "AircraftBattleDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAircraftBattleDoc

IMPLEMENT_DYNCREATE(CAircraftBattleDoc, CDocument)

BEGIN_MESSAGE_MAP(CAircraftBattleDoc, CDocument)
END_MESSAGE_MAP()


// CAircraftBattleDoc ����/����

CAircraftBattleDoc::CAircraftBattleDoc()
{
	// TODO: �ڴ����һ���Թ������
	CString fileName("data.txt");
	CFile file(fileName, CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	ar >> maxScore;
	ar.Flush();
	ar.Close();
	file.Close();
}

CAircraftBattleDoc::~CAircraftBattleDoc()
{
}

BOOL CAircraftBattleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

// CAircraftBattleDoc ���л�

void CAircraftBattleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CAircraftBattleDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CAircraftBattleDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CAircraftBattleDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CAircraftBattleDoc ���

#ifdef _DEBUG
void CAircraftBattleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAircraftBattleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAircraftBattleDoc ����

int CAircraftBattleDoc::getMaxScore() const {
	return maxScore;
}

void CAircraftBattleDoc::setMaxScore(const int score) {
	maxScore = score;
	CString fileName("data.txt");
	CFile file(fileName, CFile::modeCreate | CFile::modeWrite); 
	CArchive ar(&file, CArchive::store);
	ar << maxScore;
	ar.Flush();
	ar.Close();
	file.Close();
}