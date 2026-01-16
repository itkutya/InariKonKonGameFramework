#pragma once

#include "InariKonKon/Utility/NonCopyable.hpp"
#include "InariKonKon/Utility/NonMovable.hpp"

namespace ikk
{
    template<class T>
    class Singleton : public NonCopyable, public NonMovable
    {
    public:
        virtual ~Singleton() noexcept = default;

        [[nodiscard]] static T& getInstance() noexcept;
    protected:
        Singleton() noexcept = default;
    };

    template<class T>
    T& Singleton<T>::getInstance() noexcept
    {
        static T instance;
        return instance;
    }
}