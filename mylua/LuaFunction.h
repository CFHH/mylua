#ifndef _KOD_LUA_FUNCTION_H_
#define _KOD_LUA_FUNCTION_H_

#include "LuaAllHeader.h"
#define LUA_FUNCTION_PARAM_CNT(cnt) (m_table ? (cnt) + 1 : (cnt))

#define LUA_FUNCTION_CALL_ERROR_PROCESS(code)   if (code != 0)           \
{                                                                        \
    if (lua_gettop(m_L) > 0 )                                            \
    {                                                                    \
        char const* s = lua_tostring(m_L, -1);                           \
        SetLastError(s ? s : "Unkown error 1.");                         \
    }                                                                    \
    else                                                                 \
    {                                                                    \
        SetLastError("Unkown error 2.");                                 \
    }                                                                    \
    if (code == LUA_ERRRUN)                                              \
        return LFCR_PCallRun;                                            \
    else if (code == LUA_ERRMEM)                                         \
        return LFCR_PCallMem;                                            \
    else                                                                 \
        return LFCR_PCallErr;                                            \
}                                                                        \
//if (code != 0)
//{
//    if (lua_gettop(m_L) > 0)
//    {
//        char const* s = lua_tostring(m_L, -1);
//        m_last_error = s ? s : "Unkown error 1.";
//    }
//    else
//    {
//        m_last_error = "Unkown error 2.";
//    }
//    if (code == LUA_ERRRUN)
//        return LFCR_PCallRun;
//    else if (code == LUA_ERRMEM)
//        return LFCR_PCallMem;
//    else
//        return LFCR_PCallErr;
//}

enum LuaFunctionCallResult
{
    LFCR_Success = 0,
    LFCR_StackOverFlow,
    LFCR_PCallRun,
    LFCR_PCallMem,
    LFCR_PCallErr,
    LFCR_ReturnCnt,
    LFCR_R1Error,
    LFCR_R2Error,
    LFCR_R3Error,
    LFCR_R4Error,
    LFCR_R5Error,
    LFCR_R6Error,
};


class LuaFunction
{
private:
    LuaFunction(lua_State* L, LuaTable* table, int func_ref);

public:
    ~LuaFunction();
    static LuaFunction* CreateAsMemberFunction(lua_State* L, LuaTable* table, int func_ref);
    static LuaFunction* CreateAsNonMemberFunction(lua_State* L, const char* name);
    inline void push(lua_State* L) const { lua_rawgeti(L, LUA_REGISTRYINDEX, m_func_ref); }
    const char* GetLastError() { return m_last_error.c_str(); }

private:
    void PushSelfForCall() const;
    void SetLastError(const char* err_string);

    // 没有返回值
public:
    int Call()
    {
        int param_cnt = LUA_FUNCTION_PARAM_CNT(0);
        if (!lua_checkstack(m_L, param_cnt + LUA_STACK_EXTRA))
            return LFCR_StackOverFlow;
        LuaStackCleaner lsc(m_L);
		lua_getglobal(m_L, "traceback");
		int errfunc = lua_gettop(m_L);
        PushSelfForCall();
		int code = lua_pcall(m_L, param_cnt, 0, errfunc);
        LUA_FUNCTION_CALL_ERROR_PROCESS(code);
        return LFCR_Success;
    }

    template <typename P1>
    int Call (P1 p1)
    {
        int param_cnt = LUA_FUNCTION_PARAM_CNT(1);
        if (!lua_checkstack(m_L, param_cnt + LUA_STACK_EXTRA))
            return LFCR_StackOverFlow;
        LuaStackCleaner lsc(m_L);
		lua_getglobal(m_L, "traceback");
		int errfunc = lua_gettop(m_L);
        PushSelfForCall();
        Stack <P1>::push(m_L, p1);
		int code = lua_pcall(m_L, param_cnt, 0, errfunc);
        LUA_FUNCTION_CALL_ERROR_PROCESS(code);
        return LFCR_Success;
    }

