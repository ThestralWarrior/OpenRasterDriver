#include <stdio.h>
#include <stdlib.h>
#include <cups/raster.h>
#include "pcl6.h"

int main() {
	cups_raster_t *ras = cupsRasterOpen(0, CUPS_RASTER_READ);
	cups_page_header2_t header;
	FILE *out = fopen("output.pcl", "wb");
	int y;
	unsigned char *buffer;

	while (cupsRasterReadHeader2(ras, &header)) {

		pcl6_start_job(out, &header);

		if (header.cupsBytesPerLine <= 0)
			continue;

		buffer = malloc(header.cupsBytesPerLine);

		for(y = 0; y < header.cupsHeight; y++) {
			if(cupsRasterReadPixels(ras, buffer, header.cupsBytesPerLine) == 0)
				break;
			pcl6_write_raster_line(out, buffer, header.cupsBytesPerLine);
		}

		pcl6_end_job(out);

		free(buffer);
	}

	fclose(out);
	cupsRasterClose(ras);
	return 0;
}
