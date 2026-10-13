#pragma once

#include "G4VUserActionInitialization.hh"

// ActionInitialization registers user actions with the run manager.
// Add further user actions (stepping, event, run) in Build().
class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization()  = default;
    ~ActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build()          const override;
};
