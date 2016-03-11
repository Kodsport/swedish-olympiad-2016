#!/usr/bin/env python3
import os
import sys

output_fd = sys.stdout.buffer.fileno()
with open(sys.argv[1], 'rb') as file:
    while os.sendfile(output_fd, file.fileno(), None, 1 << 30) != 0:
        pass
