// Default geometry: cube of air (1m^3) with lead-oxide target

#include "DefaultGeometry.hpp"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

G4VPhysicalVolume* DefaultGeometry::Construct()
{
	// Material 
	// Get access to the NIST (National Institute of Standards and Technology)
	// https://geant4.web.cern.ch/documentation/dev/bfad_html/ForApplicationDevelopers/Appendix/materialNames.html
	auto nistTable = G4NistManager::Instance();

	// Get "air" from the NIST table
	auto air = nistTable->FindOrBuildMaterial("G4_AIR");

	// World volume: 1 m cube of air (each entry is the semi-axis)
	double worldHalfSize = 0.5*m;

	auto solidWorld	= new G4Box("World", worldHalfSize, worldHalfSize, worldHalfSize);
	auto logicWorld	= new G4LogicalVolume(solidWorld, air, "World");
	auto physWorld	= new G4PVPlacement(	
		nullptr,         // no rotation
		G4ThreeVector(), // at origin
		logicWorld,		 // logic volume
		"World",		 // name
		nullptr,		 // no mother volume (this IS the world)
		false,			 // has many copies?
		0,				 // copy number
		true			 // check overlaps
	);

	// Get "Lead Oxide" crystal from the NIST table
	auto crystal = nistTable->FindOrBuildMaterial("G4_LEAD_OXIDE");

	// Target semi-axis
	double targetRadius =  5.0*cm;
	double targetLength = 20.0*cm;
	// Target position
	auto posTarget = G4ThreeVector(0.0,0.0, 25.0*cm);
	
	auto solidTarget = new G4Tubs("Target", 0, targetRadius, targetLength, 0, 2*CLHEP::pi);
	auto logicTarget = new G4LogicalVolume(solidTarget, crystal, "Target");
	[[maybe_unused]] auto physTarget  = new G4PVPlacement(	
		nullptr,	// no rotation
		posTarget, 	// at origin
		logicTarget,// logic volume
		"Target",	// name
		logicWorld,	// no mother volume (this IS the world)
		false,		// has many copies?
		0,			// copy number
		true		// check overlaps
	);

	return physWorld;
}
