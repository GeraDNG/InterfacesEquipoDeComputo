/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_VEL                        2       /* control type: scale, callback function: (none) */
#define  PANEL_RPM                        3       /* control type: scale, callback function: (none) */
#define  PANEL_F                          4       /* control type: slide, callback function: (none) */
#define  PANEL_T                          5       /* control type: slide, callback function: (none) */
#define  PANEL_Tiempo                     6       /* control type: numeric, callback function: (none) */
#define  PANEL_Odometro                   7       /* control type: numeric, callback function: (none) */
#define  PANEL_QUITBUTTON                 8       /* control type: command, callback function: QuitCallback */
#define  PANEL_TIMER                      9       /* control type: timer, callback function: TimerCallBack */
#define  PANEL_PICTURE_15                 10      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_14                 11      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_13                 12      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_12                 13      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_11                 14      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_10                 15      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_9                  16      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_7                  17      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_6                  18      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_5                  19      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE                    20      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_4                  21      /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE_2                  22      /* control type: picture, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimerCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
