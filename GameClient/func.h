#pragma once

void DebugLog(LOG_TYPE _Type, const wchar_t* _LogMgs);
void DebugLog(LOG_TYPE _Type, wstring _LogMgs);
void DrawDebugRect(PEN_TYPE _Type, Vec2D _Pos, Vec2D _Scale, float _Time);
void DrawDebugCircle(PEN_TYPE _Type, Vec2D _Pos, Vec2D _Scale, float _Time);
void DrawDebugLine(PEN_TYPE _Type, Vec2D _Pos, Vec2D _Scale, float _Time);

template<typename T1, typename T2>
void Safe_Del_Map(map<T1, T2>& _map)
{
	for (const auto& pair : _map)
	{
		if (pair.second != nullptr)
			delete pair.second;
	}
	_map.clear();
}

template<typename T>
void Safe_Del_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (_vec[i] != nullptr)
			delete _vec[i];
	}
	_vec.clear();
}

template<typename T, UINT size>
void Safe_Del_Arr(T* (&Arr)[size])
{
	for (UINT i = 0; i < size; ++i)
	{
		if (Arr[i] != nullptr)
		{
			delete Arr[i];
			Arr[i] = nullptr;
		}
	}
}