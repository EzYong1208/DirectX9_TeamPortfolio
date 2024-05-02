#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Armor_Up : public CItem
{
public:
	typedef enum Armor_Up_Type
	{
		ARMORUP_BRONZE,
		ARMORUP_IRON,
		ARMORUP_GOLD,
		ARMORUP_EPIC,
		ARMORUP_END
	}ARMORUP;

private:
	explicit CItem_Armor_Up(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Armor_Up() = default;

public:
	virtual HRESULT				NativeConstruct();

public:
	virtual HRESULT				Activate(CGameObject* _pTarget);

public:
	virtual HRESULT				Save_Data(HANDLE _hFile);
	virtual HRESULT				Load_Data(HANDLE _hFile);

private:
	ARMORUP						m_ArmorUpType;

public:
	static CItem_Armor_Up*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void				Free() override;
};

END