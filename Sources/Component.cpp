#include "Component.hpp"

Component::Component(): m_name{"Invalid"} {}

Component::Component(const std::string &name): m_name{name} {}

Component::Component(const Component &component): m_name{component.m_name} {}

Component &Component::operator=(const Component &component) {

	const_cast<std::string&>(m_name) = component.m_name;

	return *this;
}

bool Component::isNamed(const std::string &possibleName) const { return (possibleName == m_name); }