/*
 * ngfd - Non-graphic feedback daemon
 *
 * Copyright (C) 2010 Nokia Corporation.
 * Contact: Xun Chen <xun.chen@nokia.com>
 *
 * This work is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This work is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include "request-internal.h"

NRequest*
n_request_new ()
{
    NRequest *request = NULL;

    request = g_slice_new0 (NRequest);
    request->properties = n_proplist_new ();

    return request;
}

NRequest*
n_request_new_with_event (const char *event)
{
    if (!event)
        return NULL;

    NRequest *request = n_request_new ();
    request->name = g_strdup (event);
    return request;
}

void
n_request_free (NRequest *request)
{
    n_proplist_free (request->properties);
    request->properties = NULL;

    g_free (request->name);
    request->name = NULL;

    g_slice_free (NRequest, request);
}

unsigned int
n_request_get_id (NRequest *request)
{
    return (request != NULL) ? request->id : 0;
}

const char*
n_request_get_name (NRequest *request)
{
    return (request != NULL) ? (const char*) request->name : NULL;
}

void
n_request_set_properties (NRequest *request, NProplist *properties)
{
    if (!request || !properties)
        return;

    n_proplist_free (request->properties);
    request->properties = n_proplist_copy (properties);
}

const NProplist*
n_request_get_properties (NRequest *request)
{
    return (request != NULL) ? (const NProplist*) request->properties : NULL;
}

void
n_request_store_data (NRequest *request, const char *key, void *data)
{
    if (!request || !key)
        return;

    n_proplist_set_pointer (request->properties, key, data);
}

void*
n_request_get_data (NRequest *request, const char *key)
{
    if (!request || !key)
        return NULL;

    return n_proplist_get_pointer (request->properties, key);
}
