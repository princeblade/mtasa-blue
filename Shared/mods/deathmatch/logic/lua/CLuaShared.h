/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto 
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        Shared/mods/logic/lua/CLuaShared.h
*
*****************************************************************************/
#pragma once

#define LUA_GC_EXTRA_BYTES 30       // Used in hack to make lua GC more aggressive when using OOP Matrix & Vector

// Lua function definitions (shared)
#include "luadefs/CLuaBitDefs.h"
#include "luadefs/CLuaCryptDefs.h"
#include <luadefs/CLuaFileDefs.h>
#include "luadefs/CLuaMatrixDefs.h"
#include "luadefs/CLuaUTFDefs.h"
#include "luadefs/CLuaUtilDefs.h"
#include "luadefs/CLuaVector2Defs.h"
#include "luadefs/CLuaVector3Defs.h"
#include "luadefs/CLuaVector4Defs.h"
#include "luadefs/CLuaXMLDefs.h"

class CLuaShared
{
public:
    static void EmbedChunkName ( SString strChunkName, const char** pcpOutBuffer, uint* puiOutSize );
    static bool CheckUTF8BOMAndUpdate ( const char** pcpOutBuffer, uint* puiOutSize );
    static void LoadFunctions ( void );
    static void AddClasses ( lua_State* luaVM );
};
