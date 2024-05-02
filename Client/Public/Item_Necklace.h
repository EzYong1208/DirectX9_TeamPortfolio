#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Necklace : public CItem
{
public:
	typedef enum Necklace_Type
	{
		NECKLACE_SILVER,
		NECKLACE_GOLD,
		NECKLACE_EPIC,
		NECKLACE_LEGEND,
		NECKLACE_END
	}NECKLACE;

private:
	explicit CItem_Necklace(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Necklace() = default;

public:
	virtual HRESULT				NativeConstruct();

public:
	virtual HRESULT				Activate(CGameObject* _pTarget);

public:
	virtual HRESULT				Save_Data(HANDLE _hFile);
	virtual HRESULT				Load_Data(HANDLE _hFile);

private:
	NECKLACE					m_NecklaceType;

public:
	static CItem_Necklace*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void				Free() override;
};

END