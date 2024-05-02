#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_LegendWand : public CItem
{
private:
	explicit CItem_LegendWand(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_LegendWand() = default;

public:
	virtual HRESULT				NativeConstruct();

public:
	virtual HRESULT				Activate(CGameObject* _pTarget);

public:
	virtual HRESULT				Save_Data(HANDLE _hFile);
	virtual HRESULT				Load_Data(HANDLE _hFile);

public:
	static CItem_LegendWand*	Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void				Free() override;
};

END