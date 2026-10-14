/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: GrantUpgradeCreate.cpp ////////////////////////////////////////////////////////////////////////
// Author: Kris Morness, April 2002
// Desc:   GrantUpgrade create module
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#define DEFINE_OBJECT_STATUS_NAMES
#include "Common/Player.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/Xfer.h"
#include "GameLogic/Module/GrantUpgradeCreate.h"
#include "GameLogic/Object.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
GrantUpgradeCreateModuleData::GrantUpgradeCreateModuleData()
{
	m_onlyForComputerPlayers = FALSE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void GrantUpgradeCreateModuleData::buildFieldParse(MultiIniFieldParse& p)
{
  CreateModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] =
	{
		{ "UpgradeToGrant",	INI::parseAsciiString,							nullptr, offsetof( GrantUpgradeCreateModuleData, m_upgradeName ) },
		{ "ExemptStatus",		ObjectStatusMaskType::parseFromINI, nullptr, offsetof( GrantUpgradeCreateModuleData, m_exemptStatus ) },
		{ "OnlyForComputerPlayers",	INI::parseBool,				nullptr, offsetof( GrantUpgradeCreateModuleData, m_onlyForComputerPlayers ) },
		{ nullptr, nullptr, nullptr, 0 }
	};

  p.add(dataFieldParse);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
GrantUpgradeCreate::GrantUpgradeCreate( Thing *thing, const ModuleData* moduleData ) : CreateModule( thing, moduleData )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
GrantUpgradeCreate::~GrantUpgradeCreate()
{

}

//-------------------------------------------------------------------------------------------------
/** The create callback. */
//-------------------------------------------------------------------------------------------------
void GrantUpgradeCreate::onCreate()
{

	if( !isGrantAllowed() )
		return;

	ObjectStatusMaskType exemptStatus = getGrantUpgradeCreateModuleData()->m_exemptStatus;
	ObjectStatusMaskType currentStatus = getObject()->getStatusBits();
	if( exemptStatus.test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
	{
		if(	!currentStatus.test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
		{
			const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade( getGrantUpgradeCreateModuleData()->m_upgradeName );
			if( !upgradeTemplate )
			{
				DEBUG_CRASH( ("GrantUpdateCreate for %s can't find upgrade template %s.", getObject()->getName().str(), getGrantUpgradeCreateModuleData()->m_upgradeName.str() ) );
				return;
			}

			Player *player = getObject()->getControllingPlayer();
			if( upgradeTemplate->getUpgradeType() == UPGRADE_TYPE_PLAYER )
			{
				// get the player
				player->addUpgrade( upgradeTemplate, UPGRADE_STATUS_COMPLETE );
			}
			else
			{
				getObject()->giveUpgrade( upgradeTemplate );
			}

			player->getAcademyStats()->recordUpgrade( upgradeTemplate, TRUE );
		}
	}

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GrantUpgradeCreate::onBuildComplete()
{
	if( ! shouldDoOnBuildComplete() )
		return;

	CreateModule::onBuildComplete(); // extend

	if( !isGrantAllowed() )
		return;

	const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade( getGrantUpgradeCreateModuleData()->m_upgradeName );
	if( !upgradeTemplate )
	{
		DEBUG_CRASH( ("GrantUpdateCreate for %s can't find upgrade template %s.", getObject()->getName().str(), getGrantUpgradeCreateModuleData()->m_upgradeName.str() ) );
		return;
	}

	if( upgradeTemplate->getUpgradeType() == UPGRADE_TYPE_PLAYER )
	{
		// get the player
		Player *player = getObject()->getControllingPlayer();
		player->addUpgrade( upgradeTemplate, UPGRADE_STATUS_COMPLETE );
	}
	else
	{
		getObject()->giveUpgrade( upgradeTemplate );
	}
}

//-------------------------------------------------------------------------------------------------
/** MOD: OnlyForComputerPlayers lets AI players skip choices the skirmish AI cannot make, such as
	* a factory add-on module. */
//-------------------------------------------------------------------------------------------------
Bool GrantUpgradeCreate::isGrantAllowed() const
{
	if( !getGrantUpgradeCreateModuleData()->m_onlyForComputerPlayers )
		return TRUE;

	const Player *player = getObject()->getControllingPlayer();
	const Bool allowed = player != nullptr && player->getPlayerType() == PLAYER_COMPUTER;
	DEBUG_LOG(( "GrantUpgradeCreate OnlyForComputerPlayers on %s: %s", getObject()->getTemplate()->getName().str(), allowed ? "allowed" : "skipped" ));
	return allowed;
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void GrantUpgradeCreate::crc( Xfer *xfer )
{

	// extend base class
	CreateModule::crc( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void GrantUpgradeCreate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	CreateModule::xfer( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void GrantUpgradeCreate::loadPostProcess()
{

	// extend base class
	CreateModule::loadPostProcess();

}
