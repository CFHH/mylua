#include "LuaTable.h"
#include "LuaFunction.h"


LuaTable::LuaTable(lua_State* L, int index)
{
    // 最终栈没有变化
    m_L = L;
    lua_pushvalue(m_L, index);
    m_table_ref = luaL_ref(m_L, LUA_REGISTRYINDEX);
}

LuaTable::LuaTable(int table_ref, lua_State* L)
{
    m_L = L;
    m_table_ref = table_ref;
}

LuaTable::~LuaTable()
{
    for (std::map<std::string, LuaFunction*>::iterator itr = m_member_function_cache.begin(); itr != m_member_function_cache.end(); ++itr)
    {
        delete itr->second;
    }
    m_member_function_cache.clear();
    luaL_unref(m_L, LUA_REGISTRYINDEX, m_table_ref);
}

LuaTable* LuaTable::CreateFromStack(lua_State* L, int index)
{
    int t = lua_type(L, index);
    if (t != LUA_TTABLE)
        return NULL;
    return new LuaTable(L, index);
}

LuaTable* LuaTable::CreateFromGlobal(lua_State* L, const char* name)
{
    // 最终栈没有变化
    lua_getglobal(L, name);
    int t = lua_type(L, -1);
    if (t != LUA_TTABLE)
    {
        lua_pop(L, 1);
        return NULL;
    }
    int table_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    LuaTable* lua_table = new LuaTable(table_ref, L);
    return lua_table;
}

LuaFunction* LuaTable::GetMemberFunction(const std::string& func_name)
{
    std::map<std::string, LuaFunction*>::iterator itr = m_member_function_cache.find(func_name);
    if (itr != m_member_function_cache.end())
        return itr->second;
    LuaStackCleaner lsc(m_L);
    lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_table_ref);
    lua_pushlstring(m_L, func_name.c_str(), func_name.size());
    lua_gettable(m_L, -2);
    int t = lua_type(m_L, -1);
    if (t != LUA_TFUNCTION)
        return NULL;
    int func_ref = luaL_ref(m_L, LUA_REGISTRYINDEX);
    LuaFunction* lua_func = LuaFunction::CreateAsMemberFunction(m_L, this, func_ref);
    m_member_function_cache[func_name] = lua_func;
    return lua_func;
}
