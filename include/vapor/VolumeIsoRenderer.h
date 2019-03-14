#pragma once

#include <vapor/VolumeRenderer.h>
#include <vapor/VolumeAlgorithm.h>
#include <glm/fwd.hpp>

using std::string;
using std::vector;

namespace VAPoR {

class RENDER_API VolumeIsoRenderer : public VolumeRenderer {
public:
    VolumeIsoRenderer(const ParamsMgr *pm, std::string &winName, std::string &dataSetName, std::string &instName, DataMgr *dataMgr);
    ~VolumeIsoRenderer();

    static std::string GetClassType() { return ("VolumeIso"); }
};

};    // namespace VAPoR
