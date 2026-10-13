#include "PrimaryGeneratorAction.hpp"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	fParticleGun = std::make_unique<G4ParticleGun>(1); // number of particles

	// Geantino: a non-interacting tracking particle, ideal for geometry checks
	auto table    = G4ParticleTable::GetParticleTable();
	auto geantino = table->FindParticle("geantino");

	fParticleGun->SetParticleDefinition(geantino);
	fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.)); // world center
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.)); // +Z
	fParticleGun->SetParticleEnergy(1.0 * GeV);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
	fParticleGun->GeneratePrimaryVertex(event);
}
