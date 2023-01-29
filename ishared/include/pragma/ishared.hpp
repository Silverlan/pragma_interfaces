#ifndef __ISHARED_HPP__
#define __ISHARED_HPP__

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <cinttypes>
#include <string>

#ifdef DLLISHARED_EX
#ifdef __linux__
#define DLLISHARED __attribute__((visibility("default")))
#else
#define DLLISHARED __declspec(dllexport) // export DLL information
#endif
#else
#ifdef __linux__
#define DLLISHARED
#else
#define DLLISHARED __declspec(dllimport) // import DLL information
#endif
#endif

class CallbackHandle;
class Model;
namespace ishared {
	enum class DLLISHARED Callback : uint32_t { Think = 0 };
	DLLISHARED void add_callback(lua_State *l, Callback cb, const CallbackHandle &f);
	DLLISHARED bool protected_lua_call(lua_State *l, int nargs = 0, int nresults = 0);
	DLLISHARED bool validate_file_write_operation(lua_State *l, std::string &path);
	DLLISHARED bool load_documentation_file(const std::string &fileName);
};

#endif
