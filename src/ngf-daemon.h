/*
 * ngfd - Non-graphical feedback daemon
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 *
 * Contact: Xun Chen <xun.chen@nokia.com>
 *
 * This software, including documentation, is protected by copyright
 * controlled by Nokia Corporation. All rights are reserved.
 * Copying, including reproducing, storing, adapting or translating,
 * any or all of this material requires the prior written consent of
 * Nokia Corporation. This material also contains confidential
 * information which may not be disclosed to others without the prior
 * written consent of Nokia.
 */

#ifndef NGF_DAEMON_H
#define NGF_DAEMON_H

#include <glib.h>

#include "ngf-event-manager.h"
#include "ngf-context.h"
#include "ngf-dbus.h"

typedef struct _NgfDaemon NgfDaemon;

struct _NgfDaemon
{
    GMainLoop       *loop;

    /* Event handling */
    NgfEventManager *event_manager;
    GList           *event_list;

    /* D-Bus interface */
    NgfDBus         *dbus;
    
    /* Context containing the backends. */
    NgfContext      context;
};

NgfDaemon*  ngf_daemon_create ();
void        ngf_daemon_destroy (NgfDaemon *self);
void        ngf_daemon_run (NgfDaemon *self);

guint       ngf_daemon_event_play (NgfDaemon *self, const char *sender, const char *event_name, GHashTable *properties);
void        ngf_daemon_event_stop (NgfDaemon *self, guint id);

#endif /* NGF_DAEMON_H */