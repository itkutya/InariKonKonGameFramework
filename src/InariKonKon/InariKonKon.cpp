#include "InariKonKon/InariKonKon.hpp"

#include "InariKonKon/Core/ExternalLibraries/ExternalLibraries.hpp"

namespace ikk
{
    bool ___::init()
    {
        return ExternalLibraries::getInstance().init().has_value();
    }
}