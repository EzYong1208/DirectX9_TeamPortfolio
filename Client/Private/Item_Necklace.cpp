#include "stdafx.h"
#include "..\Public\Item_Necklace.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Necklace::CItem_Necklace(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Necklace::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_NECK;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Necklace";

	//m_tagItemDesc.iItem_Texture_Index = 126;		//	126 ~ 129

	_uint iNecklaceType = rand() % 4;

	switch (iNecklaceType)
	{
	case NECKLACE_SILVER:
		m_tagItemDesc.fHealth_Point = 3.f;
		m_tagItemDesc.iItem_Texture_Index = 118;	//	118 119
		m_tagItemDesc.iPrice = 600;
		break;

	case NECKLACE_GOLD:
		m_tagItemDesc.fHealth_Point = 5.f;
		m_tagItemDesc.iItem_Texture_Index = 120;	//	120 121
		m_tagItemDesc.iPrice = 700;
		break;

	case NECKLACE_EPIC:
		m_tagItemDesc.fHealth_Point = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 122;	//	122 123
		m_tagItemDesc.iPrice = 800;
		break;

	case NECKLACE_LEGEND:
		m_tagItemDesc.fHealth_Point = 10.f;
		m_tagItemDesc.iItem_Texture_Index = 124;	//	124 125
		m_tagItemDesc.iPrice = 900;
		break;
	}

	return S_OK;
}

HRESULT CItem_Necklace::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Necklace::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Necklace::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Necklace * CItem_Necklace::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Necklace*		pInstance = new CItem_Necklace(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Necklace");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Necklace::Free()
{
	__super::Free();
}
