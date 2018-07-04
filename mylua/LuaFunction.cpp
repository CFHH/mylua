#include "LuaTable.h"
#include "LuaFunction.h"
#include <vector>
#include <string.h>

LuaFunction::LuaFunction(lua_State* L, LuaTable* table, int func_ref)
:m_last_error("")
{
    m_L = L;
    m_table = table;
    m_func_ref = func_ref;
}

LuaFunction* LuaFunction::CreateAsMemberFunction(lua_State* L, LuaTable* table, int func_ref)
{
    return new LuaFunction(L, table, func_ref);
}

LuaFunction* LuaFunction::CreateAsNonMemberFunction(lua_State* L, const char* full_path)
{
    LuaStackCleaner lsc(L);

    int len = strlen(full_path);
    char* buf = new char[len + 1];
    memcpy(buf, full_path, len);
    buf[len] = 0;

    std::vector<char*> parts;
    char delims[] = ".";
    char* part = strtok(buf, delims);
    while (part != NULL)
    {
        parts.push_back(part);
        part = strtok(NULL, delims);
    }

    bool success = true;
    int cnt = parts.size();
    if (cnt == 1)
    {
        // 全局函数
        lua_getglobal(L, full_path);
        int t = lua_type(L, -1);
        if (t != LUA_TFUNCTION)
            success = false;
    }
    else
    {
        // 某个table中的函数
        lua_pushstring(L, parts[0]);
        lua_rawget(L, LUA_GLOBALSINDEX);
        int t = lua_type(L, -1);
        if (t != LUA_TTABLE)
        {
            success = false;
        }
        else
        {
            for (int i = 1; i < cnt-1; ++i)
            {
                lua_pushstring(L, parts[i]);
                lua_gettable(L, -2);
                int t = lua_type(L, -1);
                if (t != LUA_TTABLE)
                {
                    success = false;
                    break;
                }
            }
        }
        if (success)
        {
            lua_pushstring(L, parts[cnt - 1]);
            lua_gettable(L, -2);
            int t = lua_type(L, -1);
            if (t != LUA_TFUNCTION)
                success = false;
        }
    }

    delete[] buf;
    if (!success)
        return NULL;
    int func_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    return new LuaFunction(L, NULL, func_ref);
}

LuaFunction::~LuaFunction()
{
    luaL_unref(m_L, LUA_REGISTRYINDEX, m_func_ref);
}


void LuaFunction::PushSelfForCall() const
{
    lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_func_ref);
    // table是第一个参数
    if (m_table)
        m_table->push(m_L);
}

void LuaFunction::SetLastError(const char* err_string)
{
    m_last_error = err_string;
}