import os
import sys

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
TEST_DIR = os.path.join(PROJECT_ROOT, 'tests')
sys.path.insert(0, PROJECT_ROOT)
