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
		void **vtable = *((void ***)object);

		// The vtable itself is an array of pointers to member functions,
		// in the order they were declared in.
		targetFunc = reinterpret_cast<R(*)(Args...)>(vtable[vtableOffset]);

		intptr_t relativeAddress = reinterpret_cast<intptr_t>(detourFunction) - reinterpret_cast<intptr_t>(targetFunc);
		// JMP relative address
		// 0xE9 ?? ?? ?? ??
		// Address is little endian
		uint8_t* targetFuncCode = reinterpret_cast<uint8_t*>(targetFunc);
		intptr_t startPage = reinterpret_cast<intptr_t >(targetFuncCode) & ~0xFFF;
		intptr_t endPage = (reinterpret_cast<intptr_t >(targetFuncCode) + 5) & ~0xFFF;
		mprotect(reinterpret_cast<void*>(startPage), ((endPage - startPage) * 4096) + 4096, PROT_READ | PROT_WRITE | PROT_EXEC);
		unpatched[0] = targetFuncCode[0];
		unpatched[1] = targetFuncCode[1];
		unpatched[2] = targetFuncCode[2];
		unpatched[3] = targetFuncCode[3];
		unpatched[4] = targetFuncCode[4];
		patched[0] = 0xE9;
		patched[1] = (relativeAddress >> 24) & 0xFF;
		patched[2] = (relativeAddress >> 16) & 0xFF;
		patched[3] = (relativeAddress >> 8) & 0xFF;
		patched[4] = (relativeAddress >> 0) & 0xFF;
		targetFuncCode[0] = patched[0];
		targetFuncCode[1] = patched[1];
		targetFuncCode[2] = patched[2];
		targetFuncCode[3] = patched[3];
		targetFuncCode[4] = patched[4];
		mprotect(reinterpret_cast<void*>(startPage), ((endPage - startPage) * 4096) + 4096, PROT_EXEC);

		LOG("Enabled hook for %s", name.c_str());
		enabled = true;
		return true;
	}

	R OriginalFunc(Args... args)
	{
		uint8_t* targetFuncCode = reinterpret_cast<uint8_t*>(targetFunc);
		intptr_t startPage = reinterpret_cast<intptr_t >(targetFuncCode) & ~0xFFF;
		intptr_t endPage = (reinterpret_cast<intptr_t >(targetFuncCode) + 5) & ~0xFFF;
		mprotect(reinterpret_cast<void*>(startPage), ((endPage - startPage) * 4096) + 4096, PROT_READ | PROT_WRITE | PROT_EXEC);
		targetFuncCode[0] = unpatched[0];
		targetFuncCode[1] = unpatched[1];
		targetFuncCode[2] = unpatched[2];
		targetFuncCode[3] = unpatched[3];
		targetFuncCode[4] = unpatched[4];
		if constexpr (!std::is_void<R>::value)
		{
			R result = targetFunc(args...);
			targetFuncCode[0] = patched[0];
			targetFuncCode[1] = patched[1];
			targetFuncCode[2] = patched[2];
			targetFuncCode[3] = patched[3];
			targetFuncCode[4] = patched[4];
			mprotect(reinterpret_cast<void*>(startPage), ((endPage - startPage) * 4096) + 4096, PROT_EXEC);
			return result;
		} else {
			targetFuncCode[0] = patched[0];
			targetFuncCode[1] = patched[1];
			targetFuncCode[2] = patched[2];
			targetFuncCode[3] = patched[3];
			targetFuncCode[4] = patched[4];
			mprotect(reinterpret_cast<void*>(startPage), ((endPage - startPage) * 4096) + 4096, PROT_EXEC);
		}
	}

	void Destroy()
	{
		if (enabled)
		{
			uint8_t* targetFuncCode = reinterpret_cast<uint8_t*>(targetFunc);
			intptr_t startPage = reinterpret_cast<intptr_t >(targetFuncCode) & ~0xFFF;
			intptr_t endPage = (reinterpret_cast<intptr_t >(targetFuncCode) + 5) & ~0xFFF;
			mprotect(reinterpret_cast<void*>(startPage), ((endPage - startPage) * 4096) + 4096, PROT_READ | PROT_WRITE | PROT_EXEC);
			targetFuncCode[0] = unpatched[0];
			targetFuncCode[1] = unpatched[1];
			targetFuncCode[2] = unpatched[2];
			targetFuncCode[3] = unpatched[3];
			targetFuncCode[4] = unpatched[4];
			mprotect(reinterpret_cast<void*>(startPage), ((endPage - startPage) * 4096) + 4096, PROT_EXEC);
			enabled = false;
		}
	}

private:
	bool enabled = false;
	R(*targetFunc)(Args...) = nullptr;
	uint8_t unpatched[5];
	uint8_t patched[5];
};