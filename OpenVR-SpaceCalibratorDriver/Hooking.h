#pragma once

#include "Logging.h"
#include <map>
#include <string>
#include <sys/mman.h>

class IHook
{
public:
	const std::string name;

	IHook(const std::string &name) : name(name) { }
	virtual ~IHook() { }

	virtual void Destroy() = 0;

	static bool Exists(const std::string &name);
	static void Register(IHook *hook);
	static void Unregister(IHook *hook);
	static void DestroyAll();

private:
	static std::map<std::string, IHook *> hooks;
};

template <typename R, typename... Args>
class Hook : public IHook
{
public:
	Hook(const std::string &name) : IHook(name) { }

	bool CreateHookInObjectVTable(void *object, int vtableOffset, R(*detourFunction)(Args...))
	{
		// For virtual objects, VC++ adds a pointer to the vtable as the first member.
		// To access the vtable, we simply dereference the object.
		vFunc = *((void ***)object) + vtableOffset;

		// The vtable itself is an array of pointers to member functions,
		// in the order they were declared in.
		originalFunc = reinterpret_cast<R(*)(Args...)>(*vFunc);
		uintptr_t startPage = reinterpret_cast<uintptr_t >(vFunc) & ~0xFFF;
		uintptr_t endPage = reinterpret_cast<uintptr_t >(vFunc + sizeof(detourFunction)) & ~0xFFF;
		mprotect(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(vFunc) & ~0xFFF), endPage - startPage + 4096, PROT_READ | PROT_WRITE | PROT_EXEC);
		*vFunc = reinterpret_cast<void*>(detourFunction);
		mprotect(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(vFunc) & ~0xFFF), endPage - startPage + 4096, PROT_EXEC);
		LOG("Enabled hook for %s", name.c_str());
		enabled = true;
		return true;
	}

	void Destroy()
	{
		if (enabled)
		{
			uintptr_t startPage = reinterpret_cast<uintptr_t >(vFunc) & ~0xFFF;
			uintptr_t endPage = reinterpret_cast<uintptr_t >(vFunc + sizeof(originalFunc)) & ~0xFFF;
			mprotect(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(vFunc) & ~0xFFF), endPage - startPage + 4096, PROT_READ | PROT_WRITE | PROT_EXEC);
			*vFunc = reinterpret_cast<void*>(originalFunc);
			mprotect(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(vFunc) & ~0xFFF), endPage - startPage + 4096, PROT_EXEC);
			enabled = false;
		}
	}
	R(*originalFunc)(Args...) = nullptr;

private:
	bool enabled = false;
	void **vFunc;
};
