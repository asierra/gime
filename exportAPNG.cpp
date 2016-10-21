#include <stdio.h>
#include <stdlib.h>
#include <QImage>
#include <QStringList>
#include <QPainter>
#include <png.h>

#include "path.h"
#include "gime_scene.h"


int exportToAPNG(QString filename, QStringList list, GimeScene *escena)
{
  png_structp png_ptr_write;
  png_infop info_ptr_write;
  png_bytepp rowPointers;
	
  FILE *file = fopen(filename.toStdString().c_str(), "wb");

  if (file == NULL) {
    //    qDebug() <<  "Unable to open file" <<filename << endl;
    return -1;
  }

  png_ptr_write = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (png_ptr_write == NULL) {
    //  fprintf(stderr, "unable to create write struct\n");
    return -1;
  }
  info_ptr_write = png_create_info_struct(png_ptr_write);
  if (info_ptr_write == NULL) {
    //fprintf(stderr, "unable to create info struct\n");
    return -1;
  }
  png_init_io(png_ptr_write, file);

  QImage ima;
  int image_idx = Path::image_idx; 
  for (int i=0; i < list.size(); i++) {
    if (ima.load(list.at(i))) {
      ima = ima.convertToFormat(QImage::Format_RGB888);
      if (escena!=NULL) {
	QPainter painter(&ima);
	painter.setRenderHint(QPainter::Antialiasing);
	Path::image_idx = i;
	escena->updatePositions();
	escena->render(&painter);
	painter.end();
      }
			
      if (i==0) {
	printf("ima depth %d %d %d\n",  ima.depth(), ima.format(), ima.bitPlaneCount());
	png_set_IHDR(png_ptr_write, info_ptr_write,  ima.width(), ima.height(),
		     ima.depth()/3, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		     PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_set_acTL(png_ptr_write, info_ptr_write, list.size(), 0);

	png_write_info(png_ptr_write, info_ptr_write);

	//				int bytesPerRow = png_get_rowbytes(png_ptr_write, info_ptr_write);
				
	rowPointers = new png_bytep[ima.height()];

      }
      png_write_frame_head(png_ptr_write, info_ptr_write, rowPointers,
			   ima.width(), ima.height(),
			   0, 0,
			   1, 1,
			   PNG_DISPOSE_OP_NONE,
			   PNG_BLEND_OP_SOURCE 
			   );

      for (int j=0; j < ima.height(); j++)
	rowPointers[j] = (png_bytep)ima.constScanLine(j);
      png_write_image(png_ptr_write, rowPointers);
      png_write_frame_tail(png_ptr_write, info_ptr_write);
    } 

  }
  Path::image_idx = image_idx;
  escena->updatePositions();
  png_write_end(png_ptr_write, NULL);
  png_destroy_write_struct(&png_ptr_write, &info_ptr_write);
  fclose(file);

  printf("all done\n");

  return 0;
}
