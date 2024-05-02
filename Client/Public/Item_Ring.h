#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Ring : public CItem
{
public:
	typedef enum Ring_Type
	{
		RING_SILVER,
		RING_GOLD,
		RING_EPIC,
		RING_LEGEND,
		RING_END
	}RING;

private:
	explicit CItem_Ring(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Ring() = default;

public:
	virtual HRESULT				NativeConstruct();

public:
	virtual HRESULT				Activate(CGameObject* _pTarget);

public:
	virtual HRESULT				Save_Data(HANDLE _hFile);
	virtual HRESULT				Load_Data(HANDLE _hFile);

private:
	RING						m_RingType;

public:
	static CItem_Ring*			Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void				Free() override;
};

END