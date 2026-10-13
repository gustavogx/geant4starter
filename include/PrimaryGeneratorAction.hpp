#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

#include <memory>

// PrimaryGeneratorAction fires a single geantino from the world center
// along +Z at 1 GeV. Swap the particle type and kinematics here to
// change what is shot into the geometry.
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override = default;

    void GeneratePrimaries(G4Event* event) override;

private:
    std::unique_ptr<G4ParticleGun> fParticleGun;
};
