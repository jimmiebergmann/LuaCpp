// ///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 Jimmie Bergmann - jimmiebergmann@gmail.com
//
// This software is provided 'as-is', without any express or
// implied warranty. In no event will the authors be held
// liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute
// it freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but
//    is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any
//    source distribution.
// ///////////////////////////////////////////////////////////////////////////

#include <LuaCpp/State.hpp>
#include <iostream>

#include <lua.hpp>

namespace Lua
{


	State::State() :
		m_pState(luaL_newstate()),
		m_ExternalState(false)
	{

	}

	State::State(lua_State * p_pLuaState) :
		m_pState(p_pLuaState),
		m_ExternalState(true)
	{
	}

	State::~State()
	{
		if (m_ExternalState)
		{
			lua_close(m_pState);
			m_pState = NULL;
		}
	}

	void State::OpenStandardLibs()
	{
		luaL_openlibs(m_pState);
	}

	State::Return State::ExecuteFile(const std::string & p_Filepath)
	{
		if(luaL_dofile(m_pState, p_Filepath.c_str()) != false)
		{
			// Something got messed up at execution

			// Get the stack size.
			int stackSize = lua_gettop(m_pState);

			// Is there any error message on the stack?
			if (stackSize)
			{
				// Get the error message, put it into a std::string
				std::string error = lua_tostring(m_pState, -1);

				// Pop the error message from the stack.
				lua_pop(m_pState, 1);

				// Return false, and the error message
				return std::make_tuple<bool, std::string>(false, error.c_str());
			}
		}

		// Succeeded.
		return std::make_tuple<bool, std::string>(true, "");
	}


	State::Return State::ExecuteString(const std::string & p_Script)
	{
		if (luaL_dostring(m_pState, p_Script.c_str()) != false)
		{
			// Something got messed up at execution

			// Get the stack size.
			int stackSize = lua_gettop(m_pState);

			// Is there any error message on the stack?
			if (stackSize)
			{
				// Get the error message, put it into a std::string
				std::string error = lua_tostring(m_pState, -1);

				// Pop the error message from the stack.
				lua_pop(m_pState, 1);

				// Return false, and the error message
				return std::make_tuple<bool, std::string>(false, error.c_str());
			}
		}

		// Succeeded.
		return std::make_tuple<bool, std::string>(true, "");
	}


};
