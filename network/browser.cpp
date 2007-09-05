/*
 * browser.cpp
 *
 * Default Browser Calling Routines.
 *
 * Copyright (c) 2007 Paulo Matias.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) AND CONTRIBUTOR(S) ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR(S) OR CONTRIBUTOR(S) BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifdef WIN32
#include <windows.h>
#else
#include <cstdlib>
#include <string>
#endif

using namespace std;

namespace Network {

#ifndef WIN32
    static int CallBrowser(const char *browser, const char *url) {
        string cmd = browser;
        cmd += " ";
        cmd += url;
        return (system(cmd.c_str()) == 0);
    }
#endif

    int CallBrowser(const char *url) {
#ifdef WIN32
        // From MSDN, "Returns a value greater than 32 if successful".
        return ((unsigned int)ShellExecute(0, "open", url, NULL, NULL, SW_SHOWMAXIMIZED) > 32);
#else
        if(CallBrowser("x-www-browser", url))
            return 1;
        if(CallBrowser("sensible-browser", url))
            return 1;
        if(CallBrowser("xfbrowser4", url))
            return 1;
        if(CallBrowser("opera", url))
            return 1;
        if(CallBrowser("firefox", url))
            return 1;
        if(CallBrowser("konqueror", url))
            return 1;
        return 0;
#endif
    }

}

