#include "MyProcessor.h"
#include <iostream>  

#include <EVENT/LCCollection.h>
#include <EVENT/ReconstructedParticle.h>

// ----- include for verbosity dependend logging ---------
//#include "marlin/VerbosityLevels.h"


using namespace lcio ;
using namespace marlin ;


MyProcessor aMyProcessor ;


MyProcessor::MyProcessor() : Processor("MyProcessor") {
  // Constructor
  // All Marlin processor must inherit Processor class which is defined. 
  // /cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16/include/marlin/Processor.h
  // ////cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16/source/src/Processor.cc
}



void MyProcessor::init() { 

  std::cout << "init() called." << std::endl;

  // TFile creation
  _file = new TFile("output.root","RECREATE");
  // TTree creation
  _tree = new TTree("evt","");
  // Register variables to TTree 
  _tree->Branch( "npfos" , &_npfos , "npfos/I"        ); // I : integer, O : boolean, F : float, D : double
  _tree->Branch( "pfo_e" , _pfo_e  , "pfo_e[npfos]/D" ); // This is an example to set an Array
  _tree->Branch( "pfo_px" , _pfo_px  , "pfo_px[npfos]/D" );
  _tree->Branch( "pfo_py" , _pfo_py  , "pfo_py[npfos]/D" );
  _tree->Branch( "pfo_pz" , _pfo_pz  , "pfo_pz[npfos]/D" );
 
}


void MyProcessor::processRunHeader( LCRunHeader* run) { 
   
  std::cout << "processRunHeader() called." << std::endl;
 
} 



void MyProcessor::processEvent( LCEvent * evt ) { 

  std::cout << "processEvent() called." << std::endl;

  // Get reconstructed particles (Pandora is a name of algorithm to reconstruct particles)
  LCCollection* colpfo     = evt->getCollection("PandoraPFOs") ;

  int nPFO = colpfo->getNumberOfElements()  ;

  // set number of PFOs to the variable registered to TTree.
  _npfos = nPFO;

  for(int i=0; i< nPFO ; i++){
    // Get a reconstructed particles
    ReconstructedParticle* p = dynamic_cast<ReconstructedParticle*>( colpfo->getElementAt( i ) ) ;
    // Access its parameters
    double e = p->getEnergy();
    const double* mom  = p->getMomentum();
    double m = 0;

    // set energy of this PFO to the variable registered to TTree.
    _pfo_e[i] = e;

    // get momentum of particles. shimo.
    _pfo_px[i] = mom[0];
    _pfo_py[i] = mom[1];
    _pfo_pz[i] = mom[2];

    // get mass. shimo.
     m = ( mom[0] * mom[0] + mom[1] * mom[1] + mom[2] * mom[2] ) / ( 2 * e ); 
  
    std::cout << "i = " << i << ", energy = " << e << " [GeV], (px, py, pz) = (" << mom[0] << ", " << mom[1] << ", " << mom[2] << "), mass = " << m << "[GeV]" <<  std::endl;

   }

  // Don't forget to call fill whenever you want.
  // At this point, the variables you set above will be actually saved.
  _tree->Fill();

}



void MyProcessor::check( LCEvent * evt ) { 

  std::cout << "check() called." << std::endl;

}


void MyProcessor::end(){ 

  std::cout << "end() called." << std::endl;

  // Write TTree data to output file
  _file->Write();

}

