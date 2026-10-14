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

// FILE: ProductionSpeedUpgrade.h /////////////////////////////////////////////////////////////////
// Desc:	 MOD: makes the ProductionUpdate of this one building faster, e.g. a factory add-on module
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "GameLogic/Module/UpgradeModule.h"

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class Thing;

//-----------------------------------------------------------------------------
class ProductionSpeedUpgradeModuleData : public UpgradeModuleData
{
public:
	Real m_speedBonus;	///< 0.25 means this building produces 25% faster

	ProductionSpeedUpgradeModuleData()
	{
		m_speedBonus = 0.0f;
	}

	static void buildFieldParse(MultiIniFieldParse& p);
};

//-------------------------------------------------------------------------------------------------
/** The production speed upgrade module */
//-------------------------------------------------------------------------------------------------
class ProductionSpeedUpgrade : public UpgradeModule
{

	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( ProductionSpeedUpgrade, "ProductionSpeedUpgrade" )
	MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA( ProductionSpeedUpgrade, ProductionSpeedUpgradeModuleData );

public:

	ProductionSpeedUpgrade( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype defined by MemoryPoolObject

protected:

	virtual void upgradeImplementation() override; ///< Here's the actual work of Upgrading
	virtual Bool isSubObjectsUpgrade() override { return false; }

};
