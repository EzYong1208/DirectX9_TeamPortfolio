#include "stdafx.h"
#include "..\Public\Item_Shield.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Shield::CItem_Shield(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Shield::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_LEFT;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Shield";

	//m_tagItemDesc.fHealth_Point = 15.f;
	//	앞에서 보이는 이미지
	//m_tagItemDesc.iItem_Texture_Index = 87;		//	87 ~ 96
	//	플레이어 시점에서 보이는 이미지
	//m_tagItemDesc.iItem_Texture_Index = 88;

	_uint iShieldType = rand() % 5;

	switch (iShieldType)
	{
	case SHIELD_IRON:
		m_tagItemDesc.fHealth_Point = 5.f;
		m_tagItemDesc.iItem_Texture_Index = 87;		//	87 88
		m_tagItemDesc.iPrice = 150;
		break;

	case SHIELD_STEEL:
		m_tagItemDesc.fHealth_Point = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 89;		//	89 90
		m_tagItemDesc.iPrice = 250;
		break;

	case SHIELD_GOLD:
		m_tagItemDesc.fHealth_Point = 10.f;
		m_tagItemDesc.iItem_Texture_Index = 91;		//	91 92
		m_tagItemDesc.iPrice = 350;
		break;

	case SHIELD_EPIC:
		m_tagItemDesc.fHealth_Point = 13.f;
		m_tagItemDesc.iItem_Texture_Index = 93;		//	93 94
		m_tagItemDesc.iPrice = 450;
		break;

	case SHIELD_LEGEND:
		m_tagItemDesc.fHealth_Point = 15.f;
		m_tagItemDesc.iItem_Texture_Index = 95;		//	95 96
		m_tagItemDesc.iPrice = 550;
		break;
	}

	return S_OK;
}

HRESULT CItem_Shield::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Shield::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Shield::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Shield * CItem_Shield::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Shield*		pInstance = new CItem_Shield(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Shield");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Shield::Free()
{
	__super::Free();
}
