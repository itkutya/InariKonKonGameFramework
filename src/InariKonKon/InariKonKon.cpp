#include "InariKonKon/InariKonKon.hpp"

#include "InariKonKon/ExternalLibraries/ExternalLibraries.hpp"

namespace ikk
{
    bool ___::init()
    {
        return ExternalLibraries::getInstance().init().has_value();
    }
}