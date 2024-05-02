#include "stdafx.h"
#include "..\Public\Item_Book.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Book::CItem_Book(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Book::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_ETC;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Book";
	//m_tagItemDesc.iItem_Texture_Index = 152;		//	152 ~ 154

	_uint	iBookType = rand() % 3;

	switch (iBookType)
	{
	case BOOK_RED:
		m_tagItemDesc.iItem_Texture_Index = 152;
		m_tagItemDesc.iPrice = 30;
		break;

	case BOOK_GREEN:
		m_tagItemDesc.iItem_Texture_Index = 153;
		m_tagItemDesc.iPrice = 30;
		break;

	case BOOK_YELLOW:
		m_tagItemDesc.iItem_Texture_Index = 154;
		m_tagItemDesc.iPrice = 30;
		break;
	}

	return S_OK;
}

HRESULT CItem_Book::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Book::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Book::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Book * CItem_Book::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Book*		pInstance = new CItem_Book(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Book");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Book::Free()
{
	__super::Free();
}
