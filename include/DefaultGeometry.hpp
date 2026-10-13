#pragma once

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

// DefaultGeometry defines the simulation world: a 1 m air cube
// containing a lead-oxide (G4_LEAD_OXIDE) cylindrical target.
// Extend Construct() to add further volumes inside the world.
class DefaultGeometry : public G4VUserDetectorConstruction
{
public:
	DefaultGeometry()  = default;
	~DefaultGeometry() override = default;

	G4VPhysicalVolume* Construct() override;
};
