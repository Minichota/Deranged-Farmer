#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

union SDL_Event;
class Event_Handler {
	public:
	virtual void handle_event(const SDL_Event& event) = 0;
};
#endif
