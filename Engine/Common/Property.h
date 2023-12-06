#pragma once

namespace Clone::Common
{
// Creates empty get-only property macro
#define CLONE_GET_ONLY_PROPERTY(type, propName)\
public:\
	__declspec(property(get = Get##propName)) type propName;\
	type Get##propName() const { return m_##propName; }\
private:\
	type m_##propName

// Creates const getter-setter property macro
#define CLONE_CONST_GET_ONLY_PROPERTY(type, propName)\
public:\
	__declspec(property(get = Get##propName)) type propName;\
	const type& Get##propName() const { return m_##propName; }\
private:\
	type m_##propName

// Creates empty getter-setter property macro
#define CLONE_PROPERTY(type, propName)\
public:\
	__declspec(property(get = Get##propName, put = Set##propName)) type propName;\
	type Get##propName() const { return m_##propName; }\
	void Set##propName(const type& value);\
private:\
	type m_##propName

// Creates const getter-setter property macro
#define CLONE_CONST_PROPERTY(type, propName)\
public:\
	__declspec(property(get = Get##propName, put = Set##propName)) type propName;\
	const type& Get##propName() const { return m_##propName; }\
	void Set##propName(const type& value);\
private:\
	type m_##propName

// Auto creates getter-setter property macro
#define CLONE_AUTO_PROPERTY(type, propName)\
public:\
	__declspec(property(get = Get##propName, put = Set##propName)) type propName;\
	type Get##propName() const { return m_##propName; }\
	void Set##propName(const type& value) { m_##propName = value; }\
private:\
	type m_##propName

// Auto creates getter-setter property macro
#define CLONE_CONST_AUTO_PROPERTY(type, propName)\
public:\
	__declspec(property(get = Get##propName, put = Set##propName)) type propName;\
	const type& Get##propName() const { return m_##propName; }\
	void Set##propName(const type& value) { m_##propName = value; }\
private:\
	type m_##propName
}