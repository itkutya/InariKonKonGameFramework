#ifndef IKK_EVENT_HPP
#define IKK_EVENT_HPP

#include <type_traits>
#include <filesystem>
#include <expected>
#include <variant>
#include <vector>

#include "InariKonKon/Utility/Error.hpp"

#include "InariKonKon/Input/Joystick.hpp"
#include "InariKonKon/Input/Keyboard.hpp"
#include "InariKonKon/Input/Mouse.hpp"
#include "InariKonKon/Input/Input.hpp"

namespace ikk
{
    //TODO:
    //Figure out a way so that the users can create their own events as well...
    class [[nodiscard]] Event final
    {
    public:
        struct Window
        {
            struct Closed
            {
            };

            struct Resized
            {
                std::uint32_t width;
                std::uint32_t height;
            };

            struct FramebufferResized
            {
                std::uint32_t width;
                std::uint32_t height;
            };

            struct Position
            {
                std::uint32_t x;
                std::uint32_t y;
            };

            struct UnIconified
            {
            };

            struct Iconified
            {
            };

            struct Minimized
            {
            };

            struct Maximized
            {
            };

            struct FocusLost
            {
            };

            struct FocusGained
            {
            };

            struct CursorEntered
            {
            };

            struct CursorLeft
            {
            };

            struct ContentScale
            {
                Vec2f scale;
            };

            struct Refreshed
            {
            };

            struct FileDroped
            {
                std::vector<std::filesystem::path> paths;
            };
        };

        //TODO:
        //Add monitor data...
        struct Monitor
        {
            struct Connected
            {
            };
            
            struct Disconnected
            {
            };
        };

        struct Input
        {
            struct Text
            {
                char32_t unicode;
            };

            struct Keyboard
            {
                ikk::Keyboard::KeyCode  keycode;
                ikk::Keyboard::ScanCode scancode;
                ikk::Input::State       state;
            };

            struct Mouse
            {
                struct Button
                {
                    ikk::Mouse::Button  button;
                    ikk::Input::State   state;
                };

                struct Wheel
                {
                    ikk::Mouse::Wheel   wheel;
                    double              delta;
                };

                struct Move
                {
                    Vec2d position;
                };
            };

            struct Joystick
            {
                struct Connected
                {
                    ikk::Joystick::ID id;
                };
                
                struct Disconnected
                {
                    ikk::Joystick::ID id;
                };

                struct Button
                {
                    ikk::Joystick::ID       id;
                    ikk::Joystick::Button   button;
                    ikk::Input::State       state;
                };

                struct Axis
                {
                    ikk::Joystick::ID   id;
                    ikk::Joystick::Axis axis;
                    ikk::Input::State   state;
                };

                struct Hat
                {
                    ikk::Joystick::ID   id;
                    ikk::Joystick::Hat  hat;
                    ikk::Input::State   state;
                };
            };
        };

        //TODO:
        struct UI
        {
            
        };

        template<class T>
        explicit constexpr Event(T type) noexcept;

        constexpr Event(const Event&) noexcept = default;
        constexpr Event(Event&&) noexcept = default;

        constexpr Event& operator=(const Event&) noexcept = default;
        constexpr Event& operator=(Event&&) noexcept = default;

        constexpr ~Event() noexcept = default;

        template<class T>
        [[nodiscard]] constexpr bool is() const noexcept;

        template<class T>
        [[nodiscard]] constexpr const std::expected<T, Error> get() const noexcept;

        template<class T>
        [[nodiscard]] constexpr const T* const getIf() const noexcept;
    private:
        std::variant<
                Window::Closed,
                Window::Resized,
                Window::FramebufferResized,
                Window::Position,
                Window::UnIconified,
                Window::Iconified,
                Window::Minimized,
                Window::Maximized,
                Window::FocusLost,
                Window::FocusGained,
                Window::CursorEntered,
                Window::CursorLeft,
                Window::ContentScale,
                Window::Refreshed,
                Window::FileDroped,
                Monitor::Connected,
                Monitor::Disconnected,
                Input::Text,
                Input::Keyboard,
                Input::Mouse::Button,
                Input::Mouse::Wheel,
                Input::Mouse::Move,
                Input::Joystick::Connected,
                Input::Joystick::Disconnected,
                Input::Joystick::Button,
                Input::Joystick::Axis,
                Input::Joystick::Hat>
            m_data;
        
        void dispatch() const noexcept;
        
        template<class T, class... Ts>
        [[nodiscard]] inline static constexpr bool isInParameterPack(const std::variant<Ts...>*) noexcept
        {
            return std::disjunction<std::is_same<T, Ts>...>::value;
        }
    public:
        template<class T>
        inline static constexpr bool isEventSubtype = isInParameterPack<T>(decltype(&m_data)(nullptr));
    };

    template<class T>
    concept EventSubType = Event::isEventSubtype<T>;

    template<class T>
    constexpr Event::Event(T type) noexcept
        : m_data(type)
    {
        static_assert(isEventSubtype<T>, "T must be a subtype of ikk::Event");
        this->dispatch();
    }

    template<class T>
    constexpr bool Event::is() const noexcept
    {
        static_assert(isEventSubtype<T>, "T must be a subtype of ikk::Event");
        return std::holds_alternative<T>(this->m_data);
    }

    template<class T>
    constexpr const std::expected<T, Error> Event::get() const noexcept
    {
        static_assert(isEventSubtype<T>, "T must be a subtype of ikk::Event");
        if (this->is<T>())
            return std::get<T>(this->m_data);
        else
            return std::unexpected(Error{ "Template parameter must be the held type." });
    }

    template<class T>
    constexpr const T* const Event::getIf() const noexcept
    {
        static_assert(isEventSubtype<T>, "T must be a subtype of ikk::Event");
        return std::get_if<T>(&this->m_data);
    }

    //TODO:
    //Type alias rest...
    using WindowEvent = Event::Window;
    using KeyboardEvent = Event::Input::Keyboard;
    using MouseEvent = Event::Input::Mouse;
    using JoystickEvent = Event::Input::Joystick;
}

#endif