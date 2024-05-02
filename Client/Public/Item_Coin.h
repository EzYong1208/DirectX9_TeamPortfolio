#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Coin : public CItem
{
public:
	typedef enum Coin_Type
	{
		COIN_ONE,
		COIN_SIX,
		COIN_CANDLE,
		COIN_EMERALD,
		COIN_RUBY,
		COIN_DIAMOND,
		COIN_GOLD,
		COIN_BIGGOLD,
		COIN_END
	}COIN;

private:
	explicit CItem_Coin(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CItem_Coin() = default;

public:
	virtual HRESULT			NativeConstruct();

public:
	virtual HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual HRESULT			Load_Data(HANDLE _hFile);

private:
	COIN					m_CoinType;

public:
	static CItem_Coin*		Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void			Free() override;
};

END