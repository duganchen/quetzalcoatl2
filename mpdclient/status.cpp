#include "mpdclient/status.h"

mpdclient::status::status(mpd_status *status)
    : m_status{status}
{}

mpdclient::status::operator bool() const
{
    return bool(m_status);
}

unsigned mpdclient::status::get_queue_version() noexcept
{
    return mpd_status_get_queue_version(m_status);
}

unsigned mpdclient::status::get_queue_length() noexcept
{
    return mpd_status_get_queue_length(m_status);
}

unsigned mpdclient::status::get_total_time() noexcept
{
    return mpd_status_get_total_time(m_status);
}

unsigned mpdclient::status::get_elapsed_ms() noexcept
{
    return mpd_status_get_elapsed_ms(m_status);
}

bool mpdclient::status::get_random() noexcept
{
    return mpd_status_get_random(m_status);
}

bool mpdclient::status::get_repeat() noexcept
{
    return mpd_status_get_repeat(m_status);
}

int mpdclient::status::get_volume() noexcept
{
    return mpd_status_get_volume(m_status);
}

mpd_state mpdclient::status::get_state() noexcept
{
    return mpd_status_get_state(m_status);
}

unsigned mpdclient::status::get_crossfade() noexcept
{
    return mpd_status_get_crossfade(m_status);
}

int mpdclient::status::get_song_id() noexcept
{
    return mpd_status_get_song_id(m_status);
}

mpdclient::status::status(mpdclient::status &&other)
    : m_status(other.m_status)
{
    other.m_status = nullptr;
}

mpdclient::status &mpdclient::status::operator=(mpdclient::status &&other)
{
    if (this != &other) {
        if (m_status) {
            mpd_status_free(m_status);
        }

        m_status = other.m_status;
        other.m_status = nullptr;
    }
    return *this;
}

mpdclient::status::~status()
{
    if (m_status) {
        mpd_status_free(m_status);
    }
}
