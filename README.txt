This is a little native events c library that can be called from JS using
JS ctypes.  In order to build the library, you need to install
scons: http://www.scons.org/doc/production/HTML/scons-user.html#chap-build-install

Then, in this directory type:
scons

= Windows =
In Windows, you'll need to run this in a visual studio enabled command prompt.
You can find that in your start menu in the mess of things visual studio installs.
Once you get that open, assuming you've installed scons via a msys mozilla-build shell into
the mozilla-build python path, you need to do the following in the visual studio 
command prompt:
> set PATH=c:\mozilla-build\python;%PATH%
> set PYTHON_HOME=c:\mozilla-build\python

Now you should be able to run scons

= Still under construction =
This is obviously, still under construction.  More info to come.
