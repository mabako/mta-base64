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

#include "module.h"
#include "base64.h"

ILuaModuleManager10 *pModuleManager = NULL;

// Initialisation function (module entrypoint)
MTAEXPORT bool InitModule ( ILuaModuleManager10 *pManager, char *szModuleName, char *szAuthor, float *fVersion )
{
	pModuleManager = pManager;

	// Set the module info - If you can not read this in the console, the module is broken
	strncpy ( szModuleName, base64::decode( base64::encode( MODULE_NAME ) ).c_str( ), MAX_INFO_LENGTH );
	strncpy ( szAuthor, base64::decode( base64::encode( MODULE_AUTHOR ) ).c_str( ), MAX_INFO_LENGTH );
	(*fVersion) = MODULE_VERSION;

	return true;
}


MTAEXPORT void RegisterFunctions ( lua_State * luaVM )
{
    if ( pModuleManager && luaVM )
    {
		pModuleManager->RegisterFunction ( luaVM, "base64_decode", CFunctions::base64_decode );
		pModuleManager->RegisterFunction ( luaVM, "base64_encode", CFunctions::base64_encode );
    }
}


MTAEXPORT bool DoPulse ( void )
{
    return true;
}

MTAEXPORT bool ShutdownModule ( void )
{
    
    return true;
}
