#pragma once
#include "stdafx.h"
#include "services/Service.h"
#include "exception/MomokaException.h"
#include "exception/ServiceException.h"
#include <map>
#include <memory>

enum SERVICE_TYPE { Service_input, Service_graphic };

class ServiceLoader {
	typedef std::shared_ptr<Service> ServicePtr;
	typedef std::map<SERVICE_TYPE, ServicePtr> ServicePtrMap;

	ServicePtrMap m_services_;

public:
	void RegisterService(SERVICE_TYPE type, ServicePtr service) {
		const auto found = m_services_.find(type);

		if (found != m_services_.end()) {
			// 有重名的
			throw ServiceRegistedTwiceException("Register Service Twice");
		}
		m_services_.insert(std::make_pair(type, service));
	}

	void UnRegisterService(SERVICE_TYPE type) {
		const auto found = m_services_.find(type);

		if (found != m_services_.end()) {
			m_services_.erase(found);
		}
	}

	template<class T>
	std::weak_ptr<T> LocateService(SERVICE_TYPE type) const {
		auto found = m_services_.find(type);

		if (found != m_services_.end()) {
			std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(found->second);

			if (ptr) {
				return ptr;
			}
			else {
				throw MomokaException("Found service but requested type did not match (bad pointer cast). Check your types.");
			}
		}
		else {
			throw ServiceNotRegistedException("Invalid service id");
		}
	}
};