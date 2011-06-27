AR = '/usr/bin/ar'
ARFLAGS = 'rcs'
CC = ['/usr/bin/gcc']
CCDEFINES = ['ENABLE_GSL', 'ENABLE_GSL']
CCDEFINES_GTK_CONFIG_STORE = ['_REENTRANT']
CCDEFINES_ST = '-D%s'
CCFLAGS = ['-O3', '-g', '-Wall', '-Werror', '-O3', '-g', '-Wall', '-Werror', '-Wno-error=deprecated-declarations', '-fstrict-aliasing', '-Wstrict-aliasing']
CCFLAGS_DEBUG = ['-g']
CCFLAGS_GTK_CONFIG_STORE = ['-pthread']
CCFLAGS_MACBUNDLE = ['-fPIC']
CCFLAGS_PTHREAD = '-pthread'
CCFLAGS_PYEMBED = ['-fno-strict-aliasing']
CCFLAGS_PYEXT = ['-fno-strict-aliasing', '-fvisibility=hidden']
CCFLAGS_RELEASE = ['-O2']
CCLNK_SRC_F = ''
CCLNK_TGT_F = ['-o', '']
CC_NAME = 'gcc'
CC_SRC_F = ''
CC_TGT_F = ['-c', '-o', '']
CC_VERSION = ('4', '4', '3')
COMPILER_CC = 'gcc'
COMPILER_CXX = 'g++'
CPP = '/usr/bin/cpp'
CPPPATH_GTK_CONFIG_STORE = ['/usr/include/gtk-2.0', '/usr/lib/gtk-2.0/include', '/usr/include/atk-1.0', '/usr/include/cairo', '/usr/include/pango-1.0', '/usr/include/gio-unix-2.0/', '/usr/include/glib-2.0', '/usr/lib/glib-2.0/include', '/usr/include/pixman-1', '/usr/include/freetype2', '/usr/include/directfb', '/usr/include/libpng12']
CPPPATH_LIBXML2 = ['/usr/include/libxml2']
CPPPATH_PYEMBED = ['/usr/include/python2.6']
CPPPATH_PYEXT = ['/usr/include/python2.6']
CPPPATH_ST = '-I%s'
CXX = ['/usr/bin/g++']
CXXDEFINES = ['ENABLE_GSL']
CXXDEFINES_GTK_CONFIG_STORE = ['_REENTRANT']
CXXDEFINES_ST = '-D%s'
CXXFLAGS = ['-O3', '-g', '-Wall', '-Werror', '-Wno-error=deprecated-declarations', '-fstrict-aliasing', '-Wstrict-aliasing']
CXXFLAGS_DEBUG = ['-g']
CXXFLAGS_GTK_CONFIG_STORE = ['-pthread']
CXXFLAGS_PTHREAD = '-pthread'
CXXFLAGS_PYEMBED = ['-fno-strict-aliasing']
CXXFLAGS_PYEXT = ['-fno-strict-aliasing', '-fvisibility=hidden']
CXXFLAGS_RELEASE = ['-O2']
CXXLNK_SRC_F = ''
CXXLNK_TGT_F = ['-o', '']
CXX_NAME = 'gcc'
CXX_SRC_F = ''
CXX_TGT_F = ['-c', '-o', '']
DEST_BINFMT = 'elf'
DEST_CPU = 'x86'
DEST_OS = 'linux'
DOXYGEN = '/usr/bin/doxygen'
ENABLE_EMU = True
ENABLE_EXAMPLES = True
ENABLE_GSL = True
ENABLE_GTK_CONFIG_STORE = True
ENABLE_LIBXML2 = True
ENABLE_NSC = False
ENABLE_PYTHON_BINDINGS = False
ENABLE_PYTHON_PCH = False
ENABLE_REAL_TIME = True
ENABLE_STATIC_NS3 = True
ENABLE_SUDO = False
ENABLE_TAP = True
ENABLE_THREADING = True
FULLSTATIC_MARKER = '-static'
GSL = True
GTK_CONFIG_STORE = True
HAVE_GETENV = 1
HAVE_IF_TUN_H = 1
HAVE_INTTYPES_H = 1
HAVE_LIBXML2 = 1
HAVE_NETINET_IN_H = 1
HAVE_PACKET_H = 1
HAVE_PTHREAD_H = 1
HAVE_PYTHON_H = 1
HAVE_SIGNAL_H = 1
HAVE_STDINT_H = 1
HAVE_STDLIB_H = 1
HAVE_SYS_INT_TYPES_H = ()
HAVE_SYS_SOCKET_H = 1
HAVE_UINT128_T = ()
HAVE___UINT128_T = ()
LIBPATH_PYEMBED = ['/usr/lib']
LIBPATH_PYTHON2.6 = ['/usr/lib']
LIBPATH_ST = '-L%s'
LIBXML2 = True
LIB_GSL = ['gsl', 'gslcblas', 'm']
LIB_GTK_CONFIG_STORE = ['gtk-x11-2.0', 'gdk-x11-2.0', 'atk-1.0', 'gio-2.0', 'pangoft2-1.0', 'gdk_pixbuf-2.0', 'm', 'pangocairo-1.0', 'cairo', 'pango-1.0', 'freetype', 'fontconfig', 'gobject-2.0', 'gmodule-2.0', 'gthread-2.0', 'rt', 'glib-2.0']
LIB_LIBXML2 = ['xml2']
LIB_PYEMBED = ['m', 'pthread', 'dl', 'util', 'python2.6']
LIB_PYTHON2.6 = ['python2.6']
LIB_RT = ['rt']
LIB_SQLITE3 = ['sqlite3']
LIB_ST = '-l%s'
LINKFLAGS_GTK_CONFIG_STORE = ['-pthread']
LINKFLAGS_MACBUNDLE = ['-bundle', '-undefined', 'dynamic_lookup']
LINKFLAGS_PTHREAD = '-pthread'
LINKFLAGS_PYEMBED = ['-Wl,-Bsymbolic-functions']
LINK_CC = ['/usr/bin/gcc']
LINK_CXX = ['/usr/bin/g++']
MPI = ''
NS3_ACTIVE_VARIANT = 'optimized'
NS3_BUILDDIR = '/home/bowitz/Documents/master thesis/ns-3.10/build'
NS3_EXECUTABLE_PATH = ['/home/bowitz/Documents/master thesis/ns-3.10/build/optimized/src/devices/emu', '/home/bowitz/Documents/master thesis/ns-3.10/build/optimized/src/devices/tap-bridge']
NS3_MODULES = ['ns3-core', 'ns3-common', 'ns3-simulator', 'ns3-contrib', 'ns3-node', 'ns3-internet-stack', 'ns3-point-to-point', 'ns3-csma', 'ns3-emu', 'ns3-bridge', 'ns3-tap-bridge', 'ns3-virtual-net-device', 'ns3-onoff', 'ns3-packet-sink', 'ns3-udp-echo', 'ns3-bulk-send', 'ns3-nix-vector-routing', 'ns3-olsr', 'ns3-global-routing', 'ns3-static-routing', 'ns3-list-routing', 'ns3-aodv', 'ns3-dsdv', 'ns3-batman', 'ns3-secure-batman', 'ns3-mobility', 'ns3-wifi', 'ns3-helper', 'ns3-stats', 'ns3-v4ping', 'ns3-uan', 'ns3-spectrum', 'ns3-mesh', 'ns3-dot11s', 'ns3-flame', 'ns3-ping6', 'ns3-radvd', 'ns3-test', 'ns3-perf', 'ns3-ns3tcp', 'ns3-nsctcp', 'ns3-ns3wifi', 'ns3-flow-monitor', 'ns3-udp-client-server', 'ns3-wimax', 'ns3-lte', 'ns3-mpi', 'ns3-topology-read', 'ns3-energy', 'ns3-visualizer']
NS3_MODULE_PATH = ['/usr/lib/gcc/i486-linux-gnu/4.4.3', '/home/bowitz/Documents/master thesis/ns-3.10/build/optimized']
NS3_OPTIONAL_FEATURES = [('Threading', 'Threading Primitives', True, '<pthread.h> include not detected'), ('RealTime', 'Real Time Simulator', True, 'threading not enabled'), ('EmuNetDevice', 'Emulated Net Device', True, '<netpacket/packet.h> include not detected'), ('TapBridge', 'Tap Bridge', True, '<linux/if_tun.h> include not detected'), ('GtkConfigStore', 'GtkConfigStore', True, "library 'gtk+-2.0 >= 2.12' not found"), ('XmlIo', 'XmlIo', True, "library 'libxml-2.0 >= 2.7' not found"), ('SqliteDataOutput', 'SQlite stats data output', True, "library 'sqlite3' not found"), ('nsc', 'Network Simulation Cradle', False, 'NSC not found (see option --with-nsc)'), ('python', 'Python Bindings', False, 'PyBindGen missing'), ('mpi', 'MPI Support', False, 'option --enable-mpi not selected'), ('ENABLE_SUDO', 'Use sudo to set suid bit', False, 'option --enable-sudo not selected'), ('ENABLE_EXAMPLES', 'Build examples and samples', True, 'defaults to enabled'), ('static', 'Static build', True, ''), ('GSL', 'GNU Scientific Library (GSL)', True, 'GSL not found')]
PKG_CONFIG = '/usr/bin/pkg-config'
PLATFORM = 'linux2'
PREFIX = '/usr/local'
PYC = 1
PYCMD = '"import sys, py_compile;py_compile.compile(sys.argv[1], sys.argv[2])"'
PYFLAGS = ''
PYFLAGS_OPT = '-O'
PYO = 1
PYTHON = '/usr/bin/python'
PYTHONDIR = '/usr/local/lib/python2.6/dist-packages'
PYTHON_CONFIG = '/usr/bin/python2.6-config'
PYTHON_VERSION = '2.6'
RANLIB = '/usr/bin/ranlib'
RPATH_ST = '-Wl,-rpath,%s'
SHLIB_MARKER = '-Wl,-Bdynamic'
SONAME_ST = '-Wl,-h,%s'
SQLITE_STATS = True
STATICLIBPATH_ST = '-L%s'
STATICLIB_MARKER = '-Wl,-Bstatic'
STATICLIB_ST = '-l%s'
SUDO = '/usr/bin/sudo'
USE_HIGH_PRECISION_CAIRO = 1
VALGRIND = '/usr/bin/valgrind'
WL_SONAME_SUPPORTED = True
_VARIANT_ = 'optimized'
cfg_files = ['ns3/core-config.h', 'ns3/simulator-config.h', 'ns3/contrib-config.h', 'ns3/net-anim-config.h']
defines = {'HAVE_LIBXML2': 1, 'HAVE_PYTHON_H': 1, 'HAVE___UINT128_T': (), 'HAVE_SYS_SOCKET_H': 1, 'HAVE_SIGNAL_H': 1, 'HAVE_NETINET_IN_H': 1, 'HAVE_GETENV': 1, 'HAVE_IF_TUN_H': 1, 'HAVE_INTTYPES_H': 1, 'PYTHONDIR': '"/usr/local/lib/python2.6/dist-packages"', 'HAVE_UINT128_T': (), 'HAVE_STDLIB_H': 1, 'HAVE_PTHREAD_H': 1, 'HAVE_SYS_INT_TYPES_H': (), 'USE_HIGH_PRECISION_CAIRO': 1, 'HAVE_PACKET_H': 1, 'HAVE_STDINT_H': 1}
macbundle_PATTERN = '%s.bundle'
program_PATTERN = '%s'
pyext_PATTERN = '%s.so'
shlib_CCFLAGS = ['-fPIC', '-DPIC']
shlib_CXXFLAGS = ['-fPIC', '-DPIC']
shlib_LINKFLAGS = ['-shared']
shlib_PATTERN = 'lib%s.so'
staticlib_LINKFLAGS = ['-Wl,-Bstatic']
staticlib_PATTERN = 'lib%s.a'