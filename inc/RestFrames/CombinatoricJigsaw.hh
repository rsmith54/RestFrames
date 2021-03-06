/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   CombinatoricJigsaw.hh
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

#ifndef CombinatoricJigsaw_HH
#define CombinatoricJigsaw_HH

#include "RestFrames/Jigsaw.hh"
#include "RestFrames/CombinatoricGroup.hh"
#include "RestFrames/CombinatoricState.hh"

using namespace std;

namespace RestFrames {

  class CombinatoricJigsaw : public Jigsaw {
  public:
    //constructor and destructor
    CombinatoricJigsaw(const string& sname, const string& stitle);
    CombinatoricJigsaw();
    virtual ~CombinatoricJigsaw();

    virtual void Clear();

    static CombinatoricJigsaw& Empty();

    virtual void SetGroup(Group& group = Group::Empty());
    virtual CombinatoricGroup& GetGroup() const;

    virtual void SetParentState(State& state = State::Empty());
    virtual CombinatoricState& GetParentState() const;
    virtual CombinatoricState& GetChildState(int i) const;

    virtual void AddFrame(RestFrame& frame, int i = 0);
    virtual void AddFrames(const RestFrames::RFList<RestFrame>& frames, int i = 0);

    virtual bool InitializeJigsawExecutionList(RestFrames::RFList<Jigsaw>& exec_jigsaws);

    virtual bool AnalyzeEvent();
  
  protected:
    virtual bool InitializeCombinatoric();
    virtual bool LoopCombinatoric();
    virtual double EvaluateMetric() const = 0;

    RestFrames::RFList<VisibleState> m_InputStates;
    map<const State*, int>  m_NForChild;
    map<const State*, bool> m_NExclusive;

    virtual CombinatoricState& GetNewChildState();
 
    RestFrames::RFList<Jigsaw> m_ExecuteJigsaws;
    bool ExecuteDependancyJigsaws();
    
  private:
    void Init();
  };

}

#endif
