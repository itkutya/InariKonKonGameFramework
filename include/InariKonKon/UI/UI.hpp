#ifndef IKK_UI_HPP
#define IKK_UI_HPP

#include "InariKonKon/ECS/Entities/Entity.hpp"
#include "InariKonKon/Assets/Model/Model.hpp"

namespace ikk
{
    class [[nodiscard]] UI : public Entity
    {
    public:
        virtual ~UI() noexcept;

        const Model& getModel() const noexcept;
    protected:
        [[nodiscard]] UI(Vec2f position, Vec2f size, Degreef rotation) noexcept;

        UI(const UI&) noexcept = default;
        UI(UI&&) noexcept = default;

        UI& operator=(const UI&) noexcept = default;
        UI& operator=(UI&&) noexcept = default;

        Model m_model =
            {
            std::vector<UIVertex>
                {
                    {{0.f, 0.f }}, {{0.f, 1.f }},
                    {{1.f, 0.f }}, {{1.f, 1.f }}
                },
            std::vector<std::uint32_t>
                {
                    0, 1, 2,
                    2, 1, 3
                }
            };
    private:
    };
}

#endif