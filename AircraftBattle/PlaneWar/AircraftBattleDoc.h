
// AircraftBattleDoc.h : CAircraftBattleDoc ��Ľӿ�
//


#pragma once


class CAircraftBattleDoc : public CDocument
{
protected: // �������л�����
	CAircraftBattleDoc();
	DECLARE_DYNCREATE(CAircraftBattleDoc)

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CAircraftBattleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int maxScore;

public:
	int getMaxScore() const;
	void setMaxScore(const int score);

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
