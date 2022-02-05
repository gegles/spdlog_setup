#!/usr/bin/env python
# -*- coding: utf-8 -*-
from conans import ConanFile

class SpdlogSetupConan(ConanFile):
    name = 'spdlog_setup'
    version = '1.0.0'

    # No settings/options are necessary, this is header only
    exports_sources = 'include/*'
    no_copy_source = True

    def package(self):
        self.copy('*.h')
