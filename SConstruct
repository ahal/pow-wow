import sys
import os

# TODO: I'm quite certain the Configuration settings can handle this, but 
# I can't seem to make it work, so punting for now...
def is_mac():
    if sys.platform == 'darwin':
        return True
    return False

def is_linux():
    if sys.platform == 'linux2':
        return True
    return False

def is_windows():
    if (sys.platform == 'win32' or
        sys.platform == 'cygwin'):
        return True
    return False

# We need to instantiate the env module differently on different platforms
env = None
subdirs = []

if is_mac():
    print "No Mac Support"
elif is_linux():
    env = Environment()
    subdirs.append('linux')
    
    # This is necessary to get gtk to compile and link properly
    env.ParseConfig('pkg-config --cflags --libs gtk+-2.0')
elif is_windows():
    # Ensure you launched us the right way
    if (not 'INCLUDE' in os.environ or not 'WindowsSdkDir' in os.environ):
        # Then you didn't launch us with a visual studio shell
        print "Error: You must run this from a visual studio enabled command prompt."
        print "Please also ensure you have a valid installation of the Windows SDK for your platform"
        sys.exit(1)
     
    env = Environment(ENV = {'PATH': os.environ['PATH'], 
                             'INCLUDE': os.environ['INCLUDE']
                            })

    # We need to build out the path to the sdk lib directory so that we can be sure 
    # it is included. Otherwise, you get a error: "missing kernel32.lib".
    sdkpath = os.path.join(os.environ['WindowsSdkDir'], 'lib')
    env['LIBPATH'] = os.environ['LIBPATH'] + ';' + sdkpath
    
    # Build our windows subdirectory
    subdirs.append('windows')
else:
    print "Your OS is not recognized"

# Export the environment to our dependent SConscripts
Export('env')

# Make our subdirectories
objs = []
for subdir in subdirs:
    o = SConscript('%s/SConscript' % subdir)
    objs.append(o)

# Append our files in the top level directory:
objs.append('native_events.c')

# Make the library
env.SharedLibrary('native_events', objs)

