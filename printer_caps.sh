#!/bin/bash

# Usage: ./printer_caps.sh <printer_name>

if [ -z "$1" ]; then
    echo "Usage: $0 <printer_name>"
    exit 1
fi

PRN="$1"

echo "=== Printer Capabilities for: $PRN ==="
lpstat -v "$PRN" 2>/dev/null | sed 's/device for //'

echo
echo "--- Basic Options ---"
lpoptions -p "$PRN" -l 2>/dev/null | grep -E "PageSize|Resolution|ColorModel|Duplex" || echo "No details found."

echo
echo "--- PDL / Language Support ---"

# Get the printer’s device URI
URI=$(lpstat -v "$PRN" 2>/dev/null | awk '{print $4}')

if [ -n "$URI" ]; then
    FORMATS=$(ipptool -tv "$URI" get-printer-attributes.test 2>/dev/null | \
              grep -i "document-format-supported" | \
              sed 's/.*= //; s/,/ /g' | tr -d '{}' | tr ' ' '\n' | sort -u)

    if [ -n "$FORMATS" ]; then
        echo "$FORMATS" | while read -r mime; do
            case "$mime" in
                *pclxl*) echo "  • PCL XL (PCL6)";;
                *pcl5*)  echo "  • PCL 5";;
                *postscript*) echo "  • PostScript";;
                *pdf*) echo "  • PDF";;
                *pwg-raster*) echo "  • PWG Raster";;
                *urf*) echo "  • Apple Raster (URF)";;
                *jpeg*) echo "  • JPEG";;
                *cups-raster*) echo "  • CUPS Raster";;
                *) echo "  • $mime";;
            esac
        done
    else
        echo "  No PDL information found (printer may not be IPP-capable)."
    fi
else
    echo "  Printer URI not found."
fi

echo
echo "--- IPP Attributes ---"
ipptool -tv "$URI" get-printer-attributes.test 2>/dev/null | \
grep -E "printer-make-and-model|media-supported|printer-resolution-supported|print-color-mode-supported|sides-supported" || \
echo "IPP query failed or printer not IPP-capable."

echo
echo "--- Color Capability ---"
COLOR=$(ipptool -tv "$URI" get-printer-attributes.test 2>/dev/null | \
        grep -i "print-color-mode-supported" | grep -o "color" | head -n1)

if [ -n "$COLOR" ]; then
    echo "  • Supports Color Printing"
else
    echo "  • Monochrome Only"
fi

