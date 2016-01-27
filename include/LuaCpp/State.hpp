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

#ifndef LUA_CPP_STATE_HPP
#define LUA_CPP_STATE_HPP

#include <LuaCpp/Build.hpp>
#include <tuple>
#include <string>

// Forward declarations
class lua_State;

namespace Lua
{

	////////////////////////////////////////////////////////////////
	/// \brief Loadable base class.
	///
	////////////////////////////////////////////////////////////////
	class LUACPP_API State
	{

	public:

		// Public typedefs
		typedef std::tuple<bool, std::string> Return;

		////////////////////////////////////////////////////////////////
		/// \brief	Creates a new state that will be deallocated at destruction.
		///
		////////////////////////////////////////////////////////////////
		State();

		////////////////////////////////////////////////////////////////
		/// \brief	Constructor.
		///			Sets a lua state from an external source.
		///			The state will not the deallocated at desturction.
		///
		////////////////////////////////////////////////////////////////
		State(lua_State * p_pLuaState);

		////////////////////////////////////////////////////////////////
		/// \brief	Destructor.
		///			Destroy the lua state if it's not from an external source.
		///
		////////////////////////////////////////////////////////////////
		~State();

		////////////////////////////////////////////////////////////////
		/// \brief Open the standard lua libraries for this state.
		///
		////////////////////////////////////////////////////////////////
		void OpenStandardLibs();

		////////////////////////////////////////////////////////////////
		/// \brief Execute script from file.
		///
		/// \param p_Filepath Path to the lua file.
		///
		////////////////////////////////////////////////////////////////
		Return ExecuteFile(const std::string & p_Filepath);

		////////////////////////////////////////////////////////////////
		/// \brief Execute script from string.
		///
		/// \param p_Script String containing the lua script.
		///
		////////////////////////////////////////////////////////////////
		Return ExecuteString(const std::string & p_Script);

	private:

		lua_State *		m_pState;			///< Pointer to the lua state.
		bool			m_ExternalState;	///< Flag for checking if we should clean up the lua state at destruction.

	};


};

#endif