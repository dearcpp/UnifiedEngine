#include <unified/application/application.hpp>
#include <unified/core/system/sleep.hpp>
#include <glad/glad.h>

UNIFIED_BEGIN_NAMESPACE

Application::Application(string title, VideoMode video_mode, u32 style) : Window(title, video_mode, style), _frame_limit(0), _frame_clock(), _frame_duration(0) {
    set_event_callback(BIND_EVENT_FN(&Application::OnEvent, this));
}

Application::~Application() { }

void Application::run() {
    Time elapsed;
    while (OnUpdate(elapsed)) {
        elapsed = _frame_clock.get_elapsed_time();
        _frame_clock.restart();
        if (_frame_duration > elapsed) {
            sleep(_frame_duration - elapsed);
        }
    }
}

void Application::set_viewport(Point2i size) {
    glViewport(0, 0, _video_mode.width = size.x, _video_mode.height = size.y);
}

UNIFIED_NODISCARD u32 Application::get_frame_limit() const {
    return _frame_limit;
}

void Application::set_frame_limit(u32 limit) {
    if (limit != 0) {
        _frame_limit = limit;
        _frame_duration = seconds(1.0 / _frame_limit);
    } else {
        _frame_duration = microseconds(0);
    }
}

void Application::OnEvent(EventDispatcher&) { }

UNIFIED_END_NAMESPACE
