#include "DefaultGeometry.hpp"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

G4VPhysicalVolume* DefaultGeometry::Construct()
{
    // --- Material --------------------------------------------------------
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

    // --- World volume: 1 m cube of air -----------------------------------
    const G4double halfSide = 0.5 * m;

    G4Box* worldSolid = new G4Box("World", halfSide, halfSide, halfSide);

    G4LogicalVolume* worldLogical =
        new G4LogicalVolume(worldSolid, air, "World");

    G4VPhysicalVolume* worldPhysical =
        new G4PVPlacement(nullptr,        // no rotation
                          G4ThreeVector(), // at origin
                          worldLogical,
                          "World",
                          nullptr,         // no mother volume (this IS the world)
                          false,
                          0,               // copy number
                          true);           // check overlaps

    return worldPhysical;
}
