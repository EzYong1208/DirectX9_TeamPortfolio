#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CItemSlot;
class CItem;
END

BEGIN(Client)

class CShop : public CGameObject
{
public:
	typedef enum eShop
	{
		SHOP_BUY,
		SHOP_SELL,
		SHOP_END
	}SHOP;

	typedef enum eShopItemType
	{
		SHOPITEM_DAGGER,
		SHOPITEM_MASE,
		SHOPITEM_BOW,
		SHOPITEM_HEAD,
		SHOPITEM_ARMOR_UP,
		SHOPITEM_ARMOR_DOWN,
		SHOPITEM_FOOD,
		SHOPITEM_POTION,
		SHOPITEM_END
	}SHOPITEMTYPE;

	typedef enum eEpicShopItemType
	{
		EPICSHOPITEM_SWORD,
		EPICSHOPITEM_WAND,
		EPICSHOPITEM_SHIELD,
		EPICSHOPITEM_NECK,
		EPICSHOPITEM_RING,
		EPICSHOPITEM_ETC,
		EPICSHOPITEM_FOOD,
		EPICSHOPITEM_POTION,
		EPICSHOPITEM_END
	}EPICSHOPITEMTYPE;

private:
	explicit CShop(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CShop(const CShop& rhs);
	virtual ~CShop() = default;

public:
	virtual HRESULT			NativeConstruct_Prototype() override;

public:
	HRESULT					Gacha();
	HRESULT					Shop(SHOP _eShop);
	HRESULT					EpicShop(SHOP _eShop);

	HRESULT					ShopBuy(SHOPITEMTYPE _eShopItemType);
	HRESULT					EpicShopBuy(EPICSHOPITEMTYPE _eEpicItemType);
	HRESULT					Sell(_uint _iIndex);

public:
	HRESULT					SetUp_Components();

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

public:
	CItemSlot*				m_pItemSlotCom = nullptr;
	CItem*					m_pItem = nullptr;
	SHOP					m_eShop;
	SHOPITEMTYPE			m_eShopItemType;
	EPICSHOPITEMTYPE		m_eEpicShopItemType;
	_int					m_iPrice = 0;

public:
	static CShop*			Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual	CGameObject*	Clone(void* _pArg);
	virtual	void			Free() override;
};

END