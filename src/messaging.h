// -----------------------------------------------------------------------------
/**
 * \file	messaging.h
 * \author	Constantin MASSON
 * \date	June 23, 2016
 *
 * \brief	Message logic
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------


/**
 * \todo		Not implemented yet
 *
 * \brief		Process the given message.
 * \details		Recover the type of message from the given msg and execute
 * 				the action for that kind of message.
 *
 * \param msg	Message to process
 * \return		1 if successfully processed, otherwise, return -1 (Unknown message)
 */
int messaging_exec_receive(const char *msg);


//TODO send function for each message
