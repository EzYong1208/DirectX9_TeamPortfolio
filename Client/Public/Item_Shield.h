#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Shield : public CItem
{
public:
	typedef enum Shield_Type
	{
		SHIELD_IRON,
		SHIELD_STEEL,
		SHIELD_GOLD,
		SHIELD_EPIC,
		SHIELD_LEGEND,
		SHIELD_END
	}SHIELD;

private:
	explicit CItem_Shield(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Shield() = default;

public:
	virtual HRESULT			NativeConstruct();

public:
	virtual HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

private:
	SHIELD					m_ShieldType;

public:
	static CItem_Shield*	Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END