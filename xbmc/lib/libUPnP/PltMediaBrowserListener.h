/*****************************************************************
|
|   Platinum - AV Media Server Control Point Listener
|
|   Copyright (c) 2004-2006 Sylvain Rebaud
|   Author: Sylvain Rebaud (sylvain@rebaud.com)
|
 ****************************************************************/

#ifndef _PLT_MEDIA_BROWSER_LISTENER_H_
#define _PLT_MEDIA_BROWSER_LISTENER_H_

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "PltMediaItem.h"
#include "PltDeviceData.h"

/*----------------------------------------------------------------------
|   PLT_BrowseInfo
+---------------------------------------------------------------------*/
struct PLT_BrowseInfo {
    NPT_String                 object_id;
    PLT_MediaItemListReference items;
    unsigned long              nr;
    unsigned long              tm;
    unsigned long              uid;
};

/*----------------------------------------------------------------------
|   PLT_MediaBrowserListener class
+---------------------------------------------------------------------*/
class PLT_MediaBrowserListener
{
public:
    virtual ~PLT_MediaBrowserListener() {}

    virtual void OnMSAddedRemoved(
        PLT_DeviceDataReference& /*device*/, 
        int                      /*added*/) {}
    virtual void OnMSStateVariablesChanged(
        PLT_Service*                  /*service*/, 
        NPT_List<PLT_StateVariable*>* /*vars*/) {}

    // 
    virtual void OnMSBrowseResult(
        NPT_Result               /*res*/, 
        PLT_DeviceDataReference& /*device*/, 
        PLT_BrowseInfo*          /*info*/, 
        void*                    /*userdata*/) {}
};

#endif /* _PLT_MEDIA_BROWSER_LISTENER_H_ */
