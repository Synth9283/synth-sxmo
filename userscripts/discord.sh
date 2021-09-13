#!/bin/bash

export EGL_PLATFORM=x11
anbox launch --action=android.intent.action.MAIN --package=com.discord --component=com.discord.app.AppActivity$Main
