#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Mase : public CItem
{
public:
	typedef enum Mase_Type
	{
		MASE_IRON,
		MASE_STEEL,
		MASE_EPIC,
		MASE_END
	}MASE;

private:
	explicit CItem_Mase(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Mase() = default;

public:
	virtual HRESULT			NativeConstruct();

public:
	virtual HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

private:
	MASE					m_MaseType;

public:
	static CItem_Mase*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END