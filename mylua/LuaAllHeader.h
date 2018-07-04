#ifndef _LUA_ALL_HEADER_H_
#define _LUA_ALL_HEADER_H_


extern "C"
{
#define LUA_LIB  // 使LUALIB_API变成DLL导出
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#if LUA_VERSION_NUM > 501
/*
** Lua 5.2
*/
#define lua_strlen lua_rawlen
/* luaL_typerror always used with arg at ndx == NULL */
#define luaL_typerror(L,ndx,str) luaL_error(L,"bad argument %d (%s expected, got nil)",ndx,str)
/* luaL_register used once, so below expansion is OK for this case */
#define luaL_register(L,name,reg) lua_newtable(L);luaL_setfuncs(L,reg,0)
/* luaL_openlib always used with name == NULL */
#define luaL_openlib(L,name,reg,nup) luaL_setfuncs(L,reg,nup)

#if LUA_VERSION_NUM > 502
/*
** Lua 5.3
*/
#define luaL_checkint(L,n)  ((int)luaL_checkinteger(L, (n)))
#endif
#endif



#include <LuaBridge.h>
using namespace luabridge;

class LuaStackCleaner
{
public:
    LuaStackCleaner(lua_State* L)
    {
        m_L = L;
        m_old_top = lua_gettop(m_L);
    }
    LuaStackCleaner(lua_State* L, int old_top)
    {
        m_L = L;
        m_old_top = old_top;
    }
    ~LuaStackCleaner()
    {
        lua_settop(m_L, m_old_top);
    }
    int OldTop()
    {
        return m_old_top;
    }
private:
    lua_State* m_L;
    int m_old_top;
};

class LuaTable;
class LuaFunction;
#include "LuaTable.h"
#include "LuaFunction.h"


#endif