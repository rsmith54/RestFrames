/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   VisibleState.cc
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

#include "RestFrames/VisibleState.hh"
#include "RestFrames/VisibleRecoFrame.hh"
#include "RestFrames/Jigsaw.hh"

using namespace std;

namespace RestFrames {

  VisibleState::VisibleState(const string& sname, const string& stitle)
    : State(sname, stitle) 
  {
    Init();
  }

  VisibleState::VisibleState() : State() {}

  VisibleState::~VisibleState() {}

  void VisibleState::Init(){
    m_Type = kVisibleState;
    m_FramePtr = nullptr;
  }

  void VisibleState::Clear(){
    m_FramePtr = nullptr;
    State::Clear();
  }

  VisibleState& VisibleState::Empty(){
    return VisibleState::m_Empty;
  }

  void VisibleState::AddFrame(RestFrame& frame){
    if(!frame) return;
    if(!frame.IsVisibleFrame() || !frame.IsRecoFrame()) return;
    m_FramePtr = static_cast<VisibleRecoFrame*>(&frame);
    m_Frames.Clear();
    m_Frames += frame;
  }

  bool VisibleState::IsFrame(const RestFrame& frame) const {
    if(!frame) return false;
    if(!m_FramePtr) return false;
    return *m_FramePtr == frame;
  }

  bool VisibleState::IsFrames(const RFList<RestFrame>& frames) const {
    return IsFrame(frames[0]);
  }

  RestFrame& VisibleState::GetFrame() const {
    if(m_FramePtr) 
      return *m_FramePtr;
    else
      return RestFrame::Empty();
  }

  void VisibleState::SetLabFrameFourVector(){
    if(!m_FramePtr) return;
    SetFourVector(m_FramePtr->GetLabFrameFourVector());
  }

  VisibleState VisibleState::m_Empty;
}
