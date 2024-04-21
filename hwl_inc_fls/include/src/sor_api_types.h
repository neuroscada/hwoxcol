/************************************************************************/
/*****     COPYRIGHT 2012           HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

#ifndef __sor_api_types_H__INCLUDED_
#define __sor_api_types_H__INCLUDED_
/*
@(#)sor_api_types.h main.SVR_MASTERPROJ_Integration.2
BEGIN_DOC
---------------------------------------------------------------------------
sor_api_types.h - header file for SOR API specific types
---------------------------------------------------------------------------
SUMMARY:
    SOR API types.

    The ECapabilityType enum is used by SOR API clients when making access
    / capability requests on points and assets.

---------------------------------------------------------------------------
END_DOC
*/


#include "src\crttbl_def"

// Possible capability type request levels
enum ECapabilityType
{
    // From CC 900
    READ_POINT_DATA = 0,    // legacy support - effectively the same as SOR_CAP_VIEW_POINTS
    WRITE_POINT_DATA,       // legacy support - effectively the same as SOR_CAP_CTRL_POINTS
    VIEW_NOTIFICATIONS,     // legacy support - effectively the same as SOR_CAP_VIEW_ALARMS
    ACKN_NOTIFICATIONS,     // legacy support - effectively the same as SOR_CAP_ACK_ALARMS

    // New in CC 910
    SOR_CAP_VIEW_POINTS = F_SOR_CAP_VIEW_POINTS,    // can view point.param data
    SOR_CAP_CTRL_POINTS = F_SOR_CAP_CTRL_POINTS,    // can control point.param data
    SOR_CAP_VIEW_ALARMS = F_SOR_CAP_VIEW_ALARMS,    // can view alarms, system alarms, alerts and messages
    SOR_CAP_ACK_ALARMS = F_SOR_CAP_ACK_ALARMS,      // can ack alarms, system alarms, alerts and messages
    SOR_CAP_VIEW_EVENTS = F_SOR_CAP_VIEW_EVENTS,    // can view events, SOEs, activities & recipes
    SOR_CAP_VIEW_OTHER = F_SOR_CAP_VIEW_OTHER,      // can view other asset bound data, eg trends, groups, reports, ...
    SOR_CAP_CTRL_OTHER = F_SOR_CAP_CTRL_OTHER,      // can modify other asset bound data, eg trends, groups, reports, ...

    // insert new capabilities ahead of SOR_CAP_MAX, ie above this line
    SOR_CAP_MAX
};

// define the permission levels as used by the Enterprise Model Asset tree
// the order of these should be as they need to be displayed in the Asset tree
// it is okay to insert a value, causing a re-number
// you'll just need a full compile to ensure it is picked up everywhere
enum EPermissionType
{
    SOR_PERM_NO_ACCESS = F_PERM_DENY,
    SOR_PERM_VIEW_WITHOUT_ALARMS = F_PERM_VIEW_WO_ALM,
    SOR_PERM_VIEW_ONLY = F_PERM_VIEW,
    SOR_PERM_VIEW_ACKNOWLEDGE = F_PERM_ACKN,
    SOR_PERM_FULL_CONTROL = F_PERM_FULL,

    // insert new permissions ahead of SOR_PERM_MAX, ie above this line
    SOR_PERM_MAX
};

// define the current capability map numbers
enum ECapabilityMapType
{
    SOR_CM_MIN = 0,

    SOR_CM_VIEW_POINTS = 0,
    SOR_CM_CTRL_POINTS,
    SOR_CM_VIEW_ALARMS,
    SOR_CM_ACKN_ALARMS,
    SOR_CM_CONS_ALARMS,

    // insert new capability map numbers ahead of SOR_CM_MAX, ie above this line
    SOR_CM_MAX
};


#endif // __sor_api_types_H__INCLUDED_

/************************************************************************/
/*****     COPYRIGHT 2012           HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/
