import sys
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

subdirs = []
env = Environment()

if is_mac():
    print "No Mac Support"
elif is_linux():
    subdirs.append('linux')

    # This is necessary to get gtk to compile and link properly
    env.ParseConfig('pkg-config --cflags --libs gtk+-2.0')
elif is_windows():
    print "No Windows Support"
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
env.Library('native_events', objs)

