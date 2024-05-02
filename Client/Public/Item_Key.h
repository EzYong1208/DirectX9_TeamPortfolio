#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Key : public CItem
{
private:
	explicit CItem_Key(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Key() = default;

public:
	virtual	HRESULT			NativeConstruct();

public:
	virtual	HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual	HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

public:
	static	CItem_Key*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END