#include <unified/application/window/window.hpp>
#include <unified/core/exceptions.hpp>
#include <GLFW/glfw3.h>

struct Unified::Window::glfw_wrapper {
    GLFWwindow *glfw_handle;
};

Unified::Window::Window(string title, VideoMode mode, u32 style) : _title(title), _window(new glfw_wrapper), _mode(mode), _vsync(false) {
    if (!glfwInit()) {
        throw EXCEPTION_INITIALIZATION_FAILED("GLFW");
    }

    glfwWindowHint(GLFW_RESIZABLE, (style & Style::Resizable) == Style::Resizable);
    glfwWindowHint(GLFW_MAXIMIZED, (style & Style::Maximized) == Style::Maximized);
    glfwWindowHint(GLFW_FLOATING,  (style & Style::Floating)  == Style::Floating);

    _window->glfw_handle = glfwCreateWindow(mode.width, mode.height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(_window->glfw_handle);

    glfwSetWindowUserPointer(_window->glfw_handle, &_event_callback);
    glfwSetWindowCloseCallback(_window->glfw_handle, [](GLFWwindow *window) -> void {
        event_callback_fn& dispatch_function = *reinterpret_cast<event_callback_fn*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        dispatch_function(event);
    });
}

bool Unified::Window::poll_events() _OSL_NOEXCEPT {
    glfwPollEvents();
    return !glfwWindowShouldClose(_window->glfw_handle);
}

_OSL_NODISCARD Unified::Vector2i Unified::Window::get_size() const _OSL_NOEXCEPT {
    glfwGetWindowSize(_window->glfw_handle, (int*)&_mode.width, (int*)&_mode.height);
    return Vector2i(_mode.width, _mode.height);
}

void Unified::Window::set_size(Vector2i size) _OSL_NOEXCEPT {
    glfwSetWindowSize(_window->glfw_handle, size.x, size.y);
}

_OSL_NODISCARD Unified::Vector2i Unified::Window::get_position() const _OSL_NOEXCEPT {
    Vector2i point;
    glfwGetWindowPos(_window->glfw_handle, &point.x, &point.y);
    return point;
}

void Unified::Window::set_position(Vector2i point) _OSL_NOEXCEPT {
    glfwSetWindowPos(_window->glfw_handle, point.x, point.y);
}

_OSL_NODISCARD bool Unified::Window::get_vsync() const _OSL_NOEXCEPT {
    return _vsync;
}

void Unified::Window::set_vsync(bool enabled) _OSL_NOEXCEPT {
    glfwSwapInterval(_vsync = enabled);
}

void Unified::Window::set_event_callback(const event_callback_fn &callback) {
    _event_callback = callback;
}
