#include "stdafx.h"
#include "..\Public\Item_Coin.h"
#include "Texture.h"
#include "Item_BoundingBox.h"

CItem_Coin::CItem_Coin(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CItem(_pGraphic_Device)
{
}

HRESULT CItem_Coin::NativeConstruct()
{
	m_tagItemDesc.eItem_Type = CItem::ITEMTYPE_ETC;
	m_tagItemDesc.eWeapon_Type = CItem::WEAPONTYPE_NOTWEAPON;
	m_tagItemDesc.pItem_Name = L"Item_Coin";
	//m_tagItemDesc.iItem_Texture_Index = 144;		//	144 ~ 151

	_uint iCoinType = rand() % 8;

	switch (iCoinType)
	{
	case COIN_ONE:
		m_tagItemDesc.iItem_Texture_Index = 144;
		m_tagItemDesc.iGold = 100;
		break;

	case COIN_SIX:
		m_tagItemDesc.iItem_Texture_Index = 145;
		m_tagItemDesc.iGold = 600;
		break;

	case COIN_CANDLE:
		m_tagItemDesc.iItem_Texture_Index = 146;
		m_tagItemDesc.iGold = 800;
		break;

	case COIN_EMERALD:
		m_tagItemDesc.iItem_Texture_Index = 147;
		m_tagItemDesc.iGold = 1000;
		break;

	case COIN_RUBY:
		m_tagItemDesc.iItem_Texture_Index = 148;
		m_tagItemDesc.iGold = 1200;
		break;

	case COIN_DIAMOND:
		m_tagItemDesc.iItem_Texture_Index = 149;
		m_tagItemDesc.iGold = 2000;
		break;

	case COIN_GOLD:
		m_tagItemDesc.iItem_Texture_Index = 150;
		m_tagItemDesc.iGold = 800;
		break;

	case COIN_BIGGOLD:
		m_tagItemDesc.iItem_Texture_Index = 151;
		m_tagItemDesc.iGold = 1600;
		break;
	}

	return S_OK;
}

HRESULT CItem_Coin::Activate(CGameObject * _pTarget)
{
	return S_OK;
}

HRESULT CItem_Coin::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CItem_Coin::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CItem_Coin * CItem_Coin::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItem_Coin*		pInstance = new CItem_Coin(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CItem_Coin");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItem_Coin::Free()
{
	__super::Free();
}
