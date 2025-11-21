#ifndef IKK_HIERACHRY_HPP
#define IKK_HIERACHRY_HPP

#include <vector>

namespace ikk
{
    //TODO: Put this into a different file?
    template<class T>
    class [[nodiscard]] Hierarchy
    {
    public:
        [[nodiscard]] Hierarchy() noexcept = default;

        Hierarchy(const Hierarchy& other) noexcept;
        Hierarchy(Hierarchy&& other) noexcept;

        Hierarchy& operator=(const Hierarchy& other) noexcept;
        Hierarchy& operator=(Hierarchy&& other) noexcept;

        virtual ~Hierarchy() noexcept;

        const T* getParent() const noexcept;
        T* getParent() noexcept;

        const std::vector<T*>& getChildren() const noexcept;
        std::vector<T*>& getChildren() noexcept;

        void setParent(T& parent) noexcept;
        void addChild(T& child) noexcept;
        void removeChild(T& child) noexcept;
    private:
        T* m_parent = nullptr;
        std::vector<T*> m_children{};
    };

    template<class T>
    Hierarchy<T>::Hierarchy(const Hierarchy& other) noexcept
    {
        if (this != &other)
        {
            this->m_parent = other.m_parent;
            this->m_children = other.m_children;
        }
    }

    template<class T>
    Hierarchy<T>::Hierarchy(Hierarchy&& other) noexcept
    {
        if (this != &other)
        {
            this->m_parent = other.m_parent;
            this->m_children = std::move(other.m_children);
            other.m_parent = nullptr;
            other.m_children.clear();
        }
    }

    template<class T>
    Hierarchy<T>& Hierarchy<T>::operator=(const Hierarchy& other) noexcept
    {
        if (this != &other)
        {
            this->m_parent = other.m_parent;
            this->m_children = other.m_children;
        }
        return *this;
    }

    template<class T>
    Hierarchy<T>& Hierarchy<T>::operator=(Hierarchy&& other) noexcept
    {
        if (this != &other)
        {
            this->m_parent = other.m_parent;
            this->m_children = std::move(other.m_children);
            other.m_parent = nullptr;
            other.m_children.clear();
        }
        return *this;
    }

    template<class T>
    Hierarchy<T>::~Hierarchy() noexcept
    {
        for (T* child : this->m_children)
            if (child != nullptr)
                child->m_parent = nullptr;
    }

    template<class T>
    const T* Hierarchy<T>::getParent() const noexcept
    {
        return this->m_parent;
    }

    template<class T>
    T* Hierarchy<T>::getParent() noexcept
    {
        return this->m_parent;
    }

    template<class T>
    const std::vector<T*>& Hierarchy<T>::getChildren() const noexcept
    {
        return this->m_children;
    }

    template<class T>
    std::vector<T*>& Hierarchy<T>::getChildren() noexcept
    {
        return this->m_children;
    }

    template<class T>
    void Hierarchy<T>::setParent(T& parent) noexcept
    {
        if (this->m_parent == &parent)
            return;

        if (this->m_parent != nullptr)
            std::erase(this->m_parent->m_children, static_cast<T*>(this));

        this->m_parent = &parent;

        if (std::ranges::find(parent.m_children, this) == parent.m_children.end())
            parent.m_children.emplace_back(static_cast<T*>(this));
    }

    template<class T>
    void Hierarchy<T>::addChild(T& child) noexcept
    {
        if (std::ranges::find(this->m_children, &child) == this->m_children.end())
        {
            this->m_children.emplace_back(&child);
            child.m_parent = static_cast<T*>(this);
        }
    }

    template<class T>
    void Hierarchy<T>::removeChild(T& child) noexcept
    {
        if (auto it = std::ranges::find(this->m_children, &child); it != this->m_children.end())
        {
            (*it)->m_parent = nullptr;
            this->m_children.erase(it);
        }
    }
}

#endif