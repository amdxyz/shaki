#!/usr/bin/env python

# Shaki bitmap converter
# Copyright (C) 2016-2018 Marco Fagiolini <mfx@amdx.de>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.


from __future__ import print_function

import sys
import os
import argparse
from PIL import Image


TEMPLATE_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), 'template.txt'))


def convertFile(f):
    im = Image.open(f)

    im = im.convert('1')

    scanline = []

    if im.size[1] != 8:
        print('ERROR: The source frames height must be 8 pixels', file=sys.stderr)
        sys.exit(1)

    for col in range(im.size[0]):
        colval = 0

        for row in range(im.size[1]):
            if im.getpixel((col, row)) != 0:
                colval |= 1 << row

        scanline.append(colval)

    return scanline

def scanlineFormatter(scanline):
    return '{%s}' % ', '.join([hex(val) for val in scanline])

def framesFormatter(frames):
    return ',\n        '.join([scanlineFormatter(scanline) for scanline in frames])

def process(filesNames):
    frames = []
    for f in filesNames:
        scanline = convertFile(f)
        frames.append(scanline)

    colsClasses = list(set([len(frame) for frame in frames]))
    if len(colsClasses) != 1:
        print('ERROR: The source frames must be having the same size', file=sys.stderr)
        sys.exit(1)

    return {'cols': colsClasses[0], 'framesCount': len(frames),
            'frames': framesFormatter(frames)}

class BandwidthAction(argparse.Action):
    def __call__(self, parser, namespace, values, option_string=None):
        if values <= 0:
            parser.error("Minimum bandwidth for {0} is 12".format(option_string))
            #raise argparse.ArgumentError("Minimum bandwidth is 12")

        setattr(namespace, self.dest, values)

def main():
    parser = argparse.ArgumentParser(description='Shaki frames converter',
            formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('--outfile', '-o', default='frame_data.h',
            help='Output C-Header file')
    parser.add_argument('--template', '-t', default=TEMPLATE_PATH,
            help='Template file')
    parser.add_argument('--spf', type=int, default=5,
            help='How many shakes each frame will be painted before advancing to the next one (non-zero integer)')
    parser.add_argument('infiles', nargs='+')

    args = parser.parse_args()

    if args.spf <= 0:
        parser.error('SPF must be a non-zero positive integer')

    context = process(args.infiles)
    context['spf'] = args.spf
    template = open(args.template).read()

    fout = open(args.outfile, 'w')
    fout.write(template % context)
    fout.close()


if __name__ == '__main__':
    main()
