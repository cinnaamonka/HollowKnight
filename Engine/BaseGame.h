#pragma once
#include "structs.h"
#include "SDL.h"
// https://BaseGameprogrammingpatterns.com/subclass-sandbox.html


class BaseGame
{
public:
	explicit BaseGame( const Window& window );
	BaseGame( const BaseGame& other ) = delete;
	BaseGame& operator=( const BaseGame& other ) = delete;
	BaseGame(BaseGame&& other) = delete;
	BaseGame& operator=(BaseGame&& other) = delete;
	virtual ~BaseGame( );

	void Run( );

	virtual void Update(float elapsedSec)
	{
		
	}
	virtual void Draw() const
	{
		
	}

	// Event handling
	virtual void ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
	{
		
	}
	virtual void ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
	{
		
	}
	virtual void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
	{
		
	}
	virtual void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
	{
		
	}
	virtual void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
	{
		
	}

	const Rectf& GetViewPort() const
	{
		return m_Viewport;
	}

protected:

	static const void SetQuit(const bool quit)
	{
		m_IsQuit = quit;
	}

private:
	// DATA MEMBERS
	// The window properties
	const Window m_Window;
	const Rectf m_Viewport;
	// The window we render to
	SDL_Window* m_pWindow;
	// OpenGL context
	SDL_GLContext m_pContext;
	// Init info
	bool m_Initialized;
	// Prevent timing jumps when debugging
	const float m_MaxElapsedSeconds;
	
	// FUNCTIONS
	void InitializeGameEngine( );
	void CleanupGameEngine( );

	static bool m_IsQuit;
};

