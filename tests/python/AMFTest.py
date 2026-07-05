# SPDX-License-Identifier: BSD-3-Clause
# Copyright Contributors to the OpenColorIO Project.

import os
import unittest

import PyOpenColorIO as OCIO
from UnitTestUtils import TEST_DATAFILES_DIR


class AMFTest(unittest.TestCase):

    def _amf(self, name):
        return os.path.join(TEST_DATAFILES_DIR, 'amf', name)

    def test_aces2_amf(self):
        """
        An AMF referencing ACES 2.0 transform IDs auto-selects an ACES 2 config
        and resolves every transform through the amf_transform_ids attribute.
        """
        config, info = OCIO.Config.CreateFromAMF(self._amf('aces2_slog3_to_p3d65.amf'))

        # The auto-selected ACES 2 studio config is profile version 2.5+.
        self.assertGreaterEqual(
            (config.getMajorVersion(), config.getMinorVersion()), (2, 5))

        self.assertTrue(info.inputColorSpaceName)
        self.assertTrue(info.displayName)
        self.assertTrue(info.viewName)

        # The resolved pipeline must be usable end to end.
        dvt = OCIO.DisplayViewTransform(src=info.inputColorSpaceName,
                                        display=info.displayName,
                                        view=info.viewName)
        self.assertIsNotNone(config.getProcessor(dvt))

    def test_aces1_amf(self):
        """
        An AMF referencing only ACES 1.x transform IDs selects an ACES 1.3
        config.
        """
        config, info = OCIO.Config.CreateFromAMF(self._amf('slogtopq.amf'))
        self.assertLess(
            (config.getMajorVersion(), config.getMinorVersion()), (2, 5))
        self.assertTrue(info.displayName)

    def test_missing_file_raises(self):
        with self.assertRaises(OCIO.Exception):
            OCIO.Config.CreateFromAMF(self._amf('does_not_exist.amf'))
