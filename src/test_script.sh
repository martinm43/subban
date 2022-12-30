
#!/bin/bash
cd predict/cython_mcss
./ext_build.sh
cd ../..
python prediction_table.py
