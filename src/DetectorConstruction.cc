//
// ********************************************************************
// * Disclaimer and License                                           *
// *                                                                  *
// * This workshop example is a modifed Basic B4c example proivded by *
// * the Geant4 Collaboration. Modifications from the example have    *
// * been made by Eric King. (9-2-2024)                               *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

#include "DetectorConstruction.hh"
#include "CalorimeterSD.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

namespace B4c
{


G4ThreadLocal
G4GlobalMagFieldMessenger * DetectorConstruction::fMagFieldMessenger = nullptr;

////////////////////////////////////////////////////////////////////////////////

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  //////////////////////////////////////////////////////////////////////////////
  // Create instance of NIST manager
  auto nistManager = G4NistManager::Instance();

  //////////////////////////////////////////////////////////////////////////////
  // Some variables that will tidy up code later A,Z,density,fracMass (maybe show new material)
  G4double a,density,fracMass;
  G4int z;

  ////////////////////////////////////////////////////////////////////////////////
  // Define the Geometry
  
  //////////////////////////////////////////////////////////////////////////////
  // World
  auto worldSizeXY = 1*m;
  auto worldSizeZ  = 2*m;
  nistManager->FindOrBuildMaterial("G4_AIR");
  G4Material * defaultMaterial = G4Material::GetMaterial("G4_AIR");  
  G4Box * worldS = new G4Box("World",worldSizeXY/2., worldSizeXY/2., worldSizeZ/2.);
  G4LogicalVolume * worldLV = new G4LogicalVolume(worldS,defaultMaterial,"World");
  auto worldPV = new G4PVPlacement(nullptr,G4ThreeVector(),worldLV,"World",nullptr,false,0,fCheckOverlaps);

  //////////////////////////////////////////////////////////////////////////////
  // HANDS-ON #1: Detector/Calorimeter
  // Create Lead-Scintillating Fiber Detector material
  // FETCH POLYETHLENE FROM NISTMANAGER





  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  // HANDS-ON #2: Radiator
  // FETCH LEAD (PB) FROM NISTMANAGER






  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  // Visualization attributes
  //worldLV->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VisAttributes * worldVisAtt   = new G4VisAttributes( G4Colour(149./255.,149./255.,100./255.,1.) );
  worldVisAtt->SetForceWireframe(true);
  worldLV->SetVisAttributes(worldVisAtt);

  //////////////////////////////////////////////////////////////////////////////
  // HANDS-ON #3: Visual Attributes



  //////////////////////////////////////////////////////////////////////////////





  //////////////////////////////////////////////////////////////////////////////
  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  //////////////////////////////////////////////////////////////////////////////
  // Always return the physical World
  return worldPV;

}

////////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::ConstructSDandField()
{
  // G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  //////////////////////////////////////////////////////////////////////////////
  // CODEBLOCK #3 ==> Sensitive detectors -- Uncomment 3 lines below after detector is built
//  CalorimeterSD * detectorSD = new CalorimeterSD("dectectorSD","DetectorHitsCollection",1);
//  G4SDManager::GetSDMpointer()->AddNewDetector(detectorSD);
//  SetSensitiveDetector("detectorLV",detectorSD);


  //////////////////////////////////////////////////////////////////////////////
  // Magnetic field
  //
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

}
