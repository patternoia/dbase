#include "FairDbWtTCanvasWidget.h"

#include <Wt/WPainter>
#include <Wt/WPainterPath>
#include <Wt/WPointF>
#include <Wt/WRectF>

#include <math.h>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include "TList.h"


namespace {
  // the blue emweb color
  WColor emweb(0x04, 0x7c, 0x93);
}

FairDbWtTCanvasWidget::FairDbWtTCanvasWidget(WContainerWidget *parent, TCanvas* gcanvas)
  : WPaintedWidget(parent),
    angle_(0),
    size_(1),
    fCanvas(gcanvas) 
{
  resize(710, 400);
}

void FairDbWtTCanvasWidget::setAngle(double angle)
{
  angle = std::max(-30.0, std::min(30.0, angle));

  if (angle_ != angle) {
    angle_ = angle;
    update();
  }
}

void FairDbWtTCanvasWidget::setRelativeSize(double size)
{
  size = std::max(0.1, std::min(1.0, size));

  if (size_ != size) {
    size_ = size;
    update();
  }
}

void FairDbWtTCanvasWidget::paintEvent(WPaintDevice *paintDevice)
{
  std::cout << "------ PAINTING CALLED !!!!!! " << std::endl;
  WPainter painter(paintDevice);

  painter.setShadow(WShadow(10, 10, WColor(0, 0, 0, 50), 10));
  painter.setRenderHint(WPainter::Antialiasing);

  painter.translate(width().value()/2, height().value()/2);
  painter.rotate(angle_);
  painter.scale(size_, size_);
  painter.translate(-width().value()/2 + 50, -height().value()/2 + 150);

  drawTCanvas(painter);
  //drawEmwebLogo(painter);

}

void FairDbWtTCanvasWidget::drawTCanvas(WPainter& painter)
{

std::cout << "------ drawTGraph called !!!!!! " << std::endl;
std::cout << " TCanvas Definition -----> WW: "  
             <<  fCanvas->GetWindowWidth()  <<  " WH: "
             <<  fCanvas->GetWindowHeight()  <<  std::endl;

int ww = fCanvas->GetWindowWidth();
int wh = fCanvas->GetWindowHeight();

// Resize according to the canvas
resize(ww, wh);

// Get objects contains in the canvas
TObjOptLink *lnk = (TObjOptLink*) fCanvas->GetListOfPrimitives()->FirstLink();
 TObject *obj;

   while (lnk) {
      obj = lnk->GetObject();
      if (obj->IsA() == TGraph::Class()) {
        // draw for Graph;
        drawTGraph( painter, (TGraph*) obj );
      }

    //obj->Paint(lnk->GetOption());
    lnk = (TObjOptLink*)lnk->Next();

   } //! (while)   

}

void FairDbWtTCanvasWidget::drawTGraph(WPainter& painter, TGraph* aGraph)
{
 
   int theNpoints = aGraph->GetN();
   double *theX  = aGraph->GetX();
   double *theY  = aGraph->GetY();


  // Prototype method to draw a Graph, by hand --- 
  //new WText(WString::tr("TGraph represented"), this);

  WStandardItemModel *model = new WStandardItemModel(theNpoints, 2, this);
  model->setItemPrototype(new NumericItem());
  model->setHeaderData(0, WString("X"));
  model->setHeaderData(1, WString("Y"));

  for (unsigned i = 0; i < theNpoints; ++i) {
    //double x = (static_cast<double>(i) - 20) / 4;
    model->setData(i, 0, theX[i]);
    model->setData(i, 1, theY[i]);
  }
 
  
  // Create the scatter plot.
   
  WCartesianChart *chart = new WCartesianChart();
  chart->setModel(model);        // set the model
  chart->setXSeriesColumn(0);    // set the column that holds the X data
  chart->setLegendEnabled(true); // enable the legend
  chart->setType(ScatterPlot);   // set type to ScatterPlot

  // Typically, for mathematical functions, you want the axes to cross
  // at the 0 mark:
  chart->axis(XAxis).setLocation(ZeroValue);
  chart->axis(YAxis).setLocation(ZeroValue);

  // Automatically layout chart (space for axes, legend, ...)
  //chart->setAutoLayoutEnabled();

  // Add the curves
  WDataSeries s(1, CurveSeries);
  s.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));
  chart->addSeries(s);

  int ww = fCanvas->GetWindowWidth();
  int wh = fCanvas->GetWindowHeight();

  //chart->resize(ww, wh); // WPaintedWidget must be given explicit size

  chart->setMargin(10, Top | Bottom);            // add margin vertically
  chart->setMargin(WLength::Auto, Left | Right); // center horizontally

  //ChartConfig *config = new ChartConfig(chart, this);
  //config->setValueFill(ZeroValueFill);
    
  // paint on the device  
  chart->paint(painter);
}


