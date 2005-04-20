import os
import SCons
import errno

SConsignFile()
EnsureSConsVersion(0, 96)

#eim version
version = '0.0.1a'

# Define options
opts = Options('scache.conf')
opts.AddOptions (
    BoolOption('debug', 'Compile a debug version', 1),
    PathOption('prefix', 'Set the install "prefix"', '/usr/local')
    )

#Define the environments
env = Environment (options = opts,
                   VERSION = version,
                   TARBALL='eim-' + version + '.tar.bz2',
                   DISTFILES = [],
                   DISTTREE = '#eim-' + version,
                   DISTCHECKDIR = '#eim-' + version + '/check'
                   )

#Save option and generate Help
opts.Save ('options.cache', env)
Help (opts.GenerateHelpText(env))


#
# source tar file builder
#

def distcopy (target, source, env):
    treedir = str (target[0])

    try:
        os.mkdir (treedir)
    except OSError, (errnum, strerror):
        if errnum != errno.EEXIST:
            print 'mkdir ', treedir, ':', strerror

    cmd = 'tar cf - '
    #
    # we don't know what characters might be in the file names
    # so quote them all before passing them to the shell
    #
    all_files = ([ str(s) for s in source ])
    cmd += " ".join ([ "'%s'" % quoted for quoted in all_files])
    cmd += ' | (cd ' + treedir + ' && tar xf -)'
    p = os.popen (cmd)
    return p.close ();

def tarballer (target, source, env):            
    cmd = 'tar -jcf ' + str (target[0]) +  ' ' + str(source[0]) + "  --exclude '*~'"
    print 'running ', cmd, ' ... '
    p = os.popen (cmd)
    ret = p.close ()
    return ret

dist_bld = Builder (action = distcopy,
                    target_factory = SCons.Node.FS.default_fs.Entry,
                    source_factory = SCons.Node.FS.default_fs.Entry,
                    multi = 1)

tarball_bld = Builder (action = tarballer,
                       target_factory = SCons.Node.FS.default_fs.Entry,
                       source_factory = SCons.Node.FS.default_fs.Entry)

env.Append (BUILDERS = {'Distribute' : dist_bld})
env.Append (BUILDERS = {'Tarball' : tarball_bld})


# source tarball
Precious (env['DISTTREE'])
env.Distribute (env['DISTTREE'],
                ['SConstruct', 'AUTHORS' , 'COPYING' ,
                 'ChangeLog' , 'INSTALL' , 'NEWS', 'README',
                 'TODO'])
srcdist = env.Tarball(env['TARBALL'], env['DISTTREE'])
env.Alias ('dist', srcdist)


#
# don't leave the distree around 
#
env.AddPreAction (env['DISTTREE'], Action ('rm -rf ' + str (File (env['DISTTREE']))))
#env.AddPostAction (srcdist, Action ('rm -rf ' + str (File (env['DISTTREE']))))



# Configure
conf = Configure(env)

#Update CFLAGS in function of the options
if env['debug']:
    conf.env.Append (CCFLAGS = '-g3')
else:
    conf.env.Append (CCFLAGS = '-O3')
conf.env.Append (CCFLAGS='-Wall')

#
#- Add the config command to the environment
#- Generate an error if the command is not available
#
def checkConfig (config, env):
    cf = env.WhereIs (config)
    if cf == None or cf == "":
        print "Impossible to find", config
        Exit (1)
    env.ParseConfig(config + ' --cflags --libs')


#Check ecore-config
checkConfig ('ecore-config', conf.env)
checkConfig ('ewl-config', conf.env)
checkConfig ('edje-config', conf.env)
checkConfig ('esmart-config', conf.env)

#Check for Expat
if not conf.CheckLib('expat'):
    print 'Did not find the expat library, exiting!'
    Exit(1)

#Add source directoy
conf.env.Append (CPPPATH='#src/')
    
env = conf.Finish ()

#Define bin, include, library directory
install_inc = os.path.join (env['prefix'], 'include/eim')
install_bin = os.path.join (env['prefix'], 'bin')
install_lib = os.path.join (env['prefix'], 'lib')
env.Alias ('install', [install_inc, install_bin, install_lib])


Export ('env install_inc install_bin install_lib')
for subdir in ['src']:
    SConscript ('%s/SConscript' % subdir)
