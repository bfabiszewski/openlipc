/*  openlipc.h
 *  some functions for liblipc
 *
 *  Copyright(C) 2013 Bartek Fabiszewski (www.fabiszewski.net)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPENLIPC
#define OPENLIPC

//#include <dbus/dbus.h>
//#include <pthread.h>
//#include <glib.h>

int LipcOpenEx(char *source, int *lipc_status); 
int LipcOpen(char *source); 
int LipcOpenNoName(); 
int LipcClose(int lipc_handle);
int LipcSetStringProperty(int lipc_handle, char *publisher, char *property, char *value);
int LipcSetIntProperty(int lipc_handle, char *publisher, char *property, int value);
int LipcGetStringProperty(int lipc_handle, char *publisher, char *property, char **value);
int LipcGetIntProperty(int lipc_handle, char *publisher, char *property, int *value);
void LipcFreeString(char *string);
char * LipcGetErrorString(int error);

int LipcNewEvent(int lipc_handle, char *event_name);
int LipcAddIntParam(int event_handle, int value);
int LipcAddStringParam(int event_handle, char *value);
int LipcSendEvent(int lipc_handle, int event_handle);
int LipcEventFree(int event_handle);

#endif
