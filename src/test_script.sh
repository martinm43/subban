
#!/bin/bash
cd predict/cython_mcss
./ext_build.sh
cd ../..
python3 prediction_table.py
