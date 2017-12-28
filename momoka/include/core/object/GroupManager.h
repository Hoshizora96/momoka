#pragma once
#include "core/object/GameObjectPool.h"

template<typename... TGroups>
class GroupManager {

	// �������ͼ���    
	template <typename T, typename... Ts>
	struct Index;

	template <typename T, typename... Ts>
	struct Index<T, T, Ts...> : std::integral_constant<std::uint16_t, 0> {
	};

	template <typename T, typename U, typename... Ts>
	struct Index<T, U, Ts...> : std::integral_constant<std::uint16_t, 1 + Index<T, Ts...>::value> {
	};

	using pVoid = void*;
	pVoid* m_groups_;

	template <int index, class T, class V, class... U>
	void InitializeGroups(GameEntityPool* pool) {
		InitializeGroups<index, T>(pool);
		InitializeGroups<index + 1, V, U...>(pool);
	}

	// �����Tһ����Group���ͣ��乹�캯����ҪGameEntityPool*���͵Ĳ���
	template <int index, class T>
	void InitializeGroups(GameEntityPool* pool) const {
		m_groups_[index] = static_cast<pVoid>(new T(pool));
	}

public:
	GroupManager(GameEntityPool* pool) {
		m_groups_ = new pVoid[sizeof...(TGroups)];
		InitializeGroups<0, TGroups...>(pool);
	}

	template<typename T>
	T& GetGroup() {
		return *(static_cast<T*>(m_groups_[Index<T, TGroups...>::value]));
	}
};
