#include "Builder.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;


void Builder::buildBarracks(UnitType Terran_Barracks){

}

void Builder::buildSupply(Unit supplyBuilder, UnitType supplyProviderType) {
	if (supplyProviderType.isBuilding())
	{
		TilePosition targetBuildLocation = Broodwar->getBuildLocation(supplyProviderType, supplyBuilder->getTilePosition());
		if (targetBuildLocation)
		{
			// Register an event that draws the target build location
			Broodwar->registerEvent([targetBuildLocation, supplyProviderType](Game*)
			{
				Broodwar->drawBoxMap(Position(targetBuildLocation),
					Position(targetBuildLocation + supplyProviderType.tileSize()),
					Colors::Blue);
			},
				nullptr,  // condition
				supplyProviderType.buildTime() + 100);  // frames to run

														// Order the builder to construct the supply structure
			supplyBuilder->build(supplyProviderType, targetBuildLocation);
		}
	}
	else
	{
		// Train the supply provider (Overlord) if the provider is not a structure
		supplyBuilder->train(supplyProviderType);
	}
}
