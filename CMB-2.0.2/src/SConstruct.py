""" 
Default build is for Windows x64 architecture. Speficify the path to CART package and RNDB if the default path are not to be used. 
To build for QNX, set OS = 'Neutrino'.
"""
from  cart.JConfig.SConfig import *
#from SBuildToolConfig import *

#OS='Windows'
OS = 'Neutrino'

env = Environment(
    CPPPATH=[
     '../../CART/include',
     '../../BCF/include',
     '../../BTF/include',
     '../../BRF/include',
     '../../CMB/include',
    ],
    CPPFLAGS=['-g'],
    tools=['mingw']    
)

LIB_DIRS = []

if OS == 'Neutrino':
    qnx_nto_aarch64_tools(env)
    env.Append(CPPPATH=[
         './../Adaptor/CSD2/'
    ])
    env.Append(CPPFLAGS='-DENABLE_BAF_ADAPTOR=0')
    env.Append(CPPFLAGS='-DENABLE_BCF_ADAPTOR=0')
    env.Append(CPPFLAGS='-DENABLE_BRF_ADAPTOR=1')
    env.Append(CPPFLAGS='-DENABLE_BTF_ADAPTOR=1')
    env.Append(CPPFLAGS='-DENABLE_ASDS_ADAPTOR=0')    
    LIB_DIRS += ['./../Adaptor/CSD2/']

if OS == 'Windows':
    env['LIBPREFIX'] = ''
    env['LIBSUFFIX'] = '.lib'
    env.Append(CPPFLAGS='-DENABLE_BAF_ADAPTOR=1')
    env.Append(CPPFLAGS='-DENABLE_BCF_ADAPTOR=1')
    env.Append(CPPFLAGS='-DENABLE_BRF_ADAPTOR=1')
    env.Append(CPPFLAGS='-DENABLE_BTF_ADAPTOR=1')
    env.Append(CPPFLAGS='-DENABLE_ASDS_ADAPTOR=1')

env.Append(CPPFLAGS='-DBCF_PROXY_CNT=1')
env.Append(CPPFLAGS='-DBRF_PROXY_CNT=1')
env.Append(CPPFLAGS='-DBTF_PROXY_CNT=1')

LIB_LIST = ['csd2IpcClient','ams2', 'slog2', 'mmap_peerS', 'OSAbstraction', 'pmem_client', 'liblibstd']
LIB_LIST += ['ssr', 'ss_drv_utilS', 'tzbsplib', 'pps', 'socket', 'amfs2S']
LIB_LIST += ['audio_log_utilS', 'ar_osalS', 'avmm_libS', 'ar_utilS', 'diag_lsm']
LIB_LIST += ['CMB','Btf','Brf']

LIB_DIRS = ['../dll','../lib','../../CMB/lib/','../../BTF/lib/','../../BRF/lib/']


if OS == 'Neutrino':
    Btf_test = env.Program(
        target =  ['Cmb_test'], 
        source = ['main.c',
                'CMB_Framework_config.cpp',
                ],
                LIBS=LIB_LIST,
                LIBPATH=LIB_DIRS)

if OS == 'Windows':
        Btf_test = env.Program(
        target =  ['Cmb_test'], 
        source = ['main.c', 
                'CMB_Framework_config.cpp',
                f'{CMB_LIB}',
                f'{BTF_LIB}',
                f'{BRF_LIB}',
                ])