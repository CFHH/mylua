//------------------------------------------------------------------------------
/*
https://github.com/vinniefalco/LuaBridge

Copyright 2012, Vinnie Falco <vinnie.falco@gmail.com>
Copyright 2007, Nathan Reed

License: The MIT License (http://www.opensource.org/licenses/mit-license.php)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//==============================================================================



/*-------------------------------------------
---------------------------------------------
跨平台规范化后的类型
---------------------------------------------
-------------------------------------------*/

/*-------------------------------------------
int8
-------------------------------------------*/
template <>
struct Stack <int8>
{
    static inline void push(lua_State* L, int8 value)
    {
        lua_pushinteger(L, static_cast <lua_Integer> (value));
    }
    static inline int8 get(lua_State* L, int index)
    {
        return static_cast <int8> (luaL_checkinteger(L, index));
    }
};
template <>
struct Stack <int8 const&>  //其实不明白为什么要写这种类型（注意是lua_pushnumber/lua_Number/luaL_checknumber）
{
    static inline void push(lua_State* L, int8 value)
    {
        lua_pushnumber(L, static_cast <lua_Number> (value));
    }
    static inline int8 get(lua_State* L, int index)
    {
        return static_cast <int8> (luaL_checknumber(L, index));
    }
};

/*-------------------------------------------
uint8
-------------------------------------------*/
template <>
struct Stack <uint8>
{
    static inline void push(lua_State* L, uint8 value)
    {
        lua_pushinteger(L, static_cast <lua_Integer> (value));
    }
    static inline uint8 get(lua_State* L, int index)
    {
        return static_cast <uint8> (luaL_checkinteger(L, index));
    }
};

/*-------------------------------------------
int16
-------------------------------------------*/
template <>
struct Stack <int16>
{
    static inline void push(lua_State* L, int16 value)
    {
        lua_pushinteger(L, static_cast <lua_Integer> (value));
    }
    static inline int16 get(lua_State* L, int index)
    {
        return static_cast <int16> (luaL_checkinteger(L, index));
    }
};

/*-------------------------------------------
uint16
-------------------------------------------*/
template <>
struct Stack <uint16>
{
    static inline void push(lua_State* L, uint16 value)
    {
        lua_pushinteger(L, static_cast <lua_Integer> (value));
    }
    static inline uint16 get(lua_State* L, int index)
    {
        return static_cast <uint16> (luaL_checkinteger(L, index));
    }
};

/*-------------------------------------------
int32
-------------------------------------------*/
template <>
struct Stack <int32>
{
    static inline void push(lua_State* L, int32 value)
    {
        lua_pushinteger(L, static_cast <lua_Integer> (value));
    }
    static inline int32 get(lua_State* L, int index)
    {
        return static_cast <int32> (luaL_checkinteger(L, index));
    }
};

/*-------------------------------------------
uint32
-------------------------------------------*/
template <>
struct Stack <uint32>
{
    static inline void push(lua_State* L, uint32 value)
    {
        lua_pushinteger(L, static_cast <lua_Integer> (value));
    }
    static inline uint32 get(lua_State* L, int index)
    {
        return static_cast <uint32> (luaL_checkinteger(L, index));
    }
};

/*-------------------------------------------
int64
-------------------------------------------*/
template <>
struct Stack <int64>
{
    static inline void push(lua_State* L, int64 value)
    {
        lua_pushinteger(L, static_cast <lua_Integer> (value));
    }
    static inline int64 get(lua_State* L, int index)
    {
        return static_cast <int64> (luaL_checkinteger(L, index));
    }
};

/*-------------------------------------------
uint64
-------------------------------------------*/
template <>
struct Stack <uint64>
{
    static inline void push(lua_State* L, uint64 value)
    {
        lua_pushinteger(L, static_cast <lua_Integer> (value));
    }
    static inline uint64 get(lua_State* L, int index)
    {
        return static_cast <uint64> (luaL_checkinteger(L, index));
    }
};



/*-------------------------------------------
---------------------------------------------
C++语言其他原生基本类型
---------------------------------------------
-------------------------------------------*/

/*-------------------------------------------
char：这里当作字符串处理的
-------------------------------------------*/
template <>
struct Stack <char>
{
    static inline void push(lua_State* L, char value)
    {
        char str[2] = { value, 0 };
        lua_pushstring(L, str);
    }
    static inline char get(lua_State* L, int index)
    {
        return luaL_checkstring(L, index)[0];
    }
};
template <>
struct Stack <char const&>
{
    static inline void push(lua_State* L, char value)
    {
        char str[2] = { value, 0 };
        lua_pushstring(L, str);
    }
    static inline char get(lua_State* L, int index)
    {
        return luaL_checkstring(L, index)[0];
    }
};

