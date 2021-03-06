/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   InvisibleState.hh
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

#ifndef InvisibleState_HH
#define InvisibleState_HH

#include "RestFrames/State.hh"

using namespace std;

namespace RestFrames {

  ///////////////////////////////////////////////
  // InvisibleState class
  ///////////////////////////////////////////////
  class InvisibleState : public State {
  public:
    InvisibleState(const string& sname, const string& stitle);
    InvisibleState();
    virtual ~InvisibleState();

    static InvisibleState& Empty();

    virtual void Clear();

    virtual void AddFrame(RestFrame& frame);

    virtual void SetParentJigsaw(Jigsaw& jigsaw);
    virtual void SetChildJigsaw(Jigsaw& jigsaw);

    virtual double GetMinimumMass() const;
    virtual void FillInvisibleMassJigsawDependancies(RestFrames::RFList<Jigsaw>& jigsaws) const;

  private:
    static InvisibleState m_Empty;
    void Init();
 
  };

}

#endif