    template <typename P1, typename P2>
    int Call(P1 p1, P2 p2)
    {
        int param_cnt = LUA_FUNCTION_PARAM_CNT(2);
        if (!lua_checkstack(m_L, param_cnt + LUA_STACK_EXTRA))
            return LFCR_StackOverFlow;
        LuaStackCleaner lsc(m_L);
		lua_getglobal(m_L, "traceback");
		int errfunc = lua_gettop(m_L);
        PushSelfForCall();
        Stack <P1>::push(m_L, p1);
        Stack <P2>::push(m_L, p2);
		int code = lua_pcall(m_L, param_cnt, 0, errfunc);
        LUA_FUNCTION_CALL_ERROR_PROCESS(code);
        return LFCR_Success;
    }

    template <typename P1, typename P2, typename P3>
    int Call(P1 p1, P2 p2, P3 p3)
    {
        int param_cnt = LUA_FUNCTION_PARAM_CNT(3);
        if (!lua_checkstack(m_L, param_cnt + LUA_STACK_EXTRA))
            return LFCR_StackOverFlow;
		LuaStackCleaner lsc(m_L);
		lua_getglobal(m_L, "traceback");
		int errfunc = lua_gettop(m_L);
        PushSelfForCall();
        Stack <P1>::push(m_L, p1);
        Stack <P2>::push(m_L, p2);
        Stack <P3>::push(m_L, p3);
		int code = lua_pcall(m_L, param_cnt, 0, errfunc);
        LUA_FUNCTION_CALL_ERROR_PROCESS(code);
        return LFCR_Success;
    }

    template <typename P1, typename P2, typename P3, typename P4>
    int Call(P1 p1, P2 p2, P3 p3, P4 p4)
    {
        int param_cnt = LUA_FUNCTION_PARAM_CNT(4);
        if (!lua_checkstack(m_L, param_cnt + LUA_STACK_EXTRA))
            return LFCR_StackOverFlow;
        LuaStackCleaner lsc(m_L);
		lua_getglobal(m_L, "traceback");
		int errfunc = lua_gettop(m_L);
        PushSelfForCall();
        Stack <P1>::push(m_L, p1);
        Stack <P2>::push(m_L, p2);
        Stack <P3>::push(m_L, p3);
        Stack <P4>::push(m_L, p4);
		int code = lua_pcall(m_L, param_cnt, 0, errfunc);
        LUA_FUNCTION_CALL_ERROR_PROCESS(code);
        return LFCR_Success;
    }

