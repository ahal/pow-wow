This is a little native events c library that can be called from JS using
JS ctypes.  In order to build the library, you need to install
scons: http://www.scons.org/doc/production/HTML/scons-user.html#chap-build-install

Then, in this directory type:
scons

= Windows =
In Windows you can either build it with an msys shell (powered by mozilla-build) or
you can run it using a visual studio command prompt (found in the start menu beneath the
visual studio folder).  You'll need to have python installed and scons installed
into that python either through virutalenv or into sitepackages.

== Fun Hat Trick ==
If you're on Windows and you need to run in the visual studio command line for
some reason (perhaps you're hacking on build stuff and are worried about '/' versus
'\'.  Then if you installed scons into the mozilla-build/msys python environment, 
you can simply add two environment variables to the visual studio shell and "install"
it there:
> set PATH=C:\mozilla-build\python;%PATH%
> set PYTHON_HOME=C:\mozilla-build\python

= Still under construction =
This is obviously, still under construction.  More info to come.
