#pragma once
#include "core/object/components/Component.h"
#include "util/Signal.h"
#include <set>
#include <vector>
#include <bitset>
#include <stack>

// 用于类型计数    
template <typename T, typename... Ts>
struct Index;

template <typename T, typename... Ts>
struct Index<T, T, Ts...> : std::integral_constant<std::uint16_t, 0> {
};

template <typename T, typename U, typename... Ts>
struct Index<T, U, Ts...> : std::integral_constant<std::uint16_t, 1 + Index<T, Ts...>::value> {
};

template <typename T>
bool AllTrue(T val) {
	return val;
}

template <typename T, typename... U>
bool AllTrue(T a, U ... vals) {
	if (a)
		return AllTrue(vals...);
	return false;
}

typedef unsigned int EntityIndex;

template <class... TComps>
class EntityPool {

	struct EntityInfo {
		std::bitset<sizeof...(TComps)> componentActiveBit;
		EntityIndex version = 0;
	};

	using pComponent = Component*;

	pComponent* m_ppComponent_;
	EntityInfo* m_entityInfoArray_;

	std::stack<EntityIndex> m_freePosition_;
	std::set<EntityIndex> m_cachedEntities_;

	unsigned int m_poolSize_;

	bool IsEntityAlive(EntityIndex version, EntityIndex index) const {
		return m_entityInfoArray_[index].version == version;
	}

	EntityInfo* GetEntityInfo(EntityIndex index) const {
		return m_entityInfoArray_ + index;
	}

	EntityIndex GetUnusedEntityPosition() {
		if (!m_freePosition_.empty()) {
			auto res = m_freePosition_.top();
			m_freePosition_.pop();
			return res;
		}
		return -1;
	}

	template <class T>
	T* GetComponent(EntityIndex index) {
		T* ptr = static_cast<T*>(m_ppComponent_[Index<T, TComps...>::value]);
		return std::is_base_of<SingletonComponent, T>::value ? ptr : ptr + index;
	}

	template <class T>
	T* ActivateComponent(EntityIndex index) {
		m_entityInfoArray_[index].componentActiveBit.set(Index<T, TComps...>::value);
		T* ptr = static_cast<T*>(m_ppComponent_[Index<T, TComps...>::value]);
		return std::is_base_of<SingletonComponent, T>::value ? ptr : ptr + index;
	}

	template <class T>
	bool HasComponent(EntityIndex index) {
		return m_entityInfoArray_[index].componentActiveBit.test(Index<T, TComps...>::value);
	}

	template <class T>
	void DisableComponent(EntityIndex index) {
		m_entityInfoArray_[index].componentActiveBit.reset(Index<T, TComps...>::value);
	}

	template <typename T>
	void AddProvidedComponents(EntityIndex index, T& comp) {
		static_assert(!std::is_base_of<SingletonComponent, T>::value, "Can't access singleton component from an entity");
		*ActivateComponent<T>(index) = comp;
	}

	template <typename T, typename... UComps>
	void AddProvidedComponents(EntityIndex index, T& comp, UComps&... comps) {
		static_assert(!std::is_base_of<SingletonComponent, T>::value, "Can't access singleton component from an entity");
		*ActivateComponent<T>(index) = comp;
		AddProvidedComponents(index, comps...);
	}

	void DisableAllComponent(EntityIndex index) {
		m_entityInfoArray_[index].componentActiveBit.reset();
	}

public:
	template <class T>
	T* GetSingletonComponent() {
		static_assert(std::is_base_of<SingletonComponent, T>::value, "Try to get a non-singleton component!");
		return GetComponent<T>(0);
	}

	template <class T>
	T* ActivateSingletonComponent() {
		static_assert(std::is_base_of<SingletonComponent, T>::value, "Try to activate a non-singleton component!");
		return ActivateComponent<T>(0);
	}

	template <class T>
	bool HasSingletonComponent() {
		static_assert(std::is_base_of<SingletonComponent, T>::value, "Try to check a non-singleton component!");
		return HasComponent<T>(0);
	}

	template <class T>
	void DisableSingletonComponent() {
		static_assert(std::is_base_of<SingletonComponent, T>::value, "Try to disable a non-singleton component!");
		DisableComponent<T>(0);
	}

	template <int index, class T>
	void InitializeComponents() const {
		if (std::is_base_of<SingletonComponent, T>::value) {
			m_ppComponent_[index] = static_cast<Component*>(new T[1]);
		}
		else {
			m_ppComponent_[index] = static_cast<Component*>(new T[m_poolSize_]);
		}
	}

