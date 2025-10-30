#include <stdio.h>
#include <stdlib.h>
#include <cups/raster.h>
#include "pcl6.h"

int main() {
	cups_raster_t *ras = cupsRasterOpen(0, CUPS_RASTER_READ);
	cups_page_header2_t header;
	FILE *out = fopen("output.pcl", "wb");
	int streamHeaderEmitted = 0;
	int page = 0;
	unsigned int y;

	while (cupsRasterReadHeader2(ras, &header)) {
		if(!streamHeaderEmitted) {
		    pcl6_start_session(out, &header);
			streamHeaderEmitted = 1;
			printf("Page header info:\n");
			printf("cupsWidth: %d\n", header.cupsWidth);
			printf("cupsHeight: %d\n", header.cupsHeight);
			printf("cupsBitsPerColor: %d\n", header.cupsBitsPerColor);
			printf("cupsBytesPerLine: %d\n", header.cupsBytesPerLine);
			printf("HWResolution: %d x %d\n", header.HWResolution[0], header.HWResolution[1]);
			printf("cupsColorSpace: %d\n", header.cupsColorSpace);
			printf("Orientation: %d\n", header.Orientation);
			printf("MediaType: %s\n", header.MediaType);
		}

		page++;
        printf("Page: %d\n", page);

		pcl6_start_job(out, &header);

		unsigned char *line = malloc(header.cupsBytesPerLine);
		for (y = 0; y < header.cupsHeight; y++) {
			if(cupsRasterReadPixels(ras, line, header.cupsBytesPerLine) == 0)
				break;
			pcl6_write_raster_line(out, line, header.cupsBytesPerLine, y);
		}
		free(line);

		pcl6_end_job(out);
	}

	pcl6_end_session(out);

	fclose(out);
	cupsRasterClose(ras);

	printf("PCL6 file output.pcl is ready!\n");
	return 0;
}
