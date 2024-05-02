#include "stdafx.h"
#include "..\Public\Item_Ring.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Ring::CItem_Ring(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Ring::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_RING;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Ring";

	//m_tagItemDesc.iItem_Texture_Index = 118;		//	118 ~ 125

	_uint iRingType = rand() % 4;

	switch (iRingType)
	{
	case RING_SILVER:
		m_tagItemDesc.fHealth_Point = 3.f;
		m_tagItemDesc.iItem_Texture_Index = 126;
		m_tagItemDesc.iPrice = 600;
		break;

	case RING_GOLD:
		m_tagItemDesc.fHealth_Point = 5.f;
		m_tagItemDesc.iItem_Texture_Index = 127;
		m_tagItemDesc.iPrice = 700;
		break;

	case RING_EPIC:
		m_tagItemDesc.fHealth_Point = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 128;
		m_tagItemDesc.iPrice = 800;
		break;

	case RING_LEGEND:
		m_tagItemDesc.fHealth_Point = 10.f;
		m_tagItemDesc.iItem_Texture_Index = 129;
		m_tagItemDesc.iPrice = 900;
		break;
	}

	return S_OK;
}

HRESULT CItem_Ring::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Ring::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Ring::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Ring * CItem_Ring::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Ring*		pInstance = new CItem_Ring(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Ring");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Ring::Free()
{
	__super::Free();
}
