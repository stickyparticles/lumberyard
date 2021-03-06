// Portions of this file Copyright (C) Amazon.com, Inc. or its affiliates.

#include "stdafx.h"
#include "ComponentFactoryRegistry.h"

bool CComponentFactoryRegistry::RegisterFactory(std::unique_ptr<IComponentFactoryBase>&& factory)
{
	const ComponentType& type = factory->GetComponentType();
	auto insertResult = m_factories.emplace(std::make_pair(type, std::move(factory)));
	// if insertion failed due to collision, insertResult.second is false
	return insertResult.second;
}

bool CComponentFactoryRegistry::ReleaseFactory(const ComponentType& type)
{
	size_t numErased = m_factories.erase(type);
	return numErased > 0;
}

IComponentFactoryBase* CComponentFactoryRegistry::GetFactoryInternal(const ComponentType& type)
{
	auto findResult = m_factories.find(type);
	if (findResult == m_factories.end())
	{
		return nullptr;
	}
	return findResult->second.get();
}
