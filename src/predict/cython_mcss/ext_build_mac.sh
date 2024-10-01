#!/bin/sh
# Delete existing temporary build folder and extension.
rm -r build && rm -r *.so
# run the python script and link sqlite.
python3 cpp_setup_mac.py build_ext --inplace -larmadillo -lsqlite3
