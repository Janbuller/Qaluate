#include "lua.hpp"
#include <libqalculate/qalculate.h>

extern "C" {
int InitQalc(lua_State *L) {
  new Calculator();
  CALCULATOR->loadExchangeRates();
  CALCULATOR->loadGlobalDefinitions();
  CALCULATOR->loadLocalDefinitions();
  return 0;
}

int CalcString(lua_State *L) {
  auto Str = lua_tostring(L, 1);
  auto Timeout = lua_tonumber(L, 2);

  auto Result = CALCULATOR->calculateAndPrint(Str, Timeout);
  auto Returned = strdup(Result.c_str());

  lua_pushstring(L, Returned);

  free(Returned);

  return 1;
}

int luaopen_Qaluate(lua_State *L) {
  lua_newtable(L);

  lua_pushcfunction(L, InitQalc);
  lua_setfield(L, -2, "Init");

  lua_pushcfunction(L, CalcString);
  lua_setfield(L, -2, "CalcString");

  return 1;
}
}