void FairDbWtTCanvasWidget::drawEmwebE(WPainter& painter)
{
  WPainterPath p;

  /* Path copied from our SVG for half of the E */

  p.moveTo(46.835084,58.783624);
  p.cubicTo(45.700172,58.783624,35.350098,58.911502,24.656354,63.283309);
  p.cubicTo(8.7595992,69.78907,0,82.38499,0,98.809238);
  p.cubicTo(0,115.20152,08.7595992,127.82141,24.656354,134.31119);
  p.cubicTo(35.350098,138.69099,45.700172,138.81088,46.835084,138.81088);
  p.lineTo(94.509362,138.81088);
  p.lineTo(94.509362,117.58323);
  p.lineTo(46.835084,117.58323);
  p.cubicTo(46.811106,117.58323,39.466151,117.47134,32.608727,114.53815);
  p.cubicTo(25.095932,111.34122,21.747144,106.47389,21.747144,98.809238);
  p.cubicTo(21.747144,91.120612,25.095932,86.269265,32.608727,83.064338);
  p.cubicTo(39.466151,80.123159,46.811106,80.027251,46.89103,80.027251);
  p.lineTo(94.509362,80.027251);
  p.lineTo(94.509362,58.783624);
  p.lineTo(46.835084,58.783624);

  painter.drawPath(p);

  painter.save();
  painter.translate(0,-58.783624);
  painter.drawPath(p);
  painter.restore();
}

void FairDbWtTCanvasWidget::drawEmwebMW(WPainter& painter)
{
  WPainterPath p;

  /* Path copied from our SVG for one fourth of the MW */

  p.moveTo(120.59634,24.072913);
  p.cubicTo(116.12064,34.518895,115.98477,44.605222,115.98477,45.732141);
  p.lineTo(115.98477,138.81088);
  p.lineTo(137.7399,138.81088);
  p.lineTo(137.7399,45.732141);
  p.cubicTo(137.7399,45.708164,137.83581,38.53904,140.84892,31.841463);
  p.cubicTo(144.14176,24.512492,149.113,21.235634,156.98545,21.235634);
  p.cubicTo(164.8499,21.235634,169.81314,24.512492,173.10599,31.841463);
  p.cubicTo(176.10311,38.53904,176.215,45.708164,176.215,45.780095);
  p.lineTo(176.215,70.41343);
  p.lineTo(197.97014,70.41343);
  p.lineTo(197.97014,45.732141);
  p.cubicTo(197.97014,44.605222,197.83427,34.518895,193.35057,24.072913);
  p.cubicTo(186.70894,8.5517985,173.77734,0,156.99344,0);
  p.cubicTo(140.17756,0,127.25396,8.5517985,120.59634,24.072913);

  /*
   * Paint it four times, translated and inverted
   */

  painter.drawPath(p);

  const double dx = 176. - 115.98477;

  painter.save();

  painter.translate(dx, 0);
  painter.drawPath(p);

  painter.translate(dx, 0);

  painter.scale(-1, -1);
  painter.translate(0, -138.81088);
  painter.translate(-115.98477 - 197.95 - dx, 0);
  painter.drawPath(p);

  painter.translate(dx, 0);
  painter.drawPath(p);

  painter.restore();
}

void FairDbWtTCanvasWidget::drawEmwebLogo(WPainter& painter)
{
  painter.save();
  painter.setPen(NoPen);

  /*
   * The emweb logo can be drawn as 3 e's, and one combined m/w
   */

  // Emweb
  painter.setBrush(black);
  drawEmwebE(painter);

  // emwEb
  painter.save();
  painter.translate(397, 0);
  drawEmwebE(painter);

  // emweB
  painter.translate(210, 0);
  painter.scale(-1, 1);
  drawEmwebE(painter);

  painter.restore();

  // eMWeb
  painter.setBrush(emweb);
  drawEmwebMW(painter);

  painter.restore();
}
