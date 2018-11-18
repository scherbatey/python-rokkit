#!/usr/bin/env python
# -*- coding: utf-8 -*-

from distutils.core import setup, Extension

module = Extension('rokkit_hash',sources = ['rokkit_hash_module.c'])

setup (name = 'rokkit_hash',
       version = '0.1',
       description = 'Implementation of Paul Hsieh\'s "SuperFastHash" (http://www.azillionmonkeys.com/qed/hash.html)',
       ext_modules = [module])
