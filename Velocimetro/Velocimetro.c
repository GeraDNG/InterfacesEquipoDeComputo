#include <cvirte.h>		
#include <userint.h>
#include "Velocimetro.h"
#include <rs232.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "toolbox.h"

#define  COM_PORT 21

static int panelHandle;

int initialize(void); 

unsigned char Enable = 0; 

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Velocimetro.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	if (event == EVENT_CLOSE)
		QuitUserInterface (0);
	return 0;
}


int initialize(void)
{
	// Open communications port
	OpenComConfig (COM_PORT, "", 38400, 0, 8, 1, 19, 8);
	
	
	// It occure once, so flag it
	Enable = 1;
	
	return 0;			   
				   
}


//Convertion from hexadecimal to decimal:
int Convertion(unsigned int AR)
{
	if(AR=='A') 	 AR=10;
	else if(AR=='B') AR=11;
	else if(AR=='C') AR=12;
	else if(AR=='D') AR=13;
	else if(AR=='E') AR=14;
	else if(AR=='F') AR=15;
	return AR-48;
}

// This function will be called every Timer Click
int CVICALLBACK TimerCallBack (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	//Odometer:
	//unsigned char ReadOdo [8] = {0x30, 0x31, 0x20, 0x33, 0x31, 0x20, 0x0D, '\0'}; //Command to request odometer
	//unsigned char Odo [35] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//Engine Temperature:
	unsigned char ReadTEMP [8] = {0x30, 0x31, 0x20, 0x30, 0x35, 0x20, 0x0D, '\0'}; //Command to request RPM
	unsigned char TEMP [19] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//Engine RPM:
	//unsigned char ReadRPM [8] = {0x30, 0x31, 0x20, 0x30, 0x43, 0x20, 0x0D, '\0'}; //Command to request RPM
	//unsigned char RPM [] = {};
	//Speedometer:
	//unsigned char ReadSPEED [8] = {0x30, 0x31, 0x20, 0x30, 0x44, 0x20, 0x0D, '\0'};
	//unsigned char SPEED [] = {};
	//Time of driving:
	//unsigned char ReadTIMEofD [8] = {0x30, 0x31, 0x20, 0x31, 0x46, 0x20, 0x0D, '\0'};
	//unsigned char TIMEofD [] = {};
	
	
	int bytes_sent,i;									   
	unsigned int ValueTEMP;
	
	// Disable NON FATAL RUN TIME Library ERROR
	SetBreakOnLibraryErrors(0);
	
	// Check wheter we have to open COMMs port and Initialize it
	if (Enable == 0)
	  initialize();
	// Comm port is open and initialized	
	else {
		
	  // Request a temperature reading
	  for (i=0; i<strlen(ReadTEMP); i++){
		  bytes_sent = ComWrtByte (COM_PORT, ReadTEMP[i]);
		  //Delay(0.1);
	  }
	  
	  // Read the temperature sent
	  for (i=0; i<19; i++) {
		  TEMP[i] = ComRdByte (COM_PORT);
		  //Delay(0.1);
	  }
	  
	  //ValueOdo 	= ((Convertion(Odo[27])+Convertion(Odo[28]))*256)+(Convertion(Odo[30])+Convertion(Odo[31]));
	  ValueTEMP = ((Convertion(TEMP[13])*16)+(Convertion(TEMP[14])))-40;
	  // Sent Value to the Thermometer indicator
	  SetCtrlVal(panelHandle,PANEL_T,ValueTEMP);
	}
	
	// Enable NON FATAL RUN TIME Library ERRORS 
	SetBreakOnLibraryErrors(1);
	
	return 0;
}





/*
int CVICALLBACK VEL (int panel, int control, int event,
					 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
		case EVENT_RIGHT_CLICK:

			break;
	}
	return 0;
}

int CVICALLBACK RPM (int panel, int control, int event,
					 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
		case EVENT_RIGHT_CLICK:

			break;
	}
	return 0;
}

int CVICALLBACK F (int panel, int control, int event,
				   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
		case EVENT_RIGHT_CLICK:

			break;
	}
	return 0;
}

int CVICALLBACK T (int panel, int control, int event,
				   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
		case EVENT_RIGHT_CLICK:

			break;
	}
	return 0;
}

int CVICALLBACK Tiempo (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
		case EVENT_RIGHT_CLICK:

			break;
	}
	return 0;
}

int CVICALLBACK Odometro (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
		case EVENT_RIGHT_CLICK:

			break;
	}
	return 0;
}

*/


int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// Close Communication port
			CloseCom (COM_PORT);
			QuitUserInterface (0);
			break;
		case EVENT_RIGHT_CLICK:

			break;
	}
	return 0;
}
