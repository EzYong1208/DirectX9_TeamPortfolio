#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Book : public CItem
{
public:
	typedef enum Book_Type
	{
		BOOK_RED,
		BOOK_GREEN,
		BOOK_YELLOW,
		BOOK_END
	}BOOK;

private:
	explicit CItem_Book(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Book() = default;

public:
	virtual HRESULT			NativeConstruct();

public:
	virtual HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

private:
	BOOK					m_BookType;

public:
	static CItem_Book*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END