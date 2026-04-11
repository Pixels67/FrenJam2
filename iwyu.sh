iwyu_tool.py -p cmake-build-iwyu/ src/ -j 8 \
  -- --cxx17ns \
  2>&1 | tee iwyu_output.txt
