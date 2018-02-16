//************************************************************************
//                                                                       *
//           Copyright (C)  2004                                         *
//     University Corporation for Atmospheric Research                   *
//           All Rights Reserved                                         *
//                                                                       *
//************************************************************************
//
//  File:       PlotParams.h
//
//  Author:     Samuel Li
//              National Center for Atmospheric Research
//              PO 3000, Boulder, Colorado
//
//  Date:       December 2017
//
//  Description:    Defines the PlotParams class.
//

#ifndef PLOTPARAMS_H
#define PLOTPARAMS_H

#include <vapor/RenderParams.h>

namespace VAPoR {

/// PlotParams inherits RenderParams.
class PlotParams : public RenderParams {
  public:
    /// Constructor 1
    PlotParams(DataMgr *dmgr, ParamsBase::StateSave *ssave);
    /// Constructor 2
    PlotParams(DataMgr *dmgr, ParamsBase::StateSave *ssave, XmlNode *node);
    /// Destructor
    ~PlotParams();

    /// In ``time mode,'' these 2 methods get/set the time range.
    std::vector<long int> GetMinMaxTS() const;
    void SetMinMaxTS(const std::vector<long int> &);

    /// In ``time mode,'' these 2 methods get/set the single point position
    std::vector<double> GetSinglePoint() const;
    void SetSinglePoint(const std::vector<double> &point);

    /// In ``space mode,'' these 4 methods get/set the point 1 and point 2 positions
    std::vector<double> GetPoint1() const;
    std::vector<double> GetPoint2() const;
    void SetPoint1(const std::vector<double> &point);
    void SetPoint2(const std::vector<double> &point);

    /// Get/set the current operational mode: space or time.
    /// true == Space; false == time
    bool GetSpaceTimeMode() const;
    void SetSpaceTimeMode(bool);

    long GetNumOfSamples() const;
    void SetNumOfSamples(long);

    static string GetClassType() {
        return ("PlotParams");
    }

    // virtual functions required by RenderParams
    virtual bool IsOpaque() const {
        return true;
    }
    virtual bool usingVariable(const std::string &varname) {
        return false;
    }

  private:
    static const string _minMaxTSTag;
    static const string _spaceTimeTag; // Space=true, Time=false

    static const string _p1Tag;         // point1 in space mode
    static const string _p2Tag;         // point2 in space mode
    static const string _numSamplesTag; // number of samples in space mode
    static const string _singlePtTag;   // a single point in time mode
};

}; // End namespace VAPoR
#endif
