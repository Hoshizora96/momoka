#pragma once
#include <map>

namespace momoka {
	template<class T>
	class HandleTable {
	public:
		HandleTable();
		~HandleTable();
		T GetObject(int id);
		int Register(T object);
		void UnRegister(int id);

	private:
		std::map<int, T> m_handleTableMap_;
	};

	template <class T>
	HandleTable<T>::HandleTable() {
	}

	template <class T>
	HandleTable<T>::~HandleTable() {
	}

	template <class T>
	T HandleTable<T>::GetObjectW(int id) {
	}

	template <class T>
	int HandleTable<T>::Register(T object) {
	}

	template <class T>
	void HandleTable<T>::UnRegister(int id) {
	}
}
