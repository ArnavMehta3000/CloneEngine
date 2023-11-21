#pragma once

namespace Clone::Common
{
// Creates empty getter-setter property macro
#define CLONE_PROPERTY(type,  propName)\
public:\
	__declspec(property(get = Get##propName, put = Set##propName)) type propName;\
	type Get##propName();\
	void Set##propName(type value);\
private:\
	type m_##propName;

// Creates const getter-setter property macro
#define CLONE_CONST_PROPERTY(type,  propName)\
public:\
	__declspec(property(get = Get##propName, put = Set##propName)) type propName;\
	const type& Get##propName() const;\
	void Set##propName(type value) const;\
private:\
	type m_##propName;

// Auto creates getter-setter property macro
#define CLONE_AUTO_PROPERTY(type,  propName)\
public:\
	__declspec(property(get = Get##propName, put = Set##propName)) type propName;\
	type Get##propName() { return m_##propName; }\
	void Set##propName(type value) { m_##propName = value; }\
private:\
	type m_##propName;

// Auto creates getter-setter property macro
#define CLONE_CONST_AUTO_PROPERTY(type,  propName)\
public:\
	__declspec(property(get = Get##propName, put = Set##propName)) type propName;\
	const type& Get##propName() const { return m_##propName; }\
	void Set##propName(type value) const { m_##propName = value; }\
private:\
	type m_##propName;
}