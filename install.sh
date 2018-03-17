#!/bin/bash

sudo apt-add-repository 'deb http://repos.codelite.org/wx3.1.1/ubuntu/ artful universe'

sudo apt-get install libwxbase3.1-0-unofficial3 \
		 libwxbase3.1unofficial3-dev \
		 libwxgtk3.1-0-unofficial3 \
		 wx3.1-headers \
		 libwxgtk-media3.1-0-unofficial3 \
		 libwxgtk-webview3.1-0-unofficial3 \
		 libwxbase3.1-0-unofficial3-dbg \
		 libwxgtk3.1-0-unofficial3-dbg \
		 libwxgtk-media3.1-0-unofficial3-dbg \
		 wx3.1-i18n \
		 wx3.1-examples

