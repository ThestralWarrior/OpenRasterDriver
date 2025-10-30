#!/bin/sh

make
./openrasterdriver < samples/Free_Test_Data_100KB_PDF.ras
gpcl6 -dDEBUG -dPCLXLDEBUG -sDEVICE=pdfwrite -sOutputFile=output.pdf -dNOPAUSE -dBATCH output.pcl

