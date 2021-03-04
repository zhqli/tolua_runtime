
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua.h"


static int _amqnativebitand(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	int value1 = (int)lua_tonumber(L, 1);   
	int value2 = (int)lua_tonumber(L, 2);   
	lua_pushnumber(L, value1&value2);
	return 1;
}

static int _amqnativebitnot(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	int value1 = (int)lua_tonumber(L, 1);   
	lua_pushnumber(L, ~value1);
	return 1;
}
static int _amqnativegetbuffer(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushstring(L, "");
		return 1;
	}
	int id = (int)lua_tonumber(L, 1);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		lua_pushlstring(L,data,size);
	}
	else
	{
		lua_pushstring(L, "");
	}
    return 1;
}
static int _amqnativegetbufferlen(lua_State* L)
{
	int type = lua_type(L,1);
	if (type != LUA_TNUMBER)
	{
		lua_pushstring(L, "");
		return 1;
	}
	int id = (int) lua_tonumber(L,1);
	if(amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char*data = amqnative_getbuffer(id, &size);
		lua_pushnumber(L,size);
	}
	else{
		lua_pushnumber(L,0);
	}
	return 1;
}

static int _amqnativegetbufferoffset(lua_State* L)
{
	int type = lua_type(L, 1);
	if (type != LUA_TNUMBER)
	{
		lua_pushstring(L, "");
		return 1;
	}
	type = lua_type(L, 2);
	if (type != LUA_TNUMBER)
	{
		lua_pushstring(L, "");
		return 1;
	}
	int id = (int)lua_tonumber(L, 1);
	int key = (int)lua_tonumber(L, 2);
	if (amqnative_getbufferoffset != NULL)
	{
		lua_pushnumber(L, amqnative_getbufferoffset(id, key));
	}
	else {
		lua_pushnumber(L, -1);
	}
	return 1;
}

static int _amqnativegetoffsetbuffer(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushstring(L, NULL);
		return 1;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushstring(L, NULL);
		return 1;
	}
	type = lua_type(L, 3);
	if( type != LUA_TNUMBER)
	{
		lua_pushstring(L, NULL);
		return 1;
	}
	int id = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	int size = (int)lua_tonumber(L, 3);   
	if( amqnative_getoffsetbuffer != NULL)
	{
		const char* data = amqnative_getoffsetbuffer(id,offset,size);
		if( data == NULL)
			lua_pushstring(L, NULL);
		else
			lua_pushlstring(L,data,size);
	}
	else
	{
		lua_pushstring(L, NULL);
	}
    return 1;
}

static int _amqnativegetsbyte(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		lua_pushnumber(L, data[offset]);
	}
	else
	{
		lua_pushnumber(L, 0);
	}
    return 1;
}

static int _amqnativegetbyte(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		unsigned char* buffer = (unsigned char*)data;
		lua_pushnumber(L, buffer[offset]);
	}
	else
	{
		lua_pushnumber(L, 0);
	}
    return 1;
}

static int _amqnativegetshort(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		short res;
		memcpy(&res,data+offset,2);
		lua_pushnumber(L, res);
	}
	else
	{
		lua_pushnumber(L, 0);
	}
    return 1;
}

static int _amqnativegetushort(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		unsigned short res;
		memcpy(&res,data+offset,2);
		lua_pushnumber(L, res);
	}
	else
	{
		lua_pushnumber(L, 0);
	}
    return 1;
}

static int _amqnativegetint(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		int res;
		memcpy(&res,data+offset,4);
		lua_pushnumber(L, res);
	}
	else
	{
		lua_pushnumber(L, 0);
	}
    return 1;
}

static int _amqnativegetuint(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		unsigned int res;
		memcpy(&res,data+offset,4);
		lua_pushnumber(L, res);
	}
	else
	{
		lua_pushnumber(L, 0);
	}
    return 1;
}

static int _amqnativegetfloat(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		return 1;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		float res;
		memcpy(&res,data+offset,4);
		lua_pushnumber(L, res);
	}
	else
	{
		lua_pushnumber(L, 0);
	}
    return 1;
}


static int _amqnativegetint64(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
		return 2;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
		return 2;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		int res;
		memcpy(&res,data+offset,4);
		lua_pushnumber(L, res);
		memcpy(&res,data+offset+4,4);
		lua_pushnumber(L, res);
	}
	else
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
	}
    return 2;
}

