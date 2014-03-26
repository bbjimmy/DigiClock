/****************************************************************
*	DigiClockSS.cpp  											*
*																*
*	Version:	0.1												*
*	Author: 	Jim Saxton  									*
*	this source code is released under GNU GPL v2				*
*---------------------------------------------------------------*
* Based on BinaryCockSS by David Enderson                       *
****************************************************************/
#include "DigiClockSS.h"
#include <StringView.h>
#include <stdlib.h>

	int red = 0;
	int blue = 18;
	int green = 0;
	int change = 0;
	

extern "C" _EXPORT BScreenSaver *instantiate_screen_saver(BMessage *message, image_id image)
{
	return new DigiClock(message, image);
}

DigiClock::DigiClock(BMessage *message, image_id image)
 : BScreenSaver(message, image)
{
}

void DigiClock::StartConfig(BView *view)
{
// I'll do this better later
	view->AddChild(new BStringView(BRect(10, 10, 200, 35), NULL, "DigiClock, by Jim Saxton"));
	view->AddChild(new BStringView(BRect(10, 40, 200, 50), NULL, "Based On:"));		
	view->AddChild(new BStringView(BRect(10, 55, 300, 85), NULL, "BinaryClock by David Enderson"));
	
}
status_t DigiClock::StartSaver(BView *view, bool preview)
{
	rgb_color offcolor = {93, 0, 93, 0};	// temporary color for this function
	srand(time(NULL) %37);
	int thewidth=(view->Bounds()).IntegerWidth()/8;
	int theheight=(view->Bounds()).IntegerHeight()/5;

	SetTickSize(5500);	

	for (int a=0; a<24; a++) {
// this line is copied from the original program incase I need to refer back to my awful formulas
//		dot[a]= new BView(BRect((a/4)*14+2+(a/8*7), ((3-(a%4))*14)+2, (a/4)*14+12+2+(a/8*7), ((3-(a%4))*14)+12+2), "thedots", B_FOLLOW_NONE, B_WILL_DRAW);
// sorry the formulas are so hideous.  I'll try to make them better when I have time.
		dot[a]= new BView(BRect((a/4)*thewidth+2+(a/8*(thewidth/2))+thewidth/2, ((3-(a%4))*theheight)+2+theheight/2, (a/4)*thewidth-thewidth/20+2+(a/8*(thewidth/2))+thewidth+thewidth/2, ((3-(a%4))*theheight)-theheight/20+2+theheight+theheight/2), "thedots", B_FOLLOW_NONE, B_WILL_DRAW);
		dot[a]->SetViewColor(offcolor);
		view->AddChild(dot[a]);
	}

	return B_OK;
}

void DigiClock::Draw(BView *view, int32 frame)
{
	int lb=0;
	int lg=0;
	int lr=0;
	if (change == 0) {
	
	red = rand() % 255;
	blue = rand() % 255;
	green = rand () % 255;
	change=rand() % 5000;
		if (red+blue+green< 125) {
			red = red + 20;
			blue = blue + 20;
			green = green + 20;
			
			}
	}
	change = change+1; // change the color? 
	if (change > 5000){
	change=0;
	} 
	lb=blue-90;
	lg=green-90;
	lr=red-90;
	
	if (lr+lb+lg>125) {
		lr=lr-20;
		lb=lb-20;
		lg=lg-20;
	}
	if (lr+lb+lg<70){
		lr=lr+20;
		lb=lb+20;
		lg=lg+20;
	}
	if (lb<0) lb=20;
	if (lr<0) lr=20;
	if (lb<0) lb=20;

	rgb_color oncolor = {red,green, blue, 0};	// color when clock part is on
	rgb_color offcolor = {lr, lg,lb, 0};	// color when clock part is off
	
	if (frame==0) {
		rgb_color backcolor = {0, 0, 0, 0};	// temporary color for this function
		/* Fill the screen with black on the first frame: */ 
		//view->SetLowColor( 0, 0, 0 ); 
		//view->FillRect( view->Bounds(), B_SOLID_LOW ); 		
		view->SetViewColor(backcolor);
		view->Invalidate();
	}

	time_t clock = time( (time_t*) NULL); 
	struct tm *tmptr = localtime(&clock);

	for (int a=0; a<4; a++) {
		if (((tmptr->tm_hour)/10)&(int)pow(2,a))
			dot[a]->SetViewColor(oncolor);
		else
			dot[a]->SetViewColor(offcolor);
		dot[a]->Invalidate();
	}
	for (int a=4; a<8; a++) {
		if (((tmptr->tm_hour)%10)&(int)pow(2,(a-4)))
			dot[a]->SetViewColor(oncolor);
		else
			dot[a]->SetViewColor(offcolor);
		dot[a]->Invalidate();
	}
	for (int a=8; a<12; a++) {
		if (((tmptr->tm_min)/10)&(int)pow(2,(a-8)))
			dot[a]->SetViewColor(oncolor);
		else
			dot[a]->SetViewColor(offcolor);
		dot[a]->Invalidate();
	}
	for (int a=12; a<16; a++) {
		if (((tmptr->tm_min)%10)&(int)pow(2,(a-12)))
			dot[a]->SetViewColor(oncolor);
		else
			dot[a]->SetViewColor(offcolor);
		dot[a]->Invalidate();
	}
	for (int a=16; a<20; a++) {
		if (((tmptr->tm_sec)/10)&(int)pow(2,(a-16)))
			dot[a]->SetViewColor(oncolor);
		else
			dot[a]->SetViewColor(offcolor);
		dot[a]->Invalidate();
	}
	for (int a=20; a<24; a++) {
		if (((tmptr->tm_sec)%10)&(int)pow(2,(a-20)))
			dot[a]->SetViewColor(oncolor);
		else
			dot[a]->SetViewColor(offcolor);
		dot[a]->Invalidate();
	}


}
