/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   SetMassInvJigsaw.cc
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

#include "RestFrames/SetMassInvJigsaw.hh"

using namespace std;

namespace RestFrames {

  ///////////////////////////////////////////////
  //SetMassInvJigsaw class methods
  ///////////////////////////////////////////////
  SetMassInvJigsaw::SetMassInvJigsaw(const string& sname, const string& stitle) : 
    InvisibleJigsaw(sname, stitle, 1, 0) {}

  SetMassInvJigsaw::SetMassInvJigsaw() : InvisibleJigsaw() {}
 
  SetMassInvJigsaw::~SetMassInvJigsaw() {}

  void SetMassInvJigsaw::Clear(){
    InvisibleJigsaw::Clear();
  }

  SetMassInvJigsaw& SetMassInvJigsaw::Empty(){
    return SetMassInvJigsaw::m_Empty;
  }

  bool SetMassInvJigsaw::AnalyzeEvent(){
    if(!IsSoundMind())
      return SetSpirit(false);
    
    TLorentzVector inv_P = GetParentState().GetFourVector();
    double M = GetChildState(0).GetMinimumMass();
    
    inv_P.SetVectM(inv_P.Vect(),M);
    GetChildState(0).SetFourVector(inv_P);

    return SetSpirit(true);
  }

  SetMassInvJigsaw SetMassInvJigsaw::m_Empty;

}
