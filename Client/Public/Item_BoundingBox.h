#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "Item.h"

BEGIN(Engine)
class CRenderer;
class CTexture;
class CVIBuffer_Rect;
class CCollider;
class CItemSlot;
class CShader;
class CLightning;
class CState_Machine;
END

BEGIN(Client)

class CItem_BoundingBox : public CGameObject
{
public:
	typedef enum TypeItem
	{
		TYPEITEM_USEABLE,
		TYPEITEM_RIGHT,
		TYPEITEM_LEFT,
		TYPEITEM_ARMOR,
		TYPEITEM_ACCESSORY,
		TYPEITEM_ETC,
		TYPEITEM_END
	}TYPEITEM;

	typedef enum Item
	{
		ITEM_BOMB, ITEM_FOOD, ITEM_POTION,
		ITEM_BOW, ITEM_DAGGER, ITEM_MASE, ITEM_SWORD, ITEM_WAND,
		ITEM_LANTERN, ITEM_SHIELD,
		ITEM_ARMOR_DOWN, ITEM_ARMOR_UP, ITEM_HEAD,
		ITEM_NECKLACE, ITEM_RING,
		ITEM_BONE, ITEM_BOOK, ITEM_COIN, ITEM_REDORB,
		ITEM_END
	}ITEM;

	typedef struct tagBoundingBoxDescription
	{
		_int		iIndex = 0;
		_float3		vPos;
	}BOUNDINGBOXDESC;

public:
	explicit CItem_BoundingBox(LPDIRECT3DDEVICE9 _pGraphicDevice);
	explicit CItem_BoundingBox(const CItem_BoundingBox& rhs);
	virtual ~CItem_BoundingBox() = default;

public:
	virtual HRESULT					NativeConstruct_Prototype();
	virtual HRESULT					NativeConstruct(void* pArg);
	virtual _int					Tick(_float fTimeDelta);
	virtual _int					LateTick(_float fTimeDelta);
	virtual HRESULT					Render();

public:
	HRESULT							SetUp_Components();
	HRESULT							SetUp_OnTerrain();

private:
	void							To_Player_Aniamtion(_float _fTimeDelta);
	_bool							m_bAnimateCVaild = false;

public:
	_bool							Collision_Check_Player();
	_bool							Is_Picked();

public:
	virtual HRESULT					Save_Data(HANDLE _hFile);
	virtual HRESULT					Load_Data(HANDLE _hFile);

protected:
	CRenderer*						m_pRendererCom = nullptr;
	CVIBuffer_Rect*					m_pVIBufferCom = nullptr;
	CTexture*						m_pTextureCom = nullptr;
	CTransform*						m_pTransformCom = nullptr;
	CItemSlot*						m_pItemSlotCom = nullptr;
	_uint							m_iTexture = 0;
	vector<CCollider*>				m_Colliders;
	CItem::ITEMDESC					m_ItemDesc;
	CItem*							m_pItem = nullptr;
	BOUNDINGBOXDESC					m_BoxDesc;
	_bool							m_bCoin = false;
	CShader*						m_pShader = nullptr;
	CLightning*						m_pLightning = nullptr;
	CState_Machine*					m_pState_MachineCom = nullptr;

private:
	_bool							m_bOnce = false;
	_float							m_fAlpha = 0.f;
	_float3							m_vStartPos = _float3(0.f, 0.f, 0.f);
	_float3							m_vEndPos = _float3(0.f, 0.f, 0.f);

public:
	HRESULT							Set_ItemTexture();
	HRESULT							Create_Useable();
	HRESULT							Create_Right();
	HRESULT							Create_Left();
	HRESULT							Create_Armor();
	HRESULT							Create_Accessory();
	HRESULT							Create_Etc();

	HRESULT							Create_Bow();
	HRESULT							Create_Dagger();
	HRESULT							Create_Lantern();
	HRESULT							Create_Coin();
	HRESULT							Create_Wand();
	HRESULT							Create_Sword();

	HRESULT							Create_LegendSword();
	HRESULT							Create_LegendMase();
	HRESULT							Create_LegendWand();
	HRESULT							Create_LegendBow();

	HRESULT							Create_Key();

public:
	static CItem_BoundingBox*		Create(LPDIRECT3DDEVICE9 _pGraphicDevice);
	virtual CGameObject*			Clone(void* pArg);
	virtual	void					Free() override;
};

END