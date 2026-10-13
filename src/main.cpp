// Minimal Geant4 Simulation, with agentic support
// This is boilerplate code using Geant4 (compilant with ver.11.4.3)
// It has optional guidelines for agentic support, 
// tasked with updating and maintaing the build chain (cmake) and the
// user documentation.
// github.com/gustavogx/


#include "DefaultGeometry.hpp"
#include "ActionInitialization.hpp"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"

int main(int argc, char** argv)
{
	// Create a run manager appropriate for this Geant4 build
	// (sequential or multi-threaded, depending on how G4 was compiled).
	auto runManager =
		std::unique_ptr<G4RunManager>(
			G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default)
		);

	// Mandatory user initializations 
	runManager->SetUserInitialization(new DefaultGeometry());
	runManager->SetUserInitialization(new FTFP_BERT());
	runManager->SetUserInitialization(new ActionInitialization());

	// Initialize the simulation kernel
	runManager->Initialize();

	// Transport one geantino
	runManager->BeamOn(1);

	return 0;
}
