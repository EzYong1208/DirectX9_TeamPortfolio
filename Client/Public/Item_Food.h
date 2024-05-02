#pragma once

#include "Client_Defines.h"
#include "Item.h"

BEGIN(Client)

class CItem_Food : public CItem
{
public:
	typedef enum Food_Type
	{
		FOOD_BREAD,
		FOOD_APPLE,
		FOOD_CHEESE,
		FOOD_MEAT,
		FOOD_STEAK,
		FOOD_ALE,
		FOOD_END
	}FOOD;

private:
	explicit CItem_Food(LPDIRECT3DDEVICE9 _pGraphicDevice);
	virtual ~CItem_Food() = default;

public:
	virtual	HRESULT			NativeConstruct();

public:
	virtual	HRESULT			Activate(CGameObject* _pTarget);

public:
	virtual HRESULT			Save_Data(HANDLE _hFile);
	virtual	HRESULT			Load_Data(HANDLE _hFile);

private:
	FOOD					m_FoodType;

public:
	static CItem_Food*		Create(LPDIRECT3DDEVICE9 _pGraphicDevice);
	virtual	void			Free() override;
};

END