#ifndef PARTICIPANT_TYPES_H
#define PARTICIPANT_TYPES_H

enum class ParticipantTypes
{
	/*
	Some participants of the Ardos cluster operate as a singleton. That is, there is never more than one of them
	connected to the cluster at any given time. The State Server is an example of one of these participants.
	All other participants are allocated a unique Participant ID between the defined range.
	*/

	// Message Director Participant ID.
	MESSAGE_DIRECTOR_PID = 1,

	// State Server Participant ID.
	STATE_SERVER_PID = 2,

	// First 100 reserved for pre-allocated ID's.
	PID_RANGE_START = 101,
	PID_RANGE_END = 65535 // Max uint16 size.
};

#endif // PARTICIPANT_TYPES_H