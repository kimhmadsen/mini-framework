#pragma once
#include "iostream"
#include "eventhandler.h"
#include "reactor.h"
#include "sockstream.h"

class LogEventHandler :
	public EventHandler
{
public:
	LogEventHandler(const SockStream &stream, Reactor *reactor): peer_stream_( stream )
	{
		reactor->RegisterHandler( this, READ_EVENT );
	}
	~LogEventHandler(void);

	virtual void HandleEvent ( HANDLE handle, Event_Type event_type )
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
	virtual HANDLE GetHandle() 
	{
		return peer_stream_.GetHandle();
	}
private:
	// Receives logging records from a connected client
	SockStream peer_stream_;
};
