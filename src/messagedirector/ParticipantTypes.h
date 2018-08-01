#ifndef PARTICIPANT_TYPES_H
#define PARTICIPANT_TYPES_H

enum class ParticipantTypes
{
	/*
	Some participants of the Ardos cluster operate as a singleton. That is, there is never more than one of them
	connected to the cluster at any given time. The State Server is an example of one of these participants.
	All other participants are allocated a unique Participant ID between the defined range.
	*/


};

#endif // PARTICIPANT_TYPES_H