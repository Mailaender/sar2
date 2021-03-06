/**********************************************************************
*   This file is part of Search and Rescue II (SaR2).                 *
*                                                                     *
*   SaR2 is free software: you can redistribute it and/or modify      *
*   it under the terms of the GNU General Public License v.2 as       *
*   published by the Free Software Foundation.                        *
*                                                                     *
*   SaR2 is distributed in the hope that it will be useful, but       *
*   WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See          *
*   the GNU General Public License for more details.                  *
*                                                                     *
*   You should have received a copy of the GNU General Public License *
*   along with SaR2.  If not, see <http://www.gnu.org/licenses/>.     *
***********************************************************************/

/*
	                  SAR Music Management

	See sound.c for low-level to sound output library functions.
 */

#ifndef SARMUSIC_H
#define SARMUSIC_H

#include "sound.h"
#include "sar.h"


/*
 *	Music Codes:
 *
 *	These correspond to an index on the core structure's list of
 *	music file references
 */
#define SAR_MUSIC_ID_DEFAULT			0
#define SAR_MUSIC_ID_SPLASH			SAR_MUSIC_CODE_DEFAULT
#define SAR_MUSIC_ID_MENUS			10
#define SAR_MUSIC_ID_LOADING_SIMULATION		50
#define SAR_MUSIC_ID_MISSION_FAILED		60
#define SAR_MUSIC_ID_MISSION_SUCCESS		61

#define SAR_MUSIC_ID_SIMULATION_ONGROUND		100
#define SAR_MUSIC_ID_SIMULATION_ONGROUND_ENTER		101
#define SAR_MUSIC_ID_SIMULATION_INFLIGHT_DAY		110
#define SAR_MUSIC_ID_SIMULATION_INFLIGHT_DAY_ENTER	111
#define SAR_MUSIC_ID_SIMULATION_INFLIGHT_NIGHT		120
#define SAR_MUSIC_ID_SIMULATION_INFLIGHT_NIGHT_ENTER	121
#define SAR_MUSIC_ID_SIMULATION_RESCUE			150
#define SAR_MUSIC_ID_SIMULATION_RESCUE_ENTER		151


extern void SARMusicUpdate(sar_core_struct *core_ptr);

#endif	/* SARMUSIC_H */
