#include <unified/core/string.hpp>
#include <unified/core/math/vector2.hpp>

#ifndef UNIFIED_PLATFORM_WINDOW_HPP
#define UNIFIED_PLATFORM_WINDOW_HPP

namespace Unified
{
    class Window
    {
    private:

        struct glfw_wrapper;

    public:

        struct VideoMode
        {
            int width, height;
            VideoMode(int width, int height) : width(width), height(height) { }
        };

        enum Style : u32
        {
            Resizable = 1 << 0,
            Maximized = 1 << 1,
            Floating  = 1 << 2,
        };

    public:

        Window(string title, VideoMode mode, u32 style);
        
        bool poll_events() _OSL_NOEXCEPT;

        _OSL_NODISCARD Vector2i get_size() const _OSL_NOEXCEPT;
        void set_size(Vector2i size) _OSL_NOEXCEPT;

        _OSL_NODISCARD Vector2i get_position() const _OSL_NOEXCEPT;
        void set_position(Vector2i point) _OSL_NOEXCEPT;

        _OSL_NODISCARD bool get_vsync() const _OSL_NOEXCEPT;
        void set_vsync(bool enabled) _OSL_NOEXCEPT;

    protected:

        string _title;
        glfw_wrapper *_window;
        
        VideoMode _mode;
        bool _vsync;

    };
};

#endif