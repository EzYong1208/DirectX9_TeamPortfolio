#include "stdafx.h"
#include "..\Public\Shop.h"
#include "ItemSlot.h"
#include "Item_Bomb.h"
#include "Item_Food.h"
#include "Item_Potion.h"
#include "Item_Bow.h"
#include "Item_Dagger.h"
#include "Item_Mase.h"
#include "Item_Sword.h"
#include "Item_Wand.h"
#include "Item_Lantern.h"
#include "Item_Shield.h"
#include "Item_Armor_Down.h"
#include "Item_Armor_Up.h"
#include "Item_Head.h"
#include "Item_Necklace.h"
#include "Item_Ring.h"
#include "Item_Bone.h"
#include "Item_Book.h"
#include "Item_Coin.h"
#include "Item_RedOrb.h"
#include "Item.h"
#include "GameInstance.h"
#include "UI_Conversation.h"

CShop::CShop(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: CGameObject(_pGraphic_Device)

{
}

CShop::CShop(const CShop & rhs)
	: CGameObject(rhs)
{
}

HRESULT CShop::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	SetUp_Components();

	return S_OK;
}

HRESULT CShop::Gacha()
{
	_int Cash = m_pItemSlotCom->Get_Gold();

	if (3000 <= Cash)
	{
		_uint		iResult = rand() % 10;

		//	»À, Ã¥, À½½Ä, ·¹µå¿Àºê

		if (0 <= iResult &&
			4 >= iResult)
		{
			m_pItem = CItem_Bone::Create(m_pGraphic_Device);
		}
		else if (5 == iResult
			|| 6 == iResult)
		{
			m_pItem = CItem_Book::Create(m_pGraphic_Device);
		}
		else if (7 == iResult
			|| 8 == iResult)
		{
			m_pItem = CItem_Food::Create(m_pGraphic_Device);
		}
		else if (9 == iResult)
		{
			m_pItem = CItem_RedOrb::Create(m_pGraphic_Device);
		}

		CUI_Conversation* UI_Conversation = dynamic_cast<CUI_Conversation*>
			(CGameInstance::GetInstance()->Get_UI(
				LEVEL_GAMEPLAY, TEXT("UI_Conversation")));
		UI_Conversation->Set_Conversation_Text(
			TEXT("3000°ñµå¸¦ ¸Û¸ÛÀÌ¿¡°Ô Áá´Ù."),
			TEXT("¸Û¸ÛÀÌÀÇ º¸¹°À» ¹Þ¾Ò´Ù."),
			TEXT("¸Û¸ÛÀÌÀÇ ±âºÐÀÌ ÁÁ¾Æº¸ÀÎ´Ù."));
		UI_Conversation->Set_UI_On();

		m_pItemSlotCom->Push_Item(m_pItem, CItemSlot::SLOTTYPE_BACKPACK);
		m_pItemSlotCom->Set_Gold(-3000);
	}

	if (3000 > Cash)
	{
		CUI_Conversation* UI_Conversation = dynamic_cast<CUI_Conversation*>
			(CGameInstance::GetInstance()->Get_UI(
				LEVEL_GAMEPLAY, TEXT("UI_Conversation")));
		UI_Conversation->Set_Conversation_Text(
			TEXT("°ñµå°¡ ºÎÁ·ÇÏ´Ù."),
			TEXT("¸Û¸ÛÀÌÀÇ ±âºÐÀÌ ³ªºüº¸ÀÎ´Ù."),
			TEXT(""));
		UI_Conversation->Set_UI_On();
	}

	return S_OK;
}

HRESULT CShop::Shop(SHOP _eShop)
{
	_int	iSelect = _eShop;

	switch (iSelect)
	{
	case SHOP_BUY:
		ShopBuy(m_eShopItemType);
		break;

	case SHOP_SELL:
		Sell(0);
		break;

	case SHOP_END:
		break;
	}


	return S_OK;
}

HRESULT CShop::EpicShop(SHOP _eShop)
{
	_int	iSelect = _eShop;

	switch (iSelect)
	{
	case SHOP_BUY:
		EpicShopBuy(m_eEpicShopItemType);
		break;

	case SHOP_SELL:
		Sell(0);
		break;

	case SHOP_END:
		break;
	}


	return S_OK;
}

HRESULT CShop::ShopBuy(SHOPITEMTYPE _eShopItemType)
{
	m_eShopItemType = _eShopItemType;

	switch (m_eShopItemType)
	{
	case SHOPITEM_DAGGER:
		m_pItem = CItem_Dagger::Create(m_pGraphic_Device);
		m_iPrice = 600;
		break;

	case SHOPITEM_MASE:
		m_pItem = CItem_Mase::Create(m_pGraphic_Device);
		m_iPrice = 800;
		break;

	case SHOPITEM_BOW:
		m_pItem = CItem_Bow::Create(m_pGraphic_Device);
		m_iPrice = 750;
		break;

	case SHOPITEM_HEAD:
		m_pItem = CItem_Head::Create(m_pGraphic_Device);
		m_iPrice = 500;
		break;

	case SHOPITEM_ARMOR_UP:
		m_pItem = CItem_Armor_Up::Create(m_pGraphic_Device);
		m_iPrice = 500;
		break;

	case SHOPITEM_ARMOR_DOWN:
		m_pItem = CItem_Armor_Down::Create(m_pGraphic_Device);
		m_iPrice = 500;
		break;

	case SHOPITEM_FOOD:
		m_pItem = CItem_Food::Create(m_pGraphic_Device);
		m_iPrice = 50;
		break;

	case SHOPITEM_POTION:
		m_pItem = CItem_Potion::Create(m_pGraphic_Device);
		m_iPrice = 120;
		break;

	case SHOPITEM_END:
		break;
	}

	_int	iCash = m_pItemSlotCom->Get_Gold();

	if (m_iPrice <= iCash)
	{
		m_pItemSlotCom->Push_Item(m_pItem, CItemSlot::SLOTTYPE_BACKPACK);
		m_pItemSlotCom->Set_Gold(-m_iPrice);
	}
	else
	{
		//µ· ¾øÀ¸¸é?
	}


	return S_OK;
}

HRESULT CShop::EpicShopBuy(EPICSHOPITEMTYPE _eEpicItemType)
{
	m_eEpicShopItemType = _eEpicItemType;

	switch (m_eEpicShopItemType)
	{
	case EPICSHOPITEM_SWORD:
		m_pItem = CItem_Sword::Create(m_pGraphic_Device);
		m_iPrice = 1000;
		break;

	case EPICSHOPITEM_WAND:
		m_pItem = CItem_Wand::Create(m_pGraphic_Device);
		m_iPrice = 800;
		break;

	case EPICSHOPITEM_SHIELD:
		m_pItem = CItem_Shield::Create(m_pGraphic_Device);
		m_iPrice = 800;
		break;

	case EPICSHOPITEM_NECK:
		m_pItem = CItem_Necklace::Create(m_pGraphic_Device);
		m_iPrice = 1200;
		break;

	case EPICSHOPITEM_RING:
		m_pItem = CItem_Ring::Create(m_pGraphic_Device);
		m_iPrice = 1200;
		break;

	case EPICSHOPITEM_ETC:
		m_pItem = CItem_Bone::Create(m_pGraphic_Device);
		m_iPrice = 77;
		break;

	case EPICSHOPITEM_FOOD:
		m_pItem = CItem_Food::Create(m_pGraphic_Device);
		m_iPrice = 300;
		break;

	case EPICSHOPITEM_POTION:
		m_pItem = CItem_Potion::Create(m_pGraphic_Device);
		m_iPrice = 500;
		break;

	case EPICSHOPITEM_END:
		break;

	}

	_int	iCash = m_pItemSlotCom->Get_Gold();

	if (m_iPrice <= iCash)
	{
		m_pItemSlotCom->Push_Item(m_pItem, CItemSlot::SLOTTYPE_BACKPACK);
		m_pItemSlotCom->Set_Gold(-m_iPrice);
	}
	else
	{
		//µ· ¾øÀ¸¸é?
	}

	return S_OK;
}

HRESULT CShop::Sell(_uint _iIndex)
{
	_int iPrice = m_pItemSlotCom->Get_Item(CItemSlot::SLOTTYPE_BACKPACK, _iIndex)->Get_ItemDesc().iPrice;
	m_pItemSlotCom->Remove_Item(CItemSlot::SLOTTYPE_BACKPACK, _iIndex);
	m_pItemSlotCom->Set_Gold(iPrice);

	return S_OK;
}

HRESULT CShop::SetUp_Components()
{
	//	For.ItemSlotCom
	if (FAILED(__super::Add_Component(
		LEVEL_GAMEPLAY,
		L"Prototype_Component_ItemSlot",
		L"Com_ItemSlot",
		(CComponent**)&m_pItemSlotCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CShop::Save_Data(HANDLE _hFile)
{
	return S_OK;
}

HRESULT CShop::Load_Data(HANDLE _hFile)
{
	return S_OK;
}

CShop * CShop::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CShop* pInstance = new CShop(_pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating CShop")
			Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CShop::Clone(void * _pArg)
{
	AddRef();
	return this;
}

void CShop::Free()
{
	__super::Free();

	Safe_Release(m_pItemSlotCom);
}
