/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   InvisibleRecoFrame.hh
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

#ifndef InvisibleRecoFrame_HH
#define InvisibleRecoFrame_HH

#include "RestFrames/InvisibleFrame.hh"
#include "RestFrames/ReconstructionFrame.hh"

using namespace std;

namespace RestFrames {

  ///////////////////////////////////////////////
  // InvisibleRecoFrame class
  ///////////////////////////////////////////////
  class InvisibleRecoFrame : public InvisibleFrame<ReconstructionFrame> {
  public:
    InvisibleRecoFrame(const string& sname, const string& stitle);
    virtual ~InvisibleRecoFrame();

    double GetMinimumMass() const;
    void SetMinimumMass(double M);

  protected:
    double m_MassMin;

  private:
    void Init();
   
  };

}

#endif
