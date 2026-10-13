#pragma once

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

// DefaultGeometry defines the simulation world: a 1 m air cube.
// Extend Construct() to add detector volumes inside the world.
class DefaultGeometry : public G4VUserDetectorConstruction
{
public:
    DefaultGeometry()  = default;
    ~DefaultGeometry() override = default;

    G4VPhysicalVolume* Construct() override;
};