/*-------------------------------------------
char const*
-------------------------------------------*/
template <>
struct Stack <char const*>
{
    static inline void push(lua_State* L, char const* str)
    {
        if (str)
            lua_pushstring(L, str);
        else
            lua_pushnil(L);
    }
    static inline char const* get(lua_State* L, int index)
    {
        return lua_isnil(L, index) ? 0 : luaL_checkstring(L, index);
    }
};

/*-------------------------------------------
long
-------------------------------------------*/
template <>
struct Stack <long>
{
    static inline void push(lua_State* L, long value)
    {
        lua_pushinteger(L, static_cast <lua_Integer> (value));
    }
    static inline long get(lua_State* L, int index)
    {
        return static_cast <long> (luaL_checkinteger(L, index));
    }
};

/*-------------------------------------------
unsigned long
-------------------------------------------*/
template <>
struct Stack <unsigned long>
{
    static inline void push(lua_State* L, unsigned long value)
    {
        lua_pushinteger(L, static_cast <lua_Integer> (value));
    }
    static inline unsigned long get(lua_State* L, int index)
    {
        return static_cast <unsigned long> (luaL_checkinteger(L, index));
    }
};

/*-------------------------------------------
bool
-------------------------------------------*/
template <>
struct Stack <bool> {
    static inline void push(lua_State* L, bool value)
    {
        lua_pushboolean(L, value ? 1 : 0);
    }
    static inline bool get(lua_State* L, int index)
    {
        return lua_toboolean(L, index) ? true : false;
    }
};

/*-------------------------------------------
float
-------------------------------------------*/
template <>
struct Stack <float>
{
    static inline void push(lua_State* L, float value)
    {
        lua_pushnumber(L, static_cast <lua_Number> (value));
    }
    static inline float get(lua_State* L, int index)
    {
        return static_cast <float> (luaL_checknumber(L, index));
    }
};

/*-------------------------------------------
double
-------------------------------------------*/
template <> struct Stack <double>
{
    static inline void push(lua_State* L, double value)
    {
        lua_pushnumber(L, static_cast <lua_Number> (value));
    }
    static inline double get(lua_State* L, int index)
    {
        return static_cast <double> (luaL_checknumber(L, index));
    }
};



/*-------------------------------------------
---------------------------------------------
系统扩展类型
---------------------------------------------
-------------------------------------------*/
#ifdef _WINDOWS
#else
#endif



/*-------------------------------------------
---------------------------------------------
自定义类型
---------------------------------------------
-------------------------------------------*/

/*-------------------------------------------
std::string
-------------------------------------------*/
template <>
struct Stack <std::string>
{
    static inline void push(lua_State* L, std::string const& str)
    {
        lua_pushlstring(L, str.c_str(), str.size());
    }
    static inline std::string get(lua_State* L, int index)
    {
        size_t len;
        const char *str = luaL_checklstring(L, index, &len);
        return std::string(str, len);
    }
};

/*-------------------------------------------
std::string&
-------------------------------------------*/
template <>
struct Stack <std::string&>
{
    static inline void push(lua_State* L, std::string& str)
    {
        lua_pushlstring(L, str.c_str(), str.size());
    }
    static inline std::string get(lua_State* L, int index)
    {
        size_t len;
        const char *str = luaL_checklstring(L, index, &len);
        return std::string(str, len);
    }
};

/*-------------------------------------------
std::string const&
-------------------------------------------*/
template <>
struct Stack <std::string const&>
{
    static inline void push(lua_State* L, std::string const& str)
    {
        lua_pushlstring(L, str.c_str(), str.size());
    }
    static inline std::string get(lua_State* L, int index)
    {
        size_t len;
        const char *str = luaL_checklstring(L, index, &len);
        return std::string(str, len);
    }
};

/*-------------------------------------------
lua_CFunction
-------------------------------------------*/
template <>
struct Stack <lua_CFunction>
{
    static void push(lua_State* L, lua_CFunction f)
    {
        lua_pushcfunction(L, f);
    }
    static lua_CFunction get(lua_State* L, int index)
    {
        return lua_tocfunction(L, index);
    }
};

/*-------------------------------------------
lua_State*
-------------------------------------------*/
template <>
struct Stack <lua_State*>
{
    static lua_State* get(lua_State* L, int)
    {
        return L;
    }
};
