#ifndef _KOD_LUA_TABLE_H_
#define _KOD_LUA_TABLE_H_

#include "LuaAllHeader.h"
#include <map>


class LuaTable
{
private:
    LuaTable(lua_State* L, int index);
    LuaTable(int table_ref, lua_State* L);

public:
    ~LuaTable();
	lua_State* GetL(){ return m_L; }
    static LuaTable* CreateFromStack(lua_State* L, int index);
    static LuaTable* CreateFromGlobal(lua_State* L, const char* name);
    inline void push(lua_State* L) const { lua_rawgeti(L, LUA_REGISTRYINDEX, m_table_ref); }
    LuaFunction* GetMemberFunction(const std::string& func_name);

private:
    lua_State* m_L;
    int m_table_ref;
    std::map<std::string, LuaFunction*> m_member_function_cache;
};


namespace luabridge
{
    template <>
    struct Stack <LuaTable>
    {
    public:
        static inline void push(lua_State* L, LuaTable const* v)
        {
            v->push(L);
        }
        static inline LuaTable* get(lua_State* L, int index)
        {
            return LuaTable::CreateFromStack(L, index);
        }
    };

    template <>
    struct Stack <LuaTable*>
    {
    public:
        static inline void push(lua_State* L, LuaTable const* v)
        {
            v->push(L);
        }
        static inline LuaTable* get(lua_State* L, int index)
        {
            return LuaTable::CreateFromStack(L, index);
        }
    };
}

#endif