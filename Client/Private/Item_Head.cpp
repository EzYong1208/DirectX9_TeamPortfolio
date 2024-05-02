#include "stdafx.h"
#include "..\Public\Item_Head.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Head::CItem_Head(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Head::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_HEAD;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Head";

	//m_tagItemDesc.fHealth_Point = 5.f;
	//m_tagItemDesc.iItem_Texture_Index = 105;		//	105 ~ 109

	_uint iHeadType = rand() % 5;

	switch (iHeadType)
	{
	case HEAD_BRONZE:
		m_tagItemDesc.fHealth_Point = 3.f;
		m_tagItemDesc.iItem_Texture_Index = 105;
		m_tagItemDesc.iPrice = 150;
		break;

	case HEAD_IRON:
		m_tagItemDesc.fHealth_Point = 5.f;
		m_tagItemDesc.iItem_Texture_Index = 106;
		m_tagItemDesc.iPrice = 250;
		break;

	case HEAD_GOLD:
		m_tagItemDesc.fHealth_Point = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 107;
		m_tagItemDesc.iPrice = 350;
		break;

	case HEAD_EPIC:
		m_tagItemDesc.fHealth_Point = 10.f;
		m_tagItemDesc.iItem_Texture_Index = 108;
		m_tagItemDesc.iPrice = 450;
		break;

	case HEAD_LEGEND:
		m_tagItemDesc.fHealth_Point = 3.f;
		m_tagItemDesc.iItem_Texture_Index = 109;
		m_tagItemDesc.iPrice = 150;
		break;
	}

	return S_OK;
}

HRESULT CItem_Head::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Head::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Head::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Head * CItem_Head::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Head*		pInstance = new CItem_Head(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Head");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Head::Free()
{
	__super::Free();
}
