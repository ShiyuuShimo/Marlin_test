#ifndef MyProcessor_h
#define MyProcessor_h 1

#include "marlin/Processor.h"
#include "lcio.h"

#include "TTree.h"
#include "TFile.h"

using namespace lcio ;
using namespace marlin ;

class MyProcessor : public Processor {
  
 public:
  
  virtual Processor*  newProcessor() { return new MyProcessor ; }
  
  
  MyProcessor() ;
  
  virtual void init() ;
  
  virtual void processRunHeader( LCRunHeader* run ) ;

  virtual void processEvent( LCEvent * evt ) ; 
  
  virtual void check( LCEvent * evt ) ; 
  
  virtual void end() ;

  TFile* _file;       // output root file 
  TTree* _tree;       // output root tree
  int    _npfos;      // number of reconstructed particles
  double _pfo_e[500]; // reserve memory for energies. 500 : maximum number of reconstructed particles per event
  double _pfo_px[500]; 
  double _pfo_py[500];
  double _pfo_pz[500];

} ;

#endif


