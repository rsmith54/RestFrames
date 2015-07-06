/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   RFrame.hh
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

#ifndef RFrame_HH
#define RFrame_HH

#include "RestFrames/RestFrame.hh"

using namespace std;

namespace RestFrames {

  class Group;
  class StateList;

  ///////////////////////////////////////////////
  // RFrame class
  ///////////////////////////////////////////////
  class RFrame : public virtual RestFrame {
  public:
    RFrame(const string& sname, const string& stitle);
    RFrame();
    virtual ~RFrame();

    /// \brief Clears RFrame of all connections to other objects
    virtual void Clear();

    virtual void SetGroup(Group& group);
    Group& GetGroup() const;

    RestFrames::RFList<Group> GetListGroups() const;

    virtual bool InitializeStates(const StateList& states, const RestFrames::RFList<Group>& groups);
    virtual void ClearEventRecursive();
    virtual bool AnalyzeEventRecursive();

  protected:
    vector<StateList> m_ChildStates;
    Group* m_GroupPtr;

    virtual bool InitializeStatesRecursive(const StateList& states, const RestFrames::RFList<Group>& groups);
    virtual bool InitializeNoGroupStates(const StateList& states);
    virtual bool InitializeGroupStates(const RestFrames::RFList<Group>& groups);

    void FillListGroupsRecursive(RestFrames::RFList<Group>& groups) const;

  private:
    void Init();

  };

}

#endif
