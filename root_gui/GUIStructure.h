/*
 * GUIStructure.h
 *
 *  Created on: Sep 10, 2018
 *      Author: newdriver
 */

#ifndef GUISTRUCTURE_H_
#define GUISTRUCTURE_H_

#include "vector"
#include "map"
#include "string"

enum CommandIdentifiers {
	// Command for the file window
	M_FILE_OPEN,
	M_FILE_NEWCANVAS,
	M_FILE_TBROWER,
	M_FILE_SAVE,
	M_FILE_SAVEAS,
	M_FILE_PRINT,
	M_FILE_PRINTSETUP,
	M_FILE_EXIT,

	// set
	M_SET_WORKMODE,
	M_SET_LOADMAPPING,
	M_SET_LOADPEDESTAL,
	M_SET_BATCH,

	M_TOOL_APVMAPPINGWIZARD,
	M_TOOL_HRSOPTICSWIZARD,

	M_VIEW_ENBL_DOCK,
	M_VIEW_ENBL_HIDE,
	M_VIEW_DOCK,
	M_VIEW_UNDOCK,

	M_HELP_CONTENTS,
	M_HELP_SEARCH,
	M_HELP_ABOUT,
	// workzone button key value
	B_PEDESTALFILE_OPEN,
	B_RAWFILE_OPEN,
	B_RAWFILE_DELETE,

	C_WORKMODE_RAW,
	C_WORKMODE_ZEROSUBTRACTION,
	C_WORKMODE_PEDESTAL,
	C_WORKMODE_HIT,
	C_WORKMODE_ANALYSIS,
	C_WORKMODE_CALIBRATION,
	C_WORKMODE_ONLINEMONITOR,


	//C_RAWFILE_PEDESTAL,
	//C_RAWFILE_DAT,

	V_NUMBERINPUT,
	B_CONFIRM,

	C_COLORSEL,

	ENUM_NULL
};

enum GUIWorkMode{
	WORKMODE_RAW,
	WORKMODE_PEDESTAL,
	WORKMODE_ZERSUBTRACTION,
	WORKMODE_HIT,
	WORKMODE_ANALYSIS,
	WORKMODE_CALIBRATION
};

#endif /* GUISTRUCTURE_H_ */
