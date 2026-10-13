#include "ActionInitialization.hpp"
#include "PrimaryGeneratorAction.hpp"

void ActionInitialization::BuildForMaster() const
{
    // Nothing needed for the master thread in this minimal setup.
}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction());
}