    template <typename P1, typename P2, typename P3, typename P4, typename P5>
    int Call(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
    {
        int param_cnt = LUA_FUNCTION_PARAM_CNT(5);
        if (!lua_checkstack(m_L, param_cnt + LUA_STACK_EXTRA))
            return LFCR_StackOverFlow;
        LuaStackCleaner lsc(m_L);
		lua_getglobal(m_L, "traceback");
		int errfunc = lua_gettop(m_L);
        PushSelfForCall();
        Stack <P1>::push(m_L, p1);
        Stack <P2>::push(m_L, p2);
        Stack <P3>::push(m_L, p3);
        Stack <P4>::push(m_L, p4);
        Stack <P5>::push(m_L, p5);
		int code = lua_pcall(m_L, param_cnt, 0, errfunc);
        LUA_FUNCTION_CALL_ERROR_PROCESS(code);
        return LFCR_Success;
    }

    template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
    int Call(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
    {
        int param_cnt = LUA_FUNCTION_PARAM_CNT(6);
        if (!lua_checkstack(m_L, param_cnt + LUA_STACK_EXTRA))
            return LFCR_StackOverFlow;
		LuaStackCleaner lsc(m_L);
		lua_getglobal(m_L, "traceback");
		int errfunc = lua_gettop(m_L);
        PushSelfForCall();
        Stack <P1>::push(m_L, p1);
        Stack <P2>::push(m_L, p2);
        Stack <P3>::push(m_L, p3);
        Stack <P4>::push(m_L, p4);
        Stack <P5>::push(m_L, p5);
        Stack <P6>::push(m_L, p6);
		int code = lua_pcall(m_L, param_cnt, 0, errfunc);
        LUA_FUNCTION_CALL_ERROR_PROCESS(code);
        return LFCR_Success;
    }

    // 有返回值，按需求自己写
    // 按函数名排序
public:
    template <typename P1, typename R1>
    int CallP1R1(P1 p1, R1& r1)
    {
        int param_cnt = LUA_FUNCTION_PARAM_CNT(1);
        int return_cnt = 1;
        if (!lua_checkstack(m_L, param_cnt + LUA_STACK_EXTRA))
            return LFCR_StackOverFlow;
        int old_top = lua_gettop(m_L);
        LuaStackCleaner lsc(m_L, old_top);
		lua_getglobal(m_L, "traceback");
		int errfunc = lua_gettop(m_L);
        PushSelfForCall();
        Stack <P1>::push(m_L, p1);
		int code = lua_pcall(m_L, param_cnt, return_cnt, errfunc);
        LUA_FUNCTION_CALL_ERROR_PROCESS(code);
        int new_top = lua_gettop(m_L);
        if (new_top - old_top < return_cnt)
            return LFCR_ReturnCnt;
        r1 = Stack <R1>::get(m_L, old_top + 2);
        return LFCR_Success;
    }

    template <typename P1, typename R1, typename R2>
    int CallP1R2(P1 p1, R1& r1, R2& r2)
    {
        int param_cnt = LUA_FUNCTION_PARAM_CNT(1);
        int return_cnt = 2;
        if (!lua_checkstack(m_L, param_cnt + LUA_STACK_EXTRA))
            return LFCR_StackOverFlow;
        int old_top = lua_gettop(m_L);
		LuaStackCleaner lsc(m_L, old_top);
		lua_getglobal(m_L, "traceback");
		int errfunc = lua_gettop(m_L);
        PushSelfForCall();
        Stack <P1>::push(m_L, p1);
		int code = lua_pcall(m_L, param_cnt, return_cnt, errfunc);
        LUA_FUNCTION_CALL_ERROR_PROCESS(code);
        int new_top = lua_gettop(m_L);
        if (new_top - old_top < return_cnt)
            return LFCR_ReturnCnt;
        r1 = Stack <R1>::get(m_L, old_top + 2);
        r2 = Stack <R2>::get(m_L, old_top + 3);
        return LFCR_Success;
    }

    template <typename P1, typename P2, typename R1, typename R2>
    int CallP2R2(P1 p1, P2 p2, R1& r1, R2& r2)
    {
        int param_cnt = LUA_FUNCTION_PARAM_CNT(2);
        int return_cnt = 2;
        if (!lua_checkstack(m_L, param_cnt + LUA_STACK_EXTRA))
            return LFCR_StackOverFlow;
        int old_top = lua_gettop(m_L);
		LuaStackCleaner lsc(m_L, old_top);
		lua_getglobal(m_L, "traceback");
		int errfunc = lua_gettop(m_L);
        PushSelfForCall();
        Stack <P1>::push(m_L, p1);
        Stack <P2>::push(m_L, p2);
		int code = lua_pcall(m_L, param_cnt, return_cnt, errfunc);
        LUA_FUNCTION_CALL_ERROR_PROCESS(code);
        int new_top = lua_gettop(m_L);
        if (new_top - old_top < return_cnt)
            return LFCR_ReturnCnt;
        r1 = Stack <R1>::get(m_L, old_top + 2);
        r2 = Stack <R2>::get(m_L, old_top + 3);
        return LFCR_Success;
    }

private:
    static const int LUA_STACK_EXTRA = 6;
    lua_State* m_L;
    LuaTable* m_table;
    int m_func_ref;
    std::string m_last_error;
};


#endif