#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Sword : public CItem
{
public:
	typedef enum Sword_Type
	{
		SWORD_GOLD,
		SWORD_EPIC,
		SWORD_END
	}SWORD;

private:
	explicit CItem_Sword(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Sword() = default;

public:
	virtual HRESULT			NativeConstruct();

public:
	virtual HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

private:
	SWORD					m_SwordType;

public:
	static CItem_Sword*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END