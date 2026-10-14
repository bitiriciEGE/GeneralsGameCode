/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2026 Egecan Cihan
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

// FILE: ProductionSpeedUpgrade.cpp ///////////////////////////////////////////////////////////////
// Desc:	 MOD: makes the ProductionUpdate of this one building faster, e.g. a factory add-on module
//
//	Behavior = ProductionSpeedUpgrade ModuleTag_XX
//	  TriggeredBy = Upgrade_SomeObjectUpgrade
//	  SpeedBonus  = 25%   ; units and upgrades from this building take 1 / 1.25 of the time
//	End
//
// The speed lives in the building's ProductionUpdate, which saves it, so this module keeps no state
// of its own. It stays with the building when the building is captured.
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/ProductionSpeedUpgrade.h"
#include "GameLogic/Module/ProductionUpdate.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void ProductionSpeedUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p)
{
  UpgradeModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] =
	{
		{ "SpeedBonus",	INI::parsePercentToReal,	nullptr, offsetof( ProductionSpeedUpgradeModuleData, m_speedBonus ) },
		{ nullptr, nullptr, nullptr, 0 }
	};
  p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
ProductionSpeedUpgrade::ProductionSpeedUpgrade( Thing *thing, const ModuleData* moduleData ) :
							UpgradeModule( thing, moduleData )
{

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
ProductionSpeedUpgrade::~ProductionSpeedUpgrade()
{

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void ProductionSpeedUpgrade::upgradeImplementation()
{
	const ProductionSpeedUpgradeModuleData *md = getProductionSpeedUpgradeModuleData();

	ProductionUpdate *production = (ProductionUpdate *)getObject()->findUpdateModule( NAMEKEY( "ProductionUpdate" ) );
	if( production == nullptr )
	{
		DEBUG_CRASH(( "ProductionSpeedUpgrade on %s needs a ProductionUpdate module", getObject()->getTemplate()->getName().str() ));
		return;
	}

	production->scaleProductionSpeed( 1.0f + md->m_speedBonus );

}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void ProductionSpeedUpgrade::crc( Xfer *xfer )
{

	// extend base class
	UpgradeModule::crc( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void ProductionSpeedUpgrade::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpgradeModule::xfer( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void ProductionSpeedUpgrade::loadPostProcess()
{

	// extend base class
	UpgradeModule::loadPostProcess();

}
