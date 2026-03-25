To add this analysis to checkmate:
put the .cc analysis file in checkmate2/tools/analysis/src/analyses/ATLAS_13TeV/, 
put the .h header file in checkmate2/tools/analysis/include/analyses/ATLAS_13TeV/ 
put the var.j file in checkmate2/data/analysis_info/ATLAS_13TeV/
add the following line to the checkmate2/data/analysis_info/ATLAS_13TeV_analysis.txt:
  atlas_2l_i3hdm_fakes 1    dilepton fakes                       300.0            no
add the analysis to the list libanalyses_la_SOURCES in checkmate2/tools/analysis/Makefile, by adding the following lines:
	include/analyses/ATLAS_13TeV/atlas_2l_i3hdm_fakes.h \
	 src/analyses/ATLAS_13TeV/atlas_2l_i3hdm_fakes.cc
Add the include and cc files to the relevant AnalysisHanders.  In checkmate2/tools/fritz/include/analysishandler/AnalysisHandlerATLAS_13TeV.h add the line
  #include "atlas_2l_i3hdm_fakes.h"
within the analysis list, and before the "//@extraheader@"
In checkmate2/tools/fritz/src/analysishandler/AnalysisHandlerATLAS_13TeV.cc add the lines
      else if(analysisName == "atlas_2l_i3hdm_fakes")
        a = new Atlas_2l_i3hdm_fakes();
to the bookAnalysis function, before "else //@@extracode@@"

and compile.

The compilation commands are:

autoreconf --force --install
./configure --prefix=`pwd` --with-rootsys=$ROOTSYS/ --with-delphes=${DELPHES_PATH} --with-hepmc=${HEPMC_PATH} --with-gziplib=${GZIP_PATH} --with-gzipinc=/usr/include/
(where each of these paths need to be defined for your system)
make install
