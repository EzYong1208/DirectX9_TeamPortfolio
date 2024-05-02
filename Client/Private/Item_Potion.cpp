#include "stdafx.h"
#include "..\Public\Item_Potion.h"

CItem_Potion::CItem_Potion(LPDIRECT3DDEVICE9 _pGraphicDevice)
	: CItem(_pGraphicDevice)
{
}

HRESULT CItem_Potion::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_USEABLE;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Potion";

	//m_tagItemDesc.iItem_Texture_Index = 131;		//	131 ~ 137
	_uint iPotionType = rand() % 7;

	switch (iPotionType)
	{
	case POTION_ORANGE:
		m_tagItemDesc.fHealth_Point = 10.f;
		m_tagItemDesc.iItem_Texture_Index = 131;
		m_tagItemDesc.iPrice = 50;
		break;

	case POTION_RED:
		m_tagItemDesc.fHealth_Point = 15.f;
		m_tagItemDesc.iItem_Texture_Index = 132;
		m_tagItemDesc.iPrice = 60;
		break;

	case POTION_BLUE:
		m_tagItemDesc.fHealth_Point = 20.f;
		m_tagItemDesc.iItem_Texture_Index = 133;
		m_tagItemDesc.iPrice = 70;
		break;

	case POTION_GREEN:
		m_tagItemDesc.fHealth_Point = 25.f;
		m_tagItemDesc.iItem_Texture_Index = 134;
		m_tagItemDesc.iPrice = 80;
		break;

	case POTION_PURPLE:
		m_tagItemDesc.fHealth_Point = 30.f;
		m_tagItemDesc.iItem_Texture_Index = 135;
		m_tagItemDesc.iPrice = 90;
		break;

	case POTION_BLACK:
		m_tagItemDesc.fHealth_Point = 35.f;
		m_tagItemDesc.iItem_Texture_Index = 136;
		m_tagItemDesc.iPrice = 100;
		break;

	case POTION_YELLOW:
		m_tagItemDesc.fHealth_Point = 40.f;
		m_tagItemDesc.iItem_Texture_Index = 137;
		m_tagItemDesc.iPrice = 110;
		break;
	}

	return S_OK;
}

HRESULT CItem_Potion::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Potion::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Potion::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Potion * CItem_Potion::Create(LPDIRECT3DDEVICE9 _pGraphicDevice)
{
	CItem_Potion*		pInstance = new CItem_Potion(_pGraphicDevice);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Potion");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Potion::Free()
{
	__super::Free();
}