/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   HistPlotVar.hh
///
///  \author Christopher Rogan
///          (crogan@cern.ch)
///
///  \date   2015 Jul
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

#ifndef HistPlotVar_HH
#define HistPlotVar_HH

#include <string>

using namespace std;

namespace RestFrames {

  ///////////////////////////////////////////////
  // HistPlotVar class
  ///////////////////////////////////////////////
  class HistPlotVar {

  public:
    HistPlotVar(const string& name, const string& title, 
		double minval, double maxval,
		const string& unit);
    ~HistPlotVar();

    void operator=(double val) const;

    operator double() const;

    double GetVal() const;

    string GetName() const;

    string GetTitle() const;

    double GetMin() const;

    double GetMax() const;

    string GetUnit() const;

  private:
    string m_Name;
    string m_Title;
    string m_Unit;
    double m_Min;
    double m_Max;
    mutable double m_Val;

  };

}

#endif
