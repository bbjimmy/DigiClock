/****************************************************************
*	DigiClockSS.h												*
*																*
*	Version:	0.1												*
*	Author: 	Jim Saxton   									*
*	this source code is released under the GPL					*
*---------------------------------------------------------------*
****************************************************************/
#include <ScreenSaver.h>
#include <time.h>
#include <math.h>

class DigiClock : public BScreenSaver
{
public:
				DigiClock(BMessage *message, image_id id);
	void		StartConfig(BView *view);
	status_t	StartSaver(BView *v, bool preview);
	void		Draw(BView *v, int32 frame);

	BView *dot[24];			// the 24 dots on the clock

};
