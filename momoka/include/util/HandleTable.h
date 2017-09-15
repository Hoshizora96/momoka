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
}
