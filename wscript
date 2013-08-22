#! /usr/bin/env python
# encoding: utf-8

VERSION = '0.0.1'
APPNAME = 'gdbusbugshowcase'

top = '.'
out = 'build'

from waflib import Logs as logs
from waflib import Utils as utils

def options(opt):
	opt.recurse(['src/gdbus','src/ref'])
	
def configure(cfg):
	cfg.recurse(['src/gdbus','src/ref'])


def build(bld):
	if bld.cmd == 'install' and bld.cmd == 'uninstall':
		logs.fatal ("Do not install this crapdemo")
	bld.recurse(['src/gdbus','src/ref'])
