#include "stdafx.h"
#include "..\Public\Item_Food.h"

CItem_Food::CItem_Food(LPDIRECT3DDEVICE9 _pGraphicDevice)
	: CItem(_pGraphicDevice)
{
}

HRESULT CItem_Food::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_USEABLE;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Food";

	//m_tagItemDesc.iItem_Texture_Index = 138;		//	138 ~ 143

	_uint iArmorUpType = rand() % 6;

	switch (iArmorUpType)
	{
	case FOOD_BREAD:
		m_tagItemDesc.fHealth_Point = 4.f;
		m_tagItemDesc.iItem_Texture_Index = 138;
		m_tagItemDesc.iPrice = 10;
		break;

	case FOOD_APPLE:
		m_tagItemDesc.fHealth_Point = 8.f;
		m_tagItemDesc.iItem_Texture_Index = 139;
		m_tagItemDesc.iPrice = 15;
		break;

	case FOOD_CHEESE:
		m_tagItemDesc.fHealth_Point = 12.f;
		m_tagItemDesc.iItem_Texture_Index = 140;
		m_tagItemDesc.iPrice = 20;
		break;

	case FOOD_MEAT:
		m_tagItemDesc.fHealth_Point = 16.f;
		m_tagItemDesc.iItem_Texture_Index = 141;
		m_tagItemDesc.iPrice = 25;
		break;

	case FOOD_STEAK:
		m_tagItemDesc.fHealth_Point = 20.f;
		m_tagItemDesc.iItem_Texture_Index = 142;
		m_tagItemDesc.iPrice = 30;
		break;

	case FOOD_ALE:
		m_tagItemDesc.fHealth_Point = 15.f;
		m_tagItemDesc.iItem_Texture_Index = 143;
		m_tagItemDesc.iPrice = 35;
		break;
	}

	return S_OK;
}

HRESULT CItem_Food::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Food::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Food::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Food * CItem_Food::Create(LPDIRECT3DDEVICE9 _pGraphicDevice)
{
	CItem_Food*		pInstance = new CItem_Food(_pGraphicDevice);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Food");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Food::Free()
{
	__super::Free();
}