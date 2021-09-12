#!/bin/bash

export EGL_PLATFORM=x11
anbox launch --package=org.anbox.appmgr --component=org.anbox.appmgr.AppViewActivity
