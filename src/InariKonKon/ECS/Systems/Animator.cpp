#include "InariKonKon/ECS/Systems/Animator.hpp"

//#include "InariKonKon/Utility/EasingFunctions.hpp"
#include "InariKonKon/ECS/Entities/Entity.hpp"

namespace ikk
{
    void Animator::operator()(const Entity& entity, Transform3D& component, const Time& dt) const noexcept
    {
        //TODO:
        //Interpolate between current and target
        //For now, just set current to target

        //static float animTime = 0.f;
        //static float animDuration = 5.f;

        //animTime += dt.asSeconds();

        //float progress = std::clamp(animTime / animDuration, 0.f, 1.f);
        //float e = EasingFuncs::EaseIn::Quad(Clamped<float,0.f,1.f>{progress});

        //component.m_localPosition = component.m_startPosition * (1.f - e) + component.m_targetPosition * e;

        //component.m_localPosition = component.m_targetPosition;
        //component.m_localRotation = component.m_targetRotation;
        //component.m_localScale = component.m_targetScale;
    }
}