	template <int index, class T, class V, class... U>
	void InitializeComponents() {
		InitializeComponents<index, T>();
		InitializeComponents<index + 1, V, U...>();
	}

	explicit EntityPool() : m_ppComponent_(nullptr),
	                        m_poolSize_(1000) {
		m_entityInfoArray_ = new EntityInfo[m_poolSize_];
		m_ppComponent_ = new pComponent[sizeof...(TComps)];
		InitializeComponents<0, TComps...>();
		for(int i = m_poolSize_ - 1; i >=0; i--) {
			m_freePosition_.push(i);
		}
	}

	class Entity {
	private:
		friend class EntityPool;
		EntityPool* m_pool_;
		EntityIndex m_version_;
		EntityIndex m_index_;

		Entity(EntityPool* pool, EntityIndex version, EntityIndex index) : m_pool_(pool),
		                                                              m_version_(version),
		                                                              m_index_(index) {
		}
	public:
		EntityIndex GetVersion() const {
			return m_version_;
		}

		EntityIndex GetIndex() const {
			return m_index_;
		}

		bool IsAlive() {
			return m_pool_->IsEntityAlive(m_version_, m_index_);
		};

		void Destory() {
			m_pool_->DestroyEntity(*this);
		}

		template <typename T>
		T* Get() {
			static_assert(!std::is_base_of<SingletonComponent, T>::value, "Can't access singleton component from an entity");
			if (!IsAlive()) {
				// throw std::logic_error("Try to get component from a destroyed entity!");
				return nullptr;
			}
			if (!m_pool_->HasComponent<T>(m_index_)) {
				return nullptr;
			}
			return m_pool_->GetComponent<T>(m_index_);
		}

		template <typename T>
		T* Activate() {
			static_assert(!std::is_base_of<SingletonComponent, T>::value, "Can't access singleton component from an entity");
			if (!IsAlive()) {
				// throw std::logic_error("Try to activate component of a destroyed entity!");
				return nullptr;
			}
			return m_pool_->ActivateComponent<T>(m_index_);
		}

		template <typename ...Ts>
		bool Has() {
			if (!IsAlive()) {
				// throw std::logic_error("Try to check component of a destroyed entity!");
				return false;
			}
			return AllTrue(m_pool_->HasComponent<Ts>(m_index_)...);
		}

		template <typename T>
		void Disable() {
			static_assert(!std::is_base_of<SingletonComponent, T>::value, "Can't access singleton component from an entity");
			if (!IsAlive()) {
				// throw std::logic_error("Try to remove component from a destroyed entity!");
				return;
			}
			m_pool_->DisableComponent<T>(m_index_);
		}

		bool operator<(const Entity& right) const {
			return this->m_index_ < right.m_index_;
		}
	};

	Entity CreateEntity() {
		auto index = GetUnusedEntityPosition();
		if (index == -1) {
			throw std::overflow_error("Entity pool overflow!");
		}
		DisableAllComponent(index);

		auto ptr = GetEntityInfo(index);
		m_cachedEntities_.insert(index);
		return Entity(this, ptr->version, index);
	}

	template <typename T, typename... UComps>
	Entity CreateEntity(T& comp, UComps&... comps) {
		auto index = GetUnusedEntityPosition();
		if (index == -1) {
			throw std::overflow_error("Entity pool overflow!");
		}

		DisableAllComponent(index);
		AddProvidedComponents(index, comp, comps...);

		EntityInfo* ptr = GetEntityInfo(index);
		m_cachedEntities_.insert(index);
		return Entity(this, ptr->version, index);
	}

	void DestroyEntity(const Entity& entity) {
		if (IsEntityAlive(entity.GetVersion(), entity.GetIndex())) {
			(GetEntityInfo(entity.GetIndex())->version) += 1;
			m_cachedEntities_.erase(entity.GetIndex());
			m_freePosition_.push(entity.GetIndex());
		}
		else {
			// throw std::logic_error("Try to destroy entity twice!");
		}
	}

//	using ComponentEventDelegate = Signal<Entity>;
//	ComponentEventDelegate OnComponentRemovedListeners;
//	ComponentEventDelegate OnComponentAddedListeners;
//	ComponentEventDelegate OnEntityCreatedListeners;
//	ComponentEventDelegate OnEntityDestroyedListeners;

	template <typename T>
	struct Identity {
		typedef T type;
	};

	template <typename... TSubComps>
	void Each(typename Identity<std::function<void(Entity)>>::type func) {
		auto copy = m_cachedEntities_;
		for (auto index : copy) {
			if (AllTrue(HasComponent<TSubComps>(index)...))
				func(Entity(this, m_entityInfoArray_[index].version, index));
		}
	}
};
