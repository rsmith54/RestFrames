/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   DecayGenFrame.hh
///
///  \author Christopher Rogan
///          (crogan@cern.ch)
///
///  \date   2015 Jan
///
//   This file is part of RestFrames.
//
//   RestFrames is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
// 
//   RestFrames is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// 
//   You should have received a copy of the GNU General Public License
//   along with RestFrames. If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////

#ifndef DecayGenFrame_HH
#define DecayGenFrame_HH

#include "RestFrames/DecayFrame.hh"
#include "RestFrames/GeneratorFrame.hh"

using namespace std;

namespace RestFrames {

  class ResonanceGenFrame;

   enum DecayGenType { DGVanilla, DGResonance };

  ///////////////////////////////////////////////
  // DecayGenFrame class
  ///////////////////////////////////////////////
  class DecayGenFrame : public DecayFrame<GeneratorFrame> {
  public:
    DecayGenFrame(const string& sname, const string& stitle);
    virtual ~DecayGenFrame();

    virtual void SetMass(double val);
    virtual double GetMass() const;
    
    bool IsResonanceFrame() const;

    // For two-body decays
    virtual void SetChildMomentum(double val);
    virtual void SetChildGamma(double val);
    virtual void SetCosDecayAngle(double val);
    virtual void SetDeltaPhiDecayPlane(double val);

  protected:
    mutable double m_Mass;
    mutable bool m_MassSet;
  
    DecayGenType m_GType;

    bool m_MarkovChainMC;
    RestFrames::RFList<ResonanceGenFrame> m_Resonances;
    double m_ResPrevMTOT;
    map<const RestFrame*, int>    m_ResIndex;
    map<const RestFrame*, double> m_ResPrevProb;
    map<const RestFrame*, double> m_ResPrevMass;
    
    bool m_Burnt;
    static int m_N_MCMC_BurnIn;
    bool MCMC_BurnIn();
    bool MCMC_Generate();

    // For two-body decays
    double m_ChildP;
    double m_ChildGamma;
    double m_CosDecayAngle;
    double m_DeltaPhiDecayPlane;

    virtual bool IsSoundBody() const;

    virtual void ResetFrame();
    virtual bool GenerateFrame();

    void ResetDecayAngles();
   
    double GenerateTwoBodyMasses(double M, const vector<double>& M_c, vector<double>& M_2b);
    double GenerateTwoBodyRecursive(const vector<double>& M_parent, const vector<double>& M_child,
				    const TVector3& axis_par, const TVector3& axis_perp,
				    vector<TLorentzVector>& P_child);
    virtual bool InitializeGenAnalysis();

  private:
    void Init();

  };

  int DoubleMax(const void *a, const void *b);

}

#endif
