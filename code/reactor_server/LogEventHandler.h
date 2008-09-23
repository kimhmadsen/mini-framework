#pragma once
#include "iostream"
#include "eventhandler.h"
#include "reactor.h"
#include "sockstream.h"

class LogEventHandler :
	public Event_Handler
{
public:
	LogEventHandler(const SOCK_Stream &stream, Reactor *reactor): peer_stream_( stream )
	{
		reactor->register_handler( this, READ_EVENT );
	}
	~LogEventHandler(void);

	virtual void handle_event ( HANDLE handle, Event_Type event_type )
	{
		switch( event_type )
		{
		case READ_EVENT:
			char buf[256];
			// code handle short "short-reads" omitted.
			peer_stream_.recv( buf, sizeof(buf), 0 );

			// Write logging record to standard output
			std::cout << buf;
			break;

		case CLOSE_EVENT:
			peer_stream_.close();
			break;
		}
		
	}
	virtual HANDLE get_handle() 
	{
		return peer_stream_.get_handle();
	}
private:
	// Receives logging records from a connected client
	SOCK_Stream peer_stream_;
};
