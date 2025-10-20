#include <stdint.h>
#include <string.h>
#include "pcl6.h"

/* Helper macros for writing bytes */
#define PUT8(v)		fputc((v) & 0xFF, out)
#define PUT16(v)	do { fputc((v) & 0xFF, out); fputc(((v) >> 8) & 0xFF, out); } while(0)
#define PUT32(v)	do { fputc((v) & 0xFF, out); fputc(((v) >> 8) & 0xFF, out); fputc(((v) >> 16) & 0xFF, out); fputc(((v) >> 24) & 0xFF, out); } while(0)

/* Helper to emit attribute (ubyte) */
static void pcl6_emit_attr_ubyte(FILE *out, uint8_t attr_id, uint8_t value) {
	PUT8(PCL_DT_UBYTE);
	PUT8(value);
	PUT8(PCL_ATTR_TAG_UBYTE);
	PUT8(attr_id);
}

/* Helper to emit attribute (uint16) */
static void pcl6_emit_attr_uint16(FILE *out, uint8_t attr_id, uint16_t value) {
	PUT8(PCL_DT_UINT16);
	PUT16(value);
	PUT8(PCL_ATTR_TAG_UBYTE);
	PUT8(attr_id);
}

/* Helper to emit attribute (uint16_xy) */
static void pcl6_emit_attr_uint16_xy(FILE *out, uint8_t attr_id, uint16_t x, uint16_t y) {
	PUT8(PCL_DT_UINT16_XY);
	PUT16(x);
	PUT16(y);
	PUT8(PCL_ATTR_TAG_UBYTE);
	PUT8(attr_id);
}

void pcl6_start_job(FILE *out, cups_page_header2_t *header) {
	/* Stream header */
	fputs(PCL_HEADER, out);
	
	/* BeginSession */
	pcl6_emit_attr_ubyte(out, PCL_ATTR_MEASURE, PCL_E_MEASURE_INCH);
	pcl6_emit_attr_uint16_xy(out, PCL_ATTR_UNITS_PER_MEASURE, header->HWResolution[0], header->HWResolution[1]);
	PUT8(PCL_OP_BEGIN_SESSION);
	
	/* BeginPage */
	pcl6_emit_attr_ubyte(out, PCL_ATTR_MEDIA_SIZE, PCL_E_MEDIA_A4);
	pcl6_emit_attr_ubyte(out, PCL_ATTR_ORIENTATION, PCL_E_ORIENT_PORTRAIT);
	PUT8(PCL_OP_BEGIN_PAGE);

	/* BeginScan */
    pcl6_emit_attr_uint16(out, PCL_ATTR_SOURCE_WIDTH, header->cupsWidth);
	pcl6_emit_attr_uint16(out, PCL_ATTR_SOURCE_HEIGHT, header->cupsHeight);
	pcl6_emit_attr_ubyte(out, PCL_ATTR_COLOR_SPACE, 
			header->cupsNumColors == 1 ? PCL_E_COLORSPACE_GRAY : PCL_E_COLORSPACE_RGB);
	pcl6_emit_attr_ubyte(out, PCL_ATTR_BITS_PER_PIXEL, header->cupsBitsPerPixel);
	pcl6_emit_attr_ubyte(out, PCL_ATTR_COMPRESSION, PCL_E_COMP_NONE);
	pcl6_emit_attr_ubyte(out, PCL_ATTR_ROP3, PCL_ROP3_SRC);
	PUT8(PCL_OP_BEGIN_SCAN);

}

void pcl6_write_raster_line(FILE *out, const unsigned char *data, int bytes_per_line) {
	PUT8(PCL_DT_EMBEDDED_DATA);
	PUT32(bytes_per_line);
	fwrite(data, 1, bytes_per_line, out);
	PUT8(PCL_OP_SCANLINE_REL);
}

void pcl6_end_job(FILE *out) {
	PUT8(PCL_OP_END_SCAN);
	PUT8(PCL_OP_END_PAGE);
	PUT8(PCL_OP_END_SESSION);
}
