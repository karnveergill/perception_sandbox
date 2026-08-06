#pragma once

#include "perception/core/VersionGenerated.hpp"
#include <string_view>

namespace perception::core
{
    constexpr int VersionMajor()
    {
        return PERCEPTION_VERSION_MAJOR;
    }
    
    constexpr int VersionMinor()
    {
        return PERCEPTION_VERSION_MINOR;
    }
    
    constexpr int VersionPatch()
    {
        return PERCEPTION_VERSION_PATCH;
    }
    
    constexpr std::string_view VersionString()
    {
        return PERCEPTION_VERSION_STRING;
    }
} // namespace perception::core