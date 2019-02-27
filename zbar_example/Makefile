PP=g++
CFLAGS=`pkg-config --cflags --libs opencv zbar`
DEPS = barcode-image-scanner-zbar.h

%.o: %.c $(DEPS)
	$(PP) -c -o $@ $< $(CFLAGS)

barcode: barcode-image-displayer.o barcode-image-scanner-zbar.o 
	$(PP) barcode-image-displayer.o barcode-image-scanner-zbar.o 
