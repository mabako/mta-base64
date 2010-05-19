/*********************************************************
*
*  Multi Theft Auto: San Andreas - Deathmatch
*
*  ml_base, External lua add-on module
*
*  Copyright © 2003-2008 MTA.  All Rights Reserved.
*
*  Grand Theft Auto is © 2002-2003 Rockstar North
*
*  THE FOLLOWING SOURCES ARE PART OF THE MULTI THEFT
*  AUTO SOFTWARE DEVELOPMENT KIT AND ARE RELEASED AS
*  OPEN SOURCE FILES. THESE FILES MAY BE USED AS LONG
*  AS THE DEVELOPER AGREES TO THE LICENSE THAT IS
*  PROVIDED WITH THIS PACKAGE.
*
*********************************************************/

#include "base64.h"
#include "CFunctions.h"
#include "extra/CLuaArguments.h"

int CFunctions::base64_decode( lua_State* luaVM )
{
	if( luaVM )
	{
		CLuaArguments args;
		if( lua_type( luaVM, 1 ) == LUA_TSTRING || lua_type( luaVM, 1 ) == LUA_TNUMBER )
		{
			args.PushString( base64::decode( lua_tostring( luaVM, 1 ) ).c_str( ) );
		}
		else
		{
			luaL_error( luaVM, "Bad argument @ 'base64_decode'" );
			args.PushBoolean( false );
		}
		args.PushArguments( luaVM );
		return 1;
	}
	return 0;
}

int CFunctions::base64_encode( lua_State* luaVM )
{
	if( luaVM )
	{
		CLuaArguments args;
		if( lua_type( luaVM, 1 ) == LUA_TSTRING || lua_type( luaVM, 1 ) == LUA_TNUMBER )
		{
			args.PushString( base64::encode( lua_tostring( luaVM, 1 ) ).c_str( ) );
		}
		else
		{
			luaL_error( luaVM, "Bad argument @ 'base64_encode'" );
			args.PushBoolean( false );
		}
		args.PushArguments( luaVM );
		return 1;
	}
	return 0;
}