static int _amqnativegetuint64(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
		return 2;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
		return 2;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		unsigned int res;
		memcpy(&res,data+offset,4);
		lua_pushnumber(L, res);
		memcpy(&res,data+offset+4,4);
		lua_pushnumber(L, res);
	}
	else
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
	}
    return 2;
}

static int _amqnativegetdouble(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
		return 2;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
		return 2;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		float res;
		memcpy(&res,data+offset,4);
		lua_pushnumber(L, res);
		memcpy(&res,data+offset+4,4);
		lua_pushnumber(L, res);
	}
	else
	{
		lua_pushnumber(L, 0);
		lua_pushnumber(L, 0);
	}
    return 2;
}

static int _amqnativegetstring(lua_State* L)
{    
	int type = lua_type(L, 1);
	if( type != LUA_TNUMBER)
	{
		lua_pushstring(L,"");
		return 1;
	}
	type = lua_type(L, 2);
	if( type != LUA_TNUMBER)
	{
		lua_pushstring(L,"");
		return 1;
	}
	type = lua_type(L, 3);
	if( type != LUA_TNUMBER)
	{
		lua_pushstring(L,"");
		return 1;
	}
	int id 	   = (int)lua_tonumber(L, 1);   
	int offset = (int)lua_tonumber(L, 2);   
	int outsize = (int)lua_tonumber(L, 3);
	if( amqnative_getbuffer != NULL)
	{
		int size = 0;
		const char* data = amqnative_getbuffer(id,&size);
		lua_pushlstring(L,data + offset,outsize);
	}
	else
	{
		lua_pushstring(L,"");
	}
    return 1;
}


void tolua_openamqnative(lua_State* L)
{        
    lua_newtable(L);      
    lua_pushvalue(L, -1);
    lua_setglobal(L, "amqnative");

    lua_getref(L, LUA_RIDX_LOADED);
    lua_pushstring(L, "amqnative");
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);
    lua_pop(L, 1);
     
    lua_pushstring(L, "getbuffer");
    lua_pushcfunction(L, _amqnativegetbuffer);
    lua_rawset(L, -3);

	lua_pushstring(L, "getbufferlen");
	lua_pushcfunction(L, _amqnativegetbufferlen);
	lua_rawset(L,-3);
	
	lua_pushstring(L, "getbufferoffset");
	lua_pushcfunction(L, _amqnativegetbufferoffset);
	lua_rawset(L, -3);

    lua_pushstring(L, "getoffsetbuffer");
    lua_pushcfunction(L, _amqnativegetoffsetbuffer);
    lua_rawset(L, -3);

    lua_pushstring(L, "getsbyte");
    lua_pushcfunction(L, _amqnativegetsbyte);
    lua_rawset(L, -3);     

    lua_pushstring(L, "getbyte");
    lua_pushcfunction(L, _amqnativegetbyte);
    lua_rawset(L, -3);

    lua_pushstring(L, "getshort");
    lua_pushcfunction(L, _amqnativegetshort);
    lua_rawset(L, -3);   

    lua_pushstring(L, "getushort");
    lua_pushcfunction(L, _amqnativegetushort);
    lua_rawset(L, -3);      

    lua_pushstring(L, "getint");
    lua_pushcfunction(L, _amqnativegetint);
    lua_rawset(L, -3);      

    lua_pushstring(L, "getuint");
    lua_pushcfunction(L, _amqnativegetuint);
    lua_rawset(L, -3);  

    lua_pushstring(L, "getfloat");
    lua_pushcfunction(L, _amqnativegetfloat);
    lua_rawset(L, -3);

    lua_pushstring(L, "getdouble");
    lua_pushcfunction(L, _amqnativegetdouble);
    lua_rawset(L, -3); 

    lua_pushstring(L, "getint64");
    lua_pushcfunction(L, _amqnativegetint64);
    lua_rawset(L, -3); 

    lua_pushstring(L, "getuint64");
    lua_pushcfunction(L, _amqnativegetuint64);
    lua_rawset(L, -3);     

    lua_pushstring(L, "getstring");
    lua_pushcfunction(L, _amqnativegetstring);
    lua_rawset(L, -3);    
	
	lua_pushstring(L, "bitand");
    lua_pushcfunction(L, _amqnativebitand);
    lua_rawset(L, -3);

	lua_pushstring(L, "bitnot");
    lua_pushcfunction(L, _amqnativebitnot);
    lua_rawset(L, -3);	

    lua_rawseti(L, LUA_REGISTRYINDEX, LUA_RIDX_AMQNATIVE);     
}

