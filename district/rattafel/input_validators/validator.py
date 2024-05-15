import re
import sys

pattern = r"[a-zA-Z0-9:;\.,\-'\"!? #\n]{1,1000000}"
regex = re.compile(pattern)
sys.exit(42)
