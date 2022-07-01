/// \brief source file for the engine class
/// \file engine.cpp
/// 
/// author: Tyler Swann (oraqlle@github.com)
/// 
/// version: 0.1.0
/// 
/// date: 26-06-2022
/// 
/// copyright: Copyright (c) 2022
///
/// license: MIT

#include <engine/engine.hpp>
#include <states/base.hpp>


namespace crank
{

    void engine::init(details::dim&& window, details::dim&& viewport, data* globals) noexcept
    {
        m_running = true;
        m_resetting = false;

        m_window = std::move(window);
        m_viewport = std::move(viewport);

        m_globals = globals;
    }


    void engine::cleanup() noexcept
    {
        while(!m_states.empty())
        {
            m_states.back()->cleanup();
            m_states.pop_back();
        }
    }

    
    void engine::push_state(states::base* state) noexcept
    {
        if (!m_states.empty()) 
        { m_states.back()->pause(); }

        m_states.push_back(state);
        m_states.back()->init();
    }

    
    void engine::pop_state() noexcept
    {
        if (!m_states.empty())
        {
            m_states.back()->cleanup();
            m_states.pop_back();
        }

        if (!m_states.empty())
        { m_states.back()->resume(); }
    }


    
    void engine::change_state(states::base* state) noexcept
    {
        if (!m_states.empty())
        {
            m_states.back()->cleanup();
            m_states.pop_back();
        }

        m_states.push_back(state);
        m_states.back()->init();      
    }


    void engine::handle_events() noexcept
    {
        if (!m_states.empty())
        { m_states.back()->handle_events(this); }
    }


    void engine::update() noexcept
    {
        if (!m_states.empty())
        { m_states.back()->update(this); }
    }


    void engine::draw() noexcept
    {
        if (!m_states.empty())
        { m_states.back()->draw(this); }
    }


    void engine::quit() noexcept
    { m_running = false; }


    bool engine::running() const noexcept
    { return m_running; }

    
} /// namespace crank