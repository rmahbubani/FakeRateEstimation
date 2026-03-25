To add this analysis to checkmate:
put the .cc analysis file in checkmate2/tools/analysis/src/analyses/ATLAS_13TeV/, 
put the .h header file in checkmate2/tools/analysis/include/analyses/ATLAS_13TeV/ 
put the var.j file in checkmate2/data/analysis_info/ATLAS_13TeV/
add the following line to the checkmate2/data/analysis_info/ATLAS_13TeV_analysis.txt:
"atlas_2l_i3hdm_fakes 1    dilepton fakes                       300.0            no"
and compile.

The compilation commands are:

autoreconf --force --install
./configure --prefix=`pwd` --with-rootsys=$ROOTSYS/ --with-delphes=${DELPHES_PATH} --with-hepmc=${HEPMC_PATH} --with-gziplib=${GZIP_PATH} --with-gzipinc=/usr/include/
(where each of these paths need to be defined for your system)
make install